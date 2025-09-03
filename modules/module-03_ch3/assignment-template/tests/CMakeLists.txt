# Simple test executable
add_executable(hw03_tests test_main.cpp)
target_include_directories(hw03_tests PRIVATE ../src)
add_test(NAME HW03_Tests COMMAND hw03_tests)
