
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/t.ld")
set(TARGET_NAME "c_from_asm")

add_executable(${TARGET_NAME}.elf
    src/t.c
    src/ts.s
)

add_custom_command(TARGET ${TARGET_NAME}.elf
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${TARGET_NAME}.elf ${TARGET_NAME}.bin
)

set_target_properties(${TARGET_NAME}.elf PROPERTIES
    ADDITIONAL_CLEAN_FILES ${TARGET_NAME}.bin
)

target_include_directories(${TARGET_NAME}.elf PUBLIC include/)
# Add the linker flag to the target

target_link_options(${TARGET_NAME}.elf PRIVATE 
    "-T${CMAKE_CURRENT_SOURCE_DIR}/t.ld" # Linker script path
    "--specs=nano.specs"                 # Optimized C library
    "-Wl,--gc-sections"                  # Remove unused code
)

set_target_properties(${TARGET_NAME}.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
