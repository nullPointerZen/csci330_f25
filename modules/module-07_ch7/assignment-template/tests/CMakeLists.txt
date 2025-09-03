# Simple test executable
add_executable(hw07_tests test_main.cpp)
target_include_directories(hw07_tests PRIVATE ../src)
add_test(NAME HW07_Tests COMMAND hw07_tests)
