# Simple test executable
add_executable(hw14_tests test_main.cpp)
target_include_directories(hw14_tests PRIVATE ../src)
add_test(NAME HW14_Tests COMMAND hw14_tests)
