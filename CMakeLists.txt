# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    iterators
    VERSION 0.1
    DESCRIPTION "Defining Iterators Sample")


add_executable(main main.cpp)
add_subdirectory(tests)

# Tell C++ compiler to use C++17 features.
target_compile_features(main PUBLIC cxx_std_17)