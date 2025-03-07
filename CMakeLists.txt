cmake_minimum_required(VERSION 3.14)
project("avl-tree")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(avl_tree INTERFACE)
target_include_directories(avl_tree INTERFACE includes)

add_executable(tree_bin main.cpp)
target_link_libraries(tree_bin avl_tree)


find_package(googletest REQUIRED)

enable_testing()

add_executable(
  tests_bin
  tests/avl_tree_test.cpp
)

target_link_libraries(tests_bin avl_tree)

target_link_libraries(
  tests_bin
  googletest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests_bin)
