cmake_minimum_required(VERSION 3.25)
project(progtest)

set(CMAKE_CXX_STANDARD 17)
set(WARNINGS "-Wall -pedantic")
set(MEMDEBUGGER "-fsanitize=address")
set(OPTIMIZATION "-O2")
set(CMAKE_CXX_FLAGS ${WARNINGS})


add_executable(debug main.cpp src/Bytes.cpp src/Bytes.hpp src/Hasher.cpp src/Hasher.hpp)
add_executable(memdebug main.cpp src/Bytes.cpp src/Bytes.hpp src/Hasher.cpp src/Hasher.hpp)
add_executable(release main.cpp src/Bytes.cpp src/Bytes.hpp src/Hasher.cpp src/Hasher.hpp)
add_executable(progtest progtest.cpp)

target_link_libraries(debug crypto)
target_link_libraries(memdebug crypto)
target_link_libraries(progtest crypto)
target_link_libraries(release crypto)

target_compile_options(release PRIVATE ${OPTIMIZATION})

target_compile_options(progtest PRIVATE ${MEMDEBUGGER})
target_link_options(progtest PRIVATE ${MEMDEBUGGER})


# Setting additional memory debugger flag for memdebug target
target_compile_options(memdebug PRIVATE ${MEMDEBUGGER})
# Need to add memory debugger to linker too
target_link_options(memdebug PRIVATE ${MEMDEBUGGER})
