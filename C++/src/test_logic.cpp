#include <catch.hpp>

#include "life.hpp"

// construct and return state as constructed.
int construct_destroy_cell(void)
{
    Cell c(0, 0);
    return c.get_state();
}

// construct and return state as constructed.
int construct_destroy_cell_state(cell_state st)
{
    Cell c(0, 0, st);
    return c.get_state();
}

// is_live at construction
bool construct_isnt_live(void)
{
    Cell c(0, 0);
    return !c.is_live();
}

// is_live at construction
bool construct_is_live(void)
{
    Cell c(0, 0, live);
    return c.is_live();
}

TEST_CASE("constructor/destructor for cell", "[ctor/dtor]")
{
    REQUIRE(construct_destroy_cell() == born);
    REQUIRE(construct_destroy_cell_state(live) == live);
    REQUIRE(construct_destroy_cell_state(dying) == dying);
    REQUIRE(construct_isnt_live() == true);
    REQUIRE(construct_is_live() == true);
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

// setup for cell for further testing
typedef struct
{
    int x_coord;
    int y_coord;
    cell_state state;
} TestCell;

// test neighbor count, count neighbors for coords[check]
int count_live_neighbor_cells(TestCell cells[], uint count, int check_x, int check_y)
{
    Universe u = Universe();
    Cell c(check_x, check_y);

    for (uint i = 0; i < count; i++)
        u.add_cell(cells[i].x_coord, cells[i].y_coord, cells[i].state);

    // verify that cells loaded
    REQUIRE(count == u.cell_count());
    //u.dump();
    //std::cout << "T " << c << std::endl;
    return u.count_live_neighbors(c);
}

TEST_CASE("count cell neighbors in Universe", "[Universe-count-neighbors]")
{
    TestCell case0[] = {{0, 0, live}, {0, 1, live}};
    /*
    |X
    |X 
     - */
    REQUIRE(count_live_neighbor_cells(case0, sizeof(case0) / sizeof(case0[0]), 0, 0) == 1);
    REQUIRE(count_live_neighbor_cells(case0, sizeof(case0) / sizeof(case0[0]), 0, 1) == 1);
    REQUIRE(count_live_neighbor_cells(case0, sizeof(case0) / sizeof(case0[0]), 0, 2) == 1);
    REQUIRE(count_live_neighbor_cells(case0, sizeof(case0) / sizeof(case0[0]), 0, 3) == 0);
    REQUIRE(count_live_neighbor_cells(case0, sizeof(case0) / sizeof(case0[0]), 2, 0) == 0);
    REQUIRE(count_live_neighbor_cells(case0, sizeof(case0) / sizeof(case0[0]), 2, 1) == 0);
    REQUIRE(count_live_neighbor_cells(case0, sizeof(case0) / sizeof(case0[0]), 1, 0) == 2);

    /*
    |X
    |X 
    |X 
     - */
    TestCell case1[] = {{0, 0, live}, {0, 1, live}, {0, 2, live}};
    REQUIRE(count_live_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 0, 0) == 1);
    REQUIRE(count_live_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 0, 1) == 2);
    REQUIRE(count_live_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 0, 2) == 1);
    REQUIRE(count_live_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 1, 1) == 3);
    REQUIRE(count_live_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 1, 0) == 2);

    // tests from empty adjacent cells
    /*
    |X
    |X 
    |X T
    |- */

    REQUIRE(count_live_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 0, 1) == 2);
    /*
    |X 
    |X T
    |X 
    |- */

    REQUIRE(count_live_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 1, 1) == 3);
    /*
    |X 
    |X . T
    |X 
    |- */

    REQUIRE(count_live_neighbor_cells(case1, sizeof(case1) / sizeof(case1[0]), 2, 1) == 0);
    /*
    |b
    |X 
    |X 
     - */
    TestCell case2[] = {{0, 0, live}, {0, 1, live}, {0, 2, born}};
    REQUIRE(count_live_neighbor_cells(case2, sizeof(case2) / sizeof(case2[0]), 0, 0) == 1);
    REQUIRE(count_live_neighbor_cells(case2, sizeof(case2) / sizeof(case2[0]), 0, 1) == 1);
    REQUIRE(count_live_neighbor_cells(case2, sizeof(case2) / sizeof(case2[0]), 0, 2) == 1);
    REQUIRE(count_live_neighbor_cells(case2, sizeof(case2) / sizeof(case2[0]), 1, 2) == 1);
    REQUIRE(count_live_neighbor_cells(case2, sizeof(case2) / sizeof(case2[0]), 1, 1) == 2);
    REQUIRE(count_live_neighbor_cells(case2, sizeof(case2) / sizeof(case2[0]), 1, 0) == 2);

    TestCell case3[] = {{0, 0, live}, {0, 1, live}, {0, 2, dying}};
    REQUIRE(count_live_neighbor_cells(case3, sizeof(case3) / sizeof(case3[0]), 0, 0) == 1);
    REQUIRE(count_live_neighbor_cells(case3, sizeof(case3) / sizeof(case3[0]), 0, 1) == 2);
    REQUIRE(count_live_neighbor_cells(case3, sizeof(case3) / sizeof(case3[0]), 0, 2) == 1);
    REQUIRE(count_live_neighbor_cells(case3, sizeof(case3) / sizeof(case3[0]), 1, 1) == 3);
    REQUIRE(count_live_neighbor_cells(case3, sizeof(case3) / sizeof(case3[0]), 1, 0) == 2);
}

