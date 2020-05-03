cmake_minimum_required(VERSION 3.7)
project(game_of_life)

# Minimum version as iknstalled on Debian Stretch
 
#Bring the headers, such as tower.h into the project
include_directories(inc)
 
#Can manually add the sources using the set command as follows:
#set(SOURCES src/tower.cpp)
 
#However, the file(GLOB...) allows for wildcard additions:
#file(TEST_SOURCES   )

# add some C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb -Wall -std=c++11 ")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -Wall -std=c++11 ")
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -ggdb -Wall -std=c++11 ")

# sources for stack test app
# add_executable(test_stack 
#     src/catch2_Main.cpp
#     src/test-stack.cpp 
#     src/stack.cpp)

# sources for board test app
# add_executable(test_board 
#     src/catch2_Main.cpp
#     src/test-board.cpp 
#     src/stack.cpp
#     src/board.cpp)

# sources for test executable
add_executable(test_logic 
    src/test_logic.cpp)



# Now some unit tests
include(CTest)

# Test stack related ========================
# does the application run
add_test (TestLogicRuns test_logic)

# does all internal Catch2 tests pass?
#add_test (StackCatch2TestOK test_stack)
#set_tests_properties (StackCatch2TestOK PROPERTIES PASS_REGULAR_EXPRESSION "All tests passed")

# does valgrind report any problems?
#add_test (StackValgrindTestOK valgrind ./test_stack)
#set_tests_properties (StackValgrindTestOK PROPERTIES PASS_REGULAR_EXPRESSION
#    "ERROR SUMMARY: 0 errors from 0 contexts")
#set_tests_properties (StackValgrindTestOK PROPERTIES FAIL_REGULAR_EXPRESSION
#    "LEAK SUMMARY")

#set_tests_properties(StackTestRuns StackCatch2TestOK StackValgrindTestOK 
#    PROPERTIES LABELS StackTest)

# Test board related ========================
# does the application run
#add_test (BoardTestRuns test_board)

# does all internal Catch2 tests pass?
#add_test (BoardCatch2TestOK test_board)
#set_tests_properties (BoardCatch2TestOK PROPERTIES PASS_REGULAR_EXPRESSION "All tests passed")

# does valgrind report any problems?
#add_test (BoardValgrindTestOK valgrind ./test_board)
#set_tests_properties (BoardValgrindTestOK PROPERTIES PASS_REGULAR_EXPRESSION
#    "ERROR SUMMARY: 0 errors from 0 contexts")
## set_tests_properties (BoardValgrindTestOK PROPERTIES FAIL_REGULAR_EXPRESSION
##    "LEAK SUMMARY")

#set_tests_properties(BoardTestRuns BoardCatch2TestOK BoardValgrindTestOK 
#    PROPERTIES LABELS BoardTest)