cmake_minimum_required(VERSION 3.28)
project(Proj_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static ")

add_executable(Proj_1
        Proj_1.cpp
        Chopstick.cpp
        Philosopher.cpp
        )

set_target_properties(Proj_1 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

target_compile_options(Proj_1 PRIVATE
        -O0
        -march=x86-64
)
