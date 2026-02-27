cmake_minimum_required(VERSION 3.28)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-toolchain.cmake)

project(cs122_lecture LANGUAGES C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(C2.1)
add_subdirectory(C2.2)
add_subdirectory(C2.3)
add_subdirectory(C2.4)
add_subdirectory(C2.5)
add_subdirectory(C2.6)
add_subdirectory(C2.7)
add_subdirectory(C3.1)
add_subdirectory(C3.2)