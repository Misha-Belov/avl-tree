cmake_minimum_required(VERSION 3.14)
project("avl-tree")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(avl_tree INTERFACE)
target_include_directories(avl_tree INTERFACE includes)

add_executable(tree_bin main.cpp)
target_link_libraries(tree_bin avl_tree)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  tests_bin
  tests/avl_tree_test.cpp
)

target_link_libraries(tests_bin avl_tree)

target_link_libraries(
  tests_bin
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests_bin)
