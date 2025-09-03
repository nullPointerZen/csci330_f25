# Simple test executable
add_executable(hw09_tests test_main.cpp)
target_include_directories(hw09_tests PRIVATE ../src)
add_test(NAME HW09_Tests COMMAND hw09_tests)
