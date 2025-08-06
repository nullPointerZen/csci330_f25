# Simple test executable
add_executable(hw01_tests test_main.cpp)
target_include_directories(hw01_tests PRIVATE ../src)
add_test(NAME HW01_Tests COMMAND hw01_tests)
