
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/t.ld")
set(TARGET_NAME "vid")

add_executable(${TARGET_NAME}.elf
    src/ts.s
    ${PROJECT_SOURCE_DIR}/src/uart.c
    src/vid.c
    src/t.c
)

add_custom_command(
    TARGET ${TARGET_NAME}.elf
    PRE_LINK
    COMMAND ${CMAKE_OBJCOPY} ARGS -I binary -O elf32-littlearm -B arm --redefine-syms symbol_names_image0.txt ${PROJECT_SOURCE_DIR}/UC_Riverside_Vert_BluBG_sm.bmp image0.o
    COMMAND ${CMAKE_OBJCOPY} ARGS -I binary -O elf32-littlearm -B arm --redefine-syms symbol_names_image1.txt ${PROJECT_SOURCE_DIR}/UC_Riverside_Vert_WhtBG_sm.bmp image1.o
)

add_custom_command(TARGET ${TARGET_NAME}.elf
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${TARGET_NAME}.elf ${TARGET_NAME}.bin
)

set_target_properties(${TARGET_NAME}.elf PROPERTIES
    ADDITIONAL_CLEAN_FILES ${TARGET_NAME}.bin
)

target_include_directories(${TARGET_NAME}.elf PUBLIC  ${PROJECT_SOURCE_DIR}/include include/)
# Add the linker flag to the target

target_compile_options(${TARGET_NAME}.elf PRIVATE -mcpu=arm926ej-s)

target_link_options(${TARGET_NAME}.elf PRIVATE 
    "-T${CMAKE_CURRENT_SOURCE_DIR}/t.ld" # Linker script path
    "--specs=nano.specs"                 # Optimized C library
    "-Wl,--gc-sections"                  # Remove unused code
)

set_target_properties(${TARGET_NAME}.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
