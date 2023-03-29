add_executable(memoryTests MemoryTests.c ../src/Architecture/Memory.h ../src/Architecture/Memory.c)
add_executable(stackTests StackTests.c ../src/Architecture/Stack.h ../src/Architecture/Stack.c)

target_link_libraries(memoryTests Unity)
target_link_libraries(stackTests Unity)

add_test(MemoryTests memoryTests)
add_test(StackTests stackTests)