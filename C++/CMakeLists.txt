cmake_minimum_required(VERSION 3.7)
project(game_of_life)

# Minimum cmake version as installed on Debian Stretch
 
# Bring the headers, such as logic.h into the project
include_directories(inc)
 
# Can manually add the sources using the set command as follows:
#set(SOURCES src/tower.cpp)
 
#However, the file(GLOB...) allows for wildcard additions:
#file(TEST_SOURCES   )

# add some C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb -Wall -std=c++11 ")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -Wall -std=c++11 ")
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -ggdb -Wall -std=c++11 ")

# sources for test executable
add_executable(test_logic 
    src/test_logic.cpp
    src/catch2_Main.cpp
    src/util.cpp
    src//logic.cpp)


# Now some tests
include(CTest)

# Test logic related ========================
# does the application run
add_test (TestLogicRuns test_logic)

# do Catch2 tests pass?
add_test (LogicCatch2TestOK test_logic)
set_tests_properties (LogicCatch2TestOK PROPERTIES PASS_REGULAR_EXPRESSION "All tests passed")

# does valgrind report any problems?
add_test (ValgrindTestLogicOK valgrind ./test_logic)
set_tests_properties (ValgrindTestLogicOK PROPERTIES PASS_REGULAR_EXPRESSION
    "ERROR SUMMARY: 0 errors from 0 contexts")
set_tests_properties (ValgrindTestLogicOK PROPERTIES FAIL_REGULAR_EXPRESSION
    "LEAK SUMMARY")

# another valgrind report any problems?
add_test (ValgrindTestLogic_sgcheck_OK valgrind --tool=exp-sgcheck ./test_logic)
set_tests_properties (ValgrindTestLogic_sgcheck_OK PROPERTIES PASS_REGULAR_EXPRESSION
    "ERROR SUMMARY: 0 errors from 0 contexts")
set_tests_properties (ValgrindTestLogic_sgcheck_OK PROPERTIES FAIL_REGULAR_EXPRESSION
    "LEAK SUMMARY")

set_tests_properties(TestLogicRuns LogicCatch2TestOK ValgrindTestLogicOK ValgrindTestLogic_sgcheck_OK
    PROPERTIES LABELS LogicTest)
