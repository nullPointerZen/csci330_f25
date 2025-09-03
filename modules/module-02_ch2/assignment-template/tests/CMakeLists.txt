# Simple test executable
add_executable(hw02_tests test_main.cpp)
target_include_directories(hw02_tests PRIVATE ../src)
add_test(NAME HW02_Tests COMMAND hw02_tests)
