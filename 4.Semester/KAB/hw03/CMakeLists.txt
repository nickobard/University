cmake_minimum_required(VERSION 3.25)
project(task4_asymmetric)

set(CMAKE_CXX_STANDARD 17)
set(WARNINGS "-Wall -pedantic")
set(MEMDEBUGGER "-fsanitize=address")
set(CMAKE_CXX_FLAGS ${WARNINGS})

add_executable(debug solution.cpp)
add_executable(memdebug solution.cpp)

target_link_libraries(debug crypto)
target_link_libraries(memdebug crypto)

# Setting additional memory debugger flag for memdebug target
target_compile_options(memdebug PRIVATE ${MEMDEBUGGER})
# Need to add memory debugger to linker too
target_link_options(memdebug PRIVATE ${MEMDEBUGGER})
