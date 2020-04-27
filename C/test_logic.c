//#include <CUnit/CUnit.h>
#include <stdbool.h>
#include <stdlib.h>

#include "life.h"

// Following boilerplate copied from http://cunit.sourceforge.net/example.html
// and modified to suit. Commentary below no longer relavent but preserved to
// identify the starting point

/*
 *  Simple example of a CUnit unit test.
 *
 *  This program (crudely) demonstrates a very simple "black box"
 *  test of the standard library functions fprintf() and fread().
 *  It uses suite initialization and cleanup functions to open
 *  and close a common temporary file used by the test functions.
 *  The test functions then write to and read from the temporary
 *  file in the course of testing the library functions.
 *
 *  The 2 test functions are added to a single CUnit suite, and
 *  then run using the CUnit Basic interface.  The output of the
 *  program (on CUnit version 2.0-2) is:
 *
 *           CUnit : A Unit testing framework for C.
 *           http://cunit.sourceforge.net/
 *
 *       Suite: Suite_1
 *         Test: test of fprintf() ... passed
 *         Test: test of fread() ... passed
 *
 *       --Run Summary: Type      Total     Ran  Passed  Failed
 *                      suites        1       1     n/a       0
 *                      tests         2       2       2       0
 *                      asserts       5       5       5       0
 */

#include "CUnit/Basic.h"

/* The suite initialization function.
 * Does nothing
 */
int init_suite1(void)
{
    return 0;
}

/* The suite cleanup function.
 * Does nothing
 */
int clean_suite1(void)
{
    return 0;
}


/* Simple test of get_universe().
 */
void test_get_universe(void)
{
    bool * universe = get_universe(3);

    CU_ASSERT(universe != (bool *)0);

    release_universe(universe);
}

/* test the macro OFFSET() 
*/

void test_OFFSET(void)
{
    locus l = {0,0};

    /* visual crutch ;)
    |0|1|2|
    |3|4|5|
    |6|7|8|
    */

    CU_ASSERT(OFFSET(l, 3) == 0);
    CU_ASSERT(OFFSET_COORD(l.col, l.row, 3) == 0);
    l.col = 1;
    CU_ASSERT(OFFSET(l, 3) == 1);
    CU_ASSERT(OFFSET_COORD(l.col, l.row, 3) == 1);
    l.col = 2;
    CU_ASSERT(OFFSET(l, 3) == 2);
    CU_ASSERT(OFFSET_COORD(l.col, l.row, 3) == 2);
    l.col = 0;
    l.row = 1;
    CU_ASSERT(OFFSET(l, 3) == 3);
    CU_ASSERT(OFFSET_COORD(l.col, l.row, 3) == 3);
    l.col = 1;
    CU_ASSERT(OFFSET(l, 3) == 4);
    CU_ASSERT(OFFSET_COORD(l.col, l.row, 3) == 4);
    l.col = l.row = 2;
    CU_ASSERT(OFFSET(l, 3) == 8);
    CU_ASSERT(OFFSET_COORD(l.col, l.row, 3) == 8);
}

/* test initializer for universe
*/

locus disp[] = {
    {0, 1},
    {1, 1},
    {2, 0},
    {2, 2},
    {-1, 0}, // end of init list
    {0, 0},  // start of entrioes to ID remaining cells
    {0, 2},
    {1, 0},
    {1, 2},
    {2, 1},
};

void test_init_universe(void)
{
    bool * universe = get_universe(3);

    init_universe(universe, 3, disp);
    CU_ASSERT(universe[OFFSET(disp[0],3)] == true);
    CU_ASSERT(universe[OFFSET(disp[1],3)] == true);
    CU_ASSERT(universe[OFFSET(disp[2],3)] == true);

    for(int i=5; i<10; i++) {
        CU_ASSERT(universe[OFFSET(disp[i],3)] == false);
    }

    // and finally, count the true cells in universe
    int count=0;
    for(int i=0; i<3*3; i++) {
        if(universe[i]) {
            count++;
        }
    }
    CU_ASSERT(count == 4);

    release_universe(universe);
}

