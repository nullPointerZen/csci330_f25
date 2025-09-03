# Simple test executable
add_executable(hw05_tests test_main.cpp)
target_include_directories(hw05_tests PRIVATE ../src)
add_test(NAME HW05_Tests COMMAND hw05_tests)
