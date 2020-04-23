//#include <CUnit/CUnit.h>
#include <stdbool.h>

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

/*#include <stdio.h>
//#include <string.h>
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

static bool * universe;

/* Simple test of get_universe().
 */
void test_get_universe(void)
{
    universe = get_universe(3);
    CU_ASSERT(universe != (bool *)0);
}

/* test initializer for universe
*/

locus disp[] = {
    {0, 1},
    {1, 1},
    {-1, 0},
};

void test_init_universe(void)
{
    init_universe(disp);
}

/* Simple test of release_universe()
*/
void test_release_universe(void)
{
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
       (NULL == CU_add_test(pSuite, "test of release_universe()", test_release_universe)) ||
       (NULL == CU_add_test(pSuite, "test of init_universe()", test_init_universe)))
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