/* Test some formatting functions
*/
void test_print_top(void)
{
    static const size_t buf_len = 10;
    char    buffer[buf_len];
    uint    return_len;
    bool * universe = get_universe(3);

    init_universe(universe, 3, disp);
    memset(buffer, ' ', buf_len);

    return_len = print_top(3, buffer, buf_len);
    CU_ASSERT_STRING_EQUAL(buffer, "_______\n");
    CU_ASSERT_EQUAL(return_len, 8);

    return_len = print_top(5, buffer, buf_len);
    CU_ASSERT_STRING_EQUAL(buffer, "________\n");
    CU_ASSERT_EQUAL(return_len, 9);

    return_len = print_top(4, buffer, buf_len);
    CU_ASSERT_STRING_EQUAL(buffer, "________\n");
    CU_ASSERT_EQUAL(return_len, 9);

    release_universe(universe);
}

/* Test some formatting one line of outpiut
*/
void test_print_line(void)
{
    static const size_t buf_len = 10;
    char buffer[buf_len];
    uint    return_len;
    bool * universe = get_universe(3);

     init_universe(universe, 3, disp);

   // print first row
    memset(buffer, ' ', buf_len);
    return_len = print_line(3, 0, buffer, buf_len, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|_|X|_|\n");
    CU_ASSERT_EQUAL(return_len, 8);

    // print second row
    memset(buffer, ' ', buf_len);
    return_len = print_line(3, 1, buffer, buf_len, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|_|X|_|\n");
    CU_ASSERT_EQUAL(return_len, 8);

    // print third row
    memset(buffer, ' ', buf_len);
    return_len = print_line(3, 2, buffer, buf_len, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|X|_|X|\n");
    CU_ASSERT_EQUAL(return_len, 8);

    // print third row, exact buffer space
    memset(buffer, ' ', buf_len);
    return_len = print_line(3, 2, buffer, 9, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|X|_|X|\n");
    CU_ASSERT_EQUAL(return_len, 8);

    // print third row, insufficient buffer space
    memset(buffer, ' ', buf_len);
    return_len = print_line(3, 2, buffer, 8, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|X|_|X|\n");
    CU_ASSERT_EQUAL(return_len, 8);

    // print third row, insufficient buffer space
    memset(buffer, ' ', buf_len);
    return_len = print_line(3, 2, buffer, 7, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|X|_|\n");
    CU_ASSERT_EQUAL(return_len, 6);
    
    release_universe(universe);
}

/* Test formatting of the entire grid
*/
void test_print_universe(void)
{
    static const size_t buf_len = 33;
    char buffer[buf_len];
    uint    return_len;
    static const char* test_str = "_______\n|_|X|_|\n|_|X|_|\n|X|_|X|\n";
    bool * universe = get_universe(3);

    init_universe(universe, 3, disp);
    memset(buffer, 'O', buf_len);

    return_len = print_universe(3, buffer, buf_len, universe);
    CU_ASSERT_STRING_EQUAL(buffer, test_str);
    CU_ASSERT_EQUAL(return_len, 32);



    // test for memory bounds errors
    // depends on compiling with -fsanitize=address
    for(int i=0; i<10; i++) {
        return_len = print_universe(3, buffer+i, buf_len-i, universe);
        memset(buffer, 'O', buf_len);
    }

    release_universe(universe);
}

/* Simple test of release_universe()
*/
void test_release_universe(void)
{
    bool * universe = get_universe(3);

    release_universe(universe);
    universe = 0;
    CU_ASSERT(universe == (bool *)0);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "test of get_universe()", test_get_universe)) ||
       (NULL == CU_add_test(pSuite, "test of init_universe()", test_init_universe)) ||
       (NULL == CU_add_test(pSuite, "test of OFFSET() macro", test_OFFSET)) ||
       (NULL == CU_add_test(pSuite, "test of print_top()", test_print_top)) ||
       (NULL == CU_add_test(pSuite, "test of print_line()", test_print_line)) ||
       (NULL == CU_add_test(pSuite, "test of print_universe()", test_print_universe)) ||
       (NULL == CU_add_test(pSuite, "test of release_universe()", test_release_universe))
       )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

