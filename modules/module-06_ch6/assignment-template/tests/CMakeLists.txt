# Simple test executable
add_executable(hw06_tests test_main.cpp)
target_include_directories(hw06_tests PRIVATE ../src)
add_test(NAME HW06_Tests COMMAND hw06_tests)
