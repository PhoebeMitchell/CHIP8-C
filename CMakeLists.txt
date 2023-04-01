cmake_minimum_required(VERSION 3.23)
project(CHIP8_C C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(CHIP8_C main.c src/Architecture/Memory.c src/Architecture/Memory.h src/Font.h src/Interface/Window.c src/Interface/Window.h src/Architecture/Stack.c src/Architecture/Stack.h src/Architecture/Keypad.c src/Architecture/Keypad.h src/Architecture/Processor.c src/Architecture/Processor.h src/System.h src/System.c src/Architecture/Display.c src/Architecture/Display.h)

target_link_libraries(CHIP8_C ${SDL2_LIBRARIES})

include(CTest)
add_subdirectory(external)
add_subdirectory(tests)
