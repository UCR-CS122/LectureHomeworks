
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/t.ld")
set(TARGET_NAME "keyboard_2")
set(SECTION_NAME "C3_3")
set(SYMBOL_NAME_PREFIX "symbol_names_${SECTION_NAME}")

add_executable(${TARGET_NAME}.elf
    src/ts.s
    ${PROJECT_SOURCE_DIR}/src/uart.c
    ${PROJECT_SOURCE_DIR}/src/vid.c
    ${PROJECT_SOURCE_DIR}/src/font.c
    ${PROJECT_SOURCE_DIR}/src/string.c
    ${PROJECT_SOURCE_DIR}/src/exceptions.c
    ${PROJECT_SOURCE_DIR}/src/timer.c
    src/kbd.c
    src/t.c
)

add_custom_command(
    TARGET ${TARGET_NAME}.elf
    PRE_LINK
    COMMAND ${CMAKE_OBJCOPY} ARGS -I binary -O elf32-littlearm -B arm --redefine-syms ${SYMBOL_NAME_PREFIX}_image0.txt ${CMAKE_CURRENT_SOURCE_DIR}/simpsonized_allan.bmp image0.o
)

add_custom_target(${SYMBOL_NAME_PREFIX}_image0.txt 
    ${PROJECT_SOURCE_DIR}/update_symbols.py ${CMAKE_CURRENT_SOURCE_DIR}/simpsonized_allan.bmp ${SYMBOL_NAME_PREFIX}_image0.txt 
)

add_dependencies(${TARGET_NAME}.elf ${SYMBOL_NAME_PREFIX}_image0.txt)

add_custom_command(TARGET ${TARGET_NAME}.elf
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${TARGET_NAME}.elf ${TARGET_NAME}.bin
)

set_target_properties(${TARGET_NAME}.elf PROPERTIES
    ADDITIONAL_CLEAN_FILES "${TARGET_NAME}.bin;image0.o;${SYMBOL_NAME_PREFIX}_image0.txt"
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
