# Simple test executable
add_executable(hw04_tests test_main.cpp)
target_include_directories(hw04_tests PRIVATE ../src)
add_test(NAME HW04_Tests COMMAND hw04_tests)
