#include <catch.hpp>

#include "life.hpp"

// construct and return state as constructed.
int construct_destroy_cell(void)
{
    Cell c(0, 0);
    return c.get_state();
}

// construct and progress to live
int construct_vivify_cell(void)
{
    Cell c(0, 0);
    c.vivify();
    return c.get_state();
}

// construct and set to dying
int construct_kill_cell(void)
{
    Cell c(0, 0);
    c.kill();
    return c.get_state();
}

// is_live at construction
bool construct_is_live(void)
{
    Cell c(0, 0);
    return c.is_live();
}

TEST_CASE("constructor/destructor for cell", "[ctor/dtor]")
{
    REQUIRE(construct_destroy_cell() == born);
    REQUIRE(construct_vivify_cell() == live);
    REQUIRE(construct_kill_cell() == dying);
    REQUIRE(construct_is_live() == false);
}

// testing adjacency

// report if two cells are adjacent
bool check_is_next_to(const Cell a, const Cell b)
{
    return a.is_next_to(b);
}

TEST_CASE("is cell next to another", "[adjacency]")
{
    // all adjacent positions
    REQUIRE(check_is_next_to(Cell(1, 1), Cell(0, 0)) == true);
    REQUIRE(check_is_next_to(Cell(1, 1), Cell(1, 0)) == true);
    REQUIRE(check_is_next_to(Cell(1, 1), Cell(2, 0)) == true);

    REQUIRE(check_is_next_to(Cell(1, 1), Cell(0, 1)) == true);
    REQUIRE(check_is_next_to(Cell(1, 1), Cell(2, 1)) == true);

    REQUIRE(check_is_next_to(Cell(1, 1), Cell(0, 2)) == true);
    REQUIRE(check_is_next_to(Cell(1, 1), Cell(1, 2)) == true);
    REQUIRE(check_is_next_to(Cell(1, 1), Cell(2, 2)) == true);

    // non-adjacent positions, corners and edges
    REQUIRE(check_is_next_to(Cell(2, 2), Cell(0, 0)) == false);
    REQUIRE(check_is_next_to(Cell(2, 2), Cell(0, 2)) == false);
    REQUIRE(check_is_next_to(Cell(2, 2), Cell(0, 4)) == false);
    REQUIRE(check_is_next_to(Cell(2, 2), Cell(2, 4)) == false);
    REQUIRE(check_is_next_to(Cell(2, 2), Cell(4, 4)) == false);
    REQUIRE(check_is_next_to(Cell(2, 2), Cell(4, 2)) == false);
    REQUIRE(check_is_next_to(Cell(2, 2), Cell(4, 0)) == false);
    REQUIRE(check_is_next_to(Cell(2, 2), Cell(2, 4)) == false);

    // same cell
    REQUIRE(check_is_next_to(Cell(2, 2), Cell(2, 2)) == false);
}

// build and test the universe

// construct and return state as constructed.
int construct_destroy_universe(void)
{
    Universe u = Universe();
    return u.cell_count();
}

int add_cell_universe(int cells)
{
    Universe u = Universe();
    for (int i = 0; i < cells; i++)
    {
        u.add_cell(i, 0);
    }
    //u.dump();
    return u.cell_count();
}

TEST_CASE("constructor/destructor for Universe", "[Universe-ctor/dtor]")
{
    REQUIRE(construct_destroy_universe() == 0);
    REQUIRE(add_cell_universe(1) == 1);
    REQUIRE(add_cell_universe(2) == 2);
}

// test neighbor count, count neighbors for coords[check]
int count_neighbor_cells(int coords[][2], uint count, int check_x, int check_y)
{
    Universe u = Universe();
    Cell c(check_x, check_y);

    for (uint i = 0; i < count; i++)
        u.add_cell(coords[i][0], coords[i][1]);

    // verify that cells loaded
    REQUIRE(count == u.cell_count());
    //u.dump();
    //std::cout << "T " << c << std::endl;
    return u.count_neighbors(c);
}

TEST_CASE("count cell neighbors in Universe", "[Universe-count-neighbors]")
{
    int case0[][2] = {{0, 0}, {0, 1}};
    /*
    |X
    |X 
     - */
    REQUIRE(count_neighbor_cells(case0, sizeof(case0) / sizeof(case0[0]), 0,0) == 1);
    REQUIRE(count_neighbor_cells(case0, sizeof(case0) / sizeof(case0[0]), 0,1) == 1);

    /*
    |X
    |X 
    |X 
     - */
    int case1[][2] = {{0, 0}, {0, 1}, {0, 2}};
    REQUIRE(count_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 0,0) == 1);
    REQUIRE(count_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 0,1) == 2);
    REQUIRE(count_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 0,2) == 1);

    // tests from empty adjacent cells
    /*
    |X
    |X 
    |X T
    |- */

    REQUIRE(count_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 0, 1) == 2);
    /*
    |X 
    |X T
    |X 
    |- */

    REQUIRE(count_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 1, 1) == 3);
    /*
    |X 
    |X . T
    |X 
    |- */

    REQUIRE(count_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 2, 1) == 0);
}