int count_evaluate_live_cells(int coords[][2], uint count)
{
    Universe u = Universe();
    uint live_count;

    for (uint i = 0; i < count; i++)
        u.add_cell(coords[i][0], coords[i][1], live);

    // verify that cells loaded
    REQUIRE(count == u.cell_count());
    // evaluate which ones remain
    live_count = u.evaluate_live_cells();

    return live_count;
}

TEST_CASE("evaluates in Universe", "[Universe-process-live]")
{
    int case0[][2] = {{0, 0}, {0, 1}};
    /*
    |X
    |X 
     - */
    REQUIRE(count_evaluate_live_cells(case0, sizeof(case0) / sizeof(case0[0])) == 0);
    /*
    |X
    |X 
    |X 
     - */
    int case1[][2] = {{0, 0}, {0, 1}, {0, 2}};
    REQUIRE(count_evaluate_live_cells(case1, sizeof(case1) / sizeof(case1[0])) == 1);
    /*
    | X
    |XXX
    | X 
     - */
    int case2[][2] = {{1, 0}, {1, 1}, {1, 2}, {0, 1}, {2, 1}};
    REQUIRE(count_evaluate_live_cells(case2, sizeof(case2) / sizeof(case2[0])) == 4);
}

// test find_cell()

bool use_find_cells(TestCell cells[], uint count, int x, int y)
{
    Universe u = Universe();

   /* for (uint i = 0; i < count; i++)
        u.add_cell(coords[i][0], coords[i][1]); */
    for (uint i = 0; i < count; i++)
        u.add_cell(cells[i].x_coord, cells[i].y_coord, cells[i].state);

    std::list<Cell>::const_iterator c = u.find_cell(x, y);

    if (c != u.end())
    {
        REQUIRE((c->get_x() == x && c->get_y() == y));
        return true;
    }
    return false;
}

TEST_CASE("find cells in Universe", "[Universe-find-cell]")
{
    TestCell case0[] = {{0, 0, live}, {0, 1, live}};
    /*
    |X
    |X 
     - */
    REQUIRE(use_find_cells(case0, sizeof(case0) / sizeof(case0[0]), 0, 0) == true);
    REQUIRE(use_find_cells(case0, sizeof(case0) / sizeof(case0[0]), 0, 1) == true);
    REQUIRE(use_find_cells(case0, sizeof(case0) / sizeof(case0[0]), 0, 2) == false);
    REQUIRE(use_find_cells(case0, 0, 0, 0) == false);
    /*
    | X
    |XXX
    | X 
     - */
    TestCell case1[] = {{1, 0, live}, {1, 1, live}, {1, 2, live}, {0, 1, live}, {2, 1, live}};
    REQUIRE(use_find_cells(case1, sizeof(case1) / sizeof(case1[0]), 0, 0) == false);
    REQUIRE(use_find_cells(case1, sizeof(case1) / sizeof(case1[0]), 1, 0) == true);
    REQUIRE(use_find_cells(case1, sizeof(case1) / sizeof(case1[0]), 1, 1) == true);
    REQUIRE(use_find_cells(case1, sizeof(case1) / sizeof(case1[0]), 1, 2) == true);
    REQUIRE(use_find_cells(case1, sizeof(case1) / sizeof(case1[0]), 0, 1) == true);
    REQUIRE(use_find_cells(case1, sizeof(case1) / sizeof(case1[0]), 2, 1) == true);
}

int count_evaluate_empty_cells(TestCell cells[], uint count)
{
    Universe u = Universe();
    uint vivify_count;

    for (uint i = 0; i < count; i++)
        u.add_cell(cells[i].x_coord, cells[i].y_coord, cells[i].state);

    // verify that cells loaded
    REQUIRE(count == u.cell_count());
    // evaluate which ones remain
    vivify_count = u.evaluate_empty_neighbors();

    // were the right number of cells added
    REQUIRE(count + vivify_count == u.cell_count());

    return vivify_count;
}

TEST_CASE("empty neighbors in Universe", "[Universe-process-empty]")
{
    //int case0[][2] = {{0, 0}, {0, 1}};
    TestCell case0[] = {
        {1, 1, live},
    };
    /*
    |X
    |X 
     - */
    REQUIRE(count_evaluate_empty_cells(case0, sizeof(case0) / sizeof(case0[0])) == 0);
    /*
    |X
    |X 
    |X 
     - */
    TestCell case1[] = {{0, 0, live}, {0, 1, live}, {0, 2, live}};
    REQUIRE(count_evaluate_empty_cells(case1, sizeof(case1) / sizeof(case1[0])) == 2);
    /*
    | X
    |XXX
    | X 
     - */
    TestCell case2[] = {{1, 0, live}, {1, 1, live}, {1, 2, live}, {0, 1, live}, {2, 1, live}};
    REQUIRE(count_evaluate_empty_cells(case2, sizeof(case2) / sizeof(case2[0])) == 4);

    TestCell case3[] = {{1, 0, born}, {1, 1, live}, {1, 2, live}, {0, 1, live}, {2, 1, live}};
    REQUIRE(count_evaluate_empty_cells(case3, sizeof(case3) / sizeof(case3[0])) == 2);
}
