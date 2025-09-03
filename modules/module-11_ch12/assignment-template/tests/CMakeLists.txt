# Simple test executable
add_executable(hw11_tests test_main.cpp)
target_include_directories(hw11_tests PRIVATE ../src)
add_test(NAME HW11_Tests COMMAND hw11_tests)
