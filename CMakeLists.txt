cmake_minimum_required(VERSION 3.23)
project(CHIP8_C C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(CHIP8_C main.c src/Architecture/Memory.c src/Architecture/Memory.h src/Font.h src/Display/Window.c src/Display/Window.h src/Architecture/Stack.c src/Architecture/Stack.h src/Architecture/Keypad.c src/Architecture/Keypad.h)

target_link_libraries(CHIP8_C ${SDL2_LIBRARIES})

include(CTest)
add_subdirectory(external)
add_subdirectory(tests)
