/** test various utlity functions
 */

#include <string>
#include <sstream>
#include <catch.hpp>

#include "life.hpp"

std::string cout_Cell(const Cell c)
{
    //string s();
    std::stringstream buffer;
    buffer << c;
    return buffer.str();
}

TEST_CASE("Cell stream inserter", "[Cell/cout]")
{
    Cell c(3, 5);
    CHECK(cout_Cell(c) == "3 5:b");

    c = Cell(2, 1, live);
    CHECK(cout_Cell(c) == "2 1:l");
}

// setup for cell for further testing
typedef struct
{
    int x_coord;
    int y_coord;
    cell_state state;
} TestCell;

std::string cout_Grid(TestCell cells[], uint count)
{
    Universe u = Universe();
    std::stringstream buffer;

    for (uint i = 0; i < count; i++)
        u.add_cell(cells[i].x_coord, cells[i].y_coord, cells[i].state);

    buffer << u;

    return buffer.str();
}

TEST_CASE("Universe stream inserter", "[Universe/cout]")
{
    TestCell case0[] = {{0, 0, live}, {0, 1, born}};
    /*
    |X
    |X 
     - */
    std::string result = cout_Grid(case0, sizeof(case0) / sizeof(case0[0]));
    CHECK(result == "..........\n"
                    "..........\n"
                    "..........\n"
                    "..........\n"
                    "..........\n"
                    "..........\n"
                    "..........\n"
                    "..........\n"
                    "o.........\n"
                    "X.........\n");
}
