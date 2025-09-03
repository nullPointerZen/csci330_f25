# Simple test executable
add_executable(hw12_tests test_main.cpp)
target_include_directories(hw12_tests PRIVATE ../src)
add_test(NAME HW12_Tests COMMAND hw12_tests)
