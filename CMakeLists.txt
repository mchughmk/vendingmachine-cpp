cmake_minimum_required(VERSION 3.5.0)
project(VendingMachine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
