cmake_minimum_required(VERSION 3.23)
project(hw02_Bestsellers)

set(CMAKE_CXX_STANDARD 17)
set(WARNINGS "-Wall -pedantic")
set(MEMDEBUGGER "-fsanitize=address")

set(CMAKE_CXX_FLAGS ${WARNINGS})

add_executable(hw02_Bestsellers main.cpp)
add_executable(memdebug main.cpp)

# Setting additional memory debugger flag for memdebug target
target_compile_options(memdebug PRIVATE ${MEMDEBUGGER})
# Need to add memory debugger to linker too
target_link_options(memdebug PRIVATE ${MEMDEBUGGER})