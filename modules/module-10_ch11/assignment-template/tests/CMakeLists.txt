# Simple test executable
add_executable(hw10_tests test_main.cpp)
target_include_directories(hw10_tests PRIVATE ../src)
add_test(NAME HW10_Tests COMMAND hw10_tests)
