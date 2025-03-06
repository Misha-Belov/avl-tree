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

file(GLOB testfiles "tests/integration/*.dat")

foreach(file ${testfiles})
    get_filename_component(testname ${file} NAME_WE)
    add_test(
        NAME ${testname}
        COMMAND python3 ${CMAKE_SOURCE_DIR}/run_test.py ${file} ./tree_bin
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    set_tests_properties(${testname} PROPERTIES DEPENDS tree_bin)
endforeach()
