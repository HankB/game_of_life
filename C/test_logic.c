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
    bool * universe = get_universe(5);

    CU_ASSERT(universe != (bool *)0);

    release_universe(universe);
}

/* test the macro OFFSET() 
*/

void test_OFFSET(void)
{
    locus l = {0,0};
    static const uint width=5;

    /* visual crutch ;)
    | 0| 1| 2| 3| 4|
    | 5| 6| 7| 8| 9|
    |10|11|12|13|14|
    |15|16|17|18|19|
    |20|21|22|23|24|
    */

    CU_ASSERT(OFFSET(l, width) == 0);                   // (0,0)
    CU_ASSERT(OFFSET_COORD(l.col, l.row, width) == 0);

    l.col = 1;
    CU_ASSERT(OFFSET(l, width) == 1);                       // (1,0)
    CU_ASSERT(OFFSET_COORD(l.col, l.row, width) == 1);

    l.col = 2;
    CU_ASSERT(OFFSET(l, width) == 2);                       // (2,0)
    CU_ASSERT(OFFSET_COORD(l.col, l.row, width) == 2);

    l.col = 0;
    l.row = 1;
    CU_ASSERT(OFFSET(l, width) == 5);                       // (0,1)
    CU_ASSERT(OFFSET_COORD(l.col, l.row, width) == 5);

    l.col = 1;
    CU_ASSERT(OFFSET(l, width) == 6);                       // (1,1)
    CU_ASSERT(OFFSET_COORD(l.col, l.row, width) == 6);

    l.col = l.row = 2;
    CU_ASSERT(OFFSET(l, width) == 12);                      // (2,2)
    CU_ASSERT(OFFSET_COORD(l.col, l.row, width) == 12);

    l.col = 4,
    l.row = 2;
    CU_ASSERT(OFFSET(l, width) == 14);                      // (4,2)
    CU_ASSERT(OFFSET_COORD(l.col, l.row, width) == 14);

    l.col = 2,
    l.row = 4;
    //printf("%d, %d\n", OFFSET(l, width), OFFSET_COORD(l.col, l.row, width));
    CU_ASSERT(OFFSET(l, width) == 22);                      // (2,4)
    CU_ASSERT(OFFSET_COORD(l.col, l.row, width) == 22);
}

/* test initializer for universe
*/

    /* visual crutch ;)
    | 0| 1| 2| 3| 4|
    | 5| 6| 7| 8| 9|
    |10|11|12|13|14|
    |15|16|17|18|19|
    |20|21|22|23|24|
    */

locus disp_live[] = { // initial values to populate a grid (live cells)
    {0, 2},
    {1, 0},
    {1, 1},
    {2, 2},
    {3, 4},
    {4, 0},
    {4, 3},
    {4, 4},
    {-1, -1}, // end of init list
};
/* 
___________
|_|X|_|_|X|
|_|X|_|_|_|
|X|_|X|_|_|
|_|_|_|_|X|
|_|_|_|X|X|
*/

locus disp_dead[] = { // initial values for dead cells
    {0, 0},  
    {0, 1},
    {0, 3},
    {0, 4},

    {1, 2},
    {1, 3},
    {1, 4},

    {2, 0},
    {2, 1},
    {2, 3},
    {2, 4},

    {3, 0},
    {3, 1},
    {3, 2},
    {3, 3},

    {4, 1},
    {4, 2},
    {-1, -1},
};

void test_init_universe(void)
{
    static const uint width=5;
    bool * universe = get_universe(width);
    int     i = 0;
    int     live_count;

    int rc = init_universe(universe, width, disp_live);
    CU_ASSERT(rc == 0);
    while(disp_live[i].row >= 0) {
        CU_ASSERT(universe[OFFSET(disp_live[i],width)] == true);
        i++;
    }
    live_count = i;

    i = 0;
    while(disp_dead[i].row >= 0) {
        CU_ASSERT(universe[OFFSET(disp_dead[i],width)] == false);
        i++;
    }

    // and finally, count the true cells in universe
    int count=0;
    for(i=0; i<width*width; i++) {
        if(universe[i]) {
            count++;
        }
    }
    CU_ASSERT(count == live_count);

    release_universe(universe);
}

