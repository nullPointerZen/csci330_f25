# Simple test executable
add_executable(hw08_tests test_main.cpp)
target_include_directories(hw08_tests PRIVATE ../src)
add_test(NAME HW08_Tests COMMAND hw08_tests)
