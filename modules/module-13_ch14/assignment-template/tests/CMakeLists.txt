# Simple test executable
add_executable(hw13_tests test_main.cpp)
target_include_directories(hw13_tests PRIVATE ../src)
add_test(NAME HW13_Tests COMMAND hw13_tests)