/* Test some formatting functions
*/
void test_print_top(void)
{
    static const uint width=5;
    static const size_t buf_len = width*2+3;
    char    buffer[buf_len];
    uint    return_len;
    bool * universe = get_universe(width);

    init_universe(universe, width, disp_live);
    memset(buffer, ' ', buf_len);

    return_len = print_top(width, buffer, buf_len-2);
    CU_ASSERT_STRING_EQUAL(buffer, "_________\n");
    CU_ASSERT_EQUAL(return_len, buf_len-3);
    memset(buffer, ' ', buf_len);

    return_len = print_top(width, buffer, buf_len);
    //printf(">%s< %d %ld\n", buffer, return_len, strlen(buffer));
    CU_ASSERT_STRING_EQUAL(buffer, "___________\n");
    CU_ASSERT_EQUAL(return_len, buf_len-1);
    memset(buffer, ' ', buf_len);

    return_len = print_top(width, buffer, buf_len);
    CU_ASSERT_STRING_EQUAL(buffer, "___________\n");
    CU_ASSERT_EQUAL(return_len, buf_len-1);

    release_universe(universe);
}

/* Test some formatting one line of outpiut
*/
void test_print_line(void)
{
    static const uint width=5;
    static const size_t buf_len = width*2+3;
    char buffer[buf_len];
    uint    return_len;
    bool * universe = get_universe(width);

    init_universe(universe, width, disp_live);

   // print first row
    memset(buffer, ' ', buf_len);
    return_len = print_line(width, 0, buffer, buf_len, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|_|X|_|_|X|\n");
    CU_ASSERT_EQUAL(return_len, width*2+2);

    // print second row
    memset(buffer, ' ', buf_len);
    return_len = print_line(width, 1, buffer, buf_len, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|_|X|_|_|_|\n");
    CU_ASSERT_EQUAL(return_len, width*2+2);

    // print third row
    memset(buffer, ' ', buf_len);
    return_len = print_line(width, 2, buffer, buf_len, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|X|_|X|_|_|\n");
    CU_ASSERT_EQUAL(return_len, width*2+2);

    // print third row, exact buffer space
    memset(buffer, ' ', buf_len);
    return_len = print_line(width, 2, buffer, width*2+3, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|X|_|X|_|_|\n");
    CU_ASSERT_EQUAL(return_len, width*2+2);

    // print third row, insufficient buffer space
    memset(buffer, ' ', buf_len);
    return_len = print_line(width, 2, buffer, width*2, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|X|_|X|_|\n");
    CU_ASSERT_EQUAL(return_len, width*2);

    // print third row, insufficient buffer space
    memset(buffer, ' ', buf_len);
    return_len = print_line(width, 2, buffer, width*2-1, universe);
    CU_ASSERT_STRING_EQUAL(buffer, "|X|_|X|\n");
    CU_ASSERT_EQUAL(return_len, width*2-2);
    
    release_universe(universe);
}

/* Test formatting of the entire grid
*/
void test_print_universe(void)
{
    static const uint width=5;
    static const size_t buf_len = (width+1)*(width+1)*2+3;
    char buffer[buf_len];
    uint    return_len;
    static const char* test_str = "___________\n"
"|_|X|_|_|X|\n"
"|_|X|_|_|_|\n"
"|X|_|X|_|_|\n"
"|_|_|_|_|X|\n"
"|_|_|_|X|X|\n";

    bool * universe = get_universe(width);

    init_universe(universe, width, disp_live);
    memset(buffer, 'O', buf_len);

    return_len = print_universe(width, buffer, buf_len, universe);
    CU_ASSERT_STRING_EQUAL(buffer, test_str);
    CU_ASSERT_EQUAL(return_len, 72);



    // test for memory bounds errors
    // depends on compiling with -fsanitize=address
    for(int i=0; i<10; i++) {
        return_len = print_universe(width, buffer+i, buf_len-i, universe);
        memset(buffer, 'O', buf_len);
    }

    release_universe(universe);
}

/* Simple test of release_universe()
*/
void test_release_universe(void)
{
    static const uint width=5;
    bool * universe = get_universe(width);

    release_universe(universe);
    universe = 0;
    CU_ASSERT(universe == (bool *)0);
}

// Tests for core logic

/* test code to count live neighbors.
*/
void test_count_neighbors(void)
{
    static const uint width=5;
    bool *  universe = get_universe(width);
    locus   l = {1,1};

    init_universe(universe, width, disp_live);

    // first some tests with univers populated with disp_live[]
    uint count = count_neighbors(universe, l, width);
    CU_ASSERT_EQUAL(count, 3);

    l.row = 0; // (1,0)
    count = count_neighbors(universe, l, width);
    CU_ASSERT_EQUAL(count, 1);

    // now test four corners
    l.col = 0; // (0,0)
    count = count_neighbors(universe, l, width);
    CU_ASSERT_EQUAL(count, 2);

    l.col = width-1; // (0,width-1)
    count = count_neighbors(universe, l, width);
    CU_ASSERT_EQUAL(count, 0);

    l.row = width-1; // (width-1,width-1)
    count = count_neighbors(universe, l, width);
    CU_ASSERT_EQUAL(count, 2);

    l.col = 0; // (0,width-1)
    count = count_neighbors(universe, l, width);
    CU_ASSERT_EQUAL(count, 0);

// test four edges 
    l.col = 2; l.row = 0; // (2,0)
    count = count_neighbors(universe, l, width);
    CU_ASSERT_EQUAL(count, 2);

    l.row = 4; // (2,4)
    count = count_neighbors(universe, l, width);
    CU_ASSERT_EQUAL(count, 1);

    l.col = 0; l.row = 2; // (0,2)
    count = count_neighbors(universe, l, width);
    CU_ASSERT_EQUAL(count, 1);

    l.col = 4; // (4,2)
    count = count_neighbors(universe, l, width);
    CU_ASSERT_EQUAL(count, 1);

    // Complete test of dsp_live grid

    // expected results, by row

    uint    disp_live_counts[] = {
        2, 1, 2, 1, 0,
        3, 3, 3, 2, 1,
        1, 3, 1, 2, 1,
        1, 2, 2, 4, 2,
        0, 0, 1, 2, 2,
    };

    // check all cells
    for(int i=0; i<width*width; i++) {
        l.col = i%width;
        l.row = i/width;
        uint    count = count_neighbors(universe, l, width);
        CU_ASSERT_EQUAL(count, disp_live_counts[i]);
    }


//#define NEED_OUTPUT 1
#if NEED_OUTPUT
    static const size_t buf_len = (width+1)*(width+1)*2+3;
    char    buffer[buf_len];
    print_universe(width, buffer, buf_len, universe);
    printf("\n%s%d\n", buffer, count);
#endif

    release_universe(universe); // finished with this universe

// Create a grid with one live cell in the middle and test all cells around it.

    locus disp_center[] = { // initial values to populate a grid (live cells)
        {2, 2},
        {-1, -1},
    };

    universe = get_universe(width);
    int rc = init_universe(universe, width, disp_center);
    CU_ASSERT(rc == 0);

    locus t[] = {
        {1,1},
        {2,1},
        {3,1},
        {2,1},
        {2,3},
        {3,1},
        {1,3},
        {2,3},
        {3,3},
    };

    for(int i=0; i<(sizeof t)/sizeof(t[0]); i++) {
        CU_ASSERT_EQUAL(count_neighbors(universe, t[i], width), 1);
    }

    release_universe(universe);
}


void test_calc_next_gen(void)
{
    static const uint width=5;
    bool *  u1 = get_universe(width);
    bool *  u2 = get_universe(width);

    int rc = init_universe(u1, width, disp_live);
    CU_ASSERT(rc == 0);

    int count = calc_next_gen(u1, u2, width);

#define NEED_OUTPUT 1
#if NEED_OUTPUT
    static const size_t buf_len = (width+1)*(width+1)*2+3;
    char    buffer[buf_len];
    print_universe(width, buffer, buf_len, u1);
    printf("\n%s%d\n", buffer, count);
    print_universe(width, buffer, buf_len, u2);
    printf("\n%s%d\n", buffer, count);
#endif

    release_universe(u1);
    release_universe(u2);
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

   /* add a suite to the registry - utility functions*/
   pSuite = CU_add_suite("test Utility", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test of get_universe()", test_get_universe)) ||
        (NULL == CU_add_test(pSuite, "test of init_universe()", test_init_universe)) ||
        (NULL == CU_add_test(pSuite, "test of OFFSET() macro", test_OFFSET))
       )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add a suite to the registry - output functions*/
   pSuite = CU_add_suite("test Output", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   
    if ((NULL == CU_add_test(pSuite, "test of print_top()", test_print_top)) ||
        (NULL == CU_add_test(pSuite, "test of print_line()", test_print_line)) ||
        (NULL == CU_add_test(pSuite, "test of print_universe()", test_print_universe)) ||
        (NULL == CU_add_test(pSuite, "test of release_universe()", test_release_universe))
       )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add a suite to the registry - core logic*/
   pSuite = CU_add_suite("test core logic", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
    if ((NULL == CU_add_test(pSuite, "test of count_neighbors()", test_count_neighbors)) ||
        (NULL == CU_add_test(pSuite, "test of test_calc_next_gen()", test_calc_next_gen)) 
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

