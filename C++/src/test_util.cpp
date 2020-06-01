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

    TestCell case1[] = {{0, 0, live}, {0, 11, born}, {-1, 3, born}, {3, 3, dying}};
    /*
    |X
    |X 
     - */
    result = cout_Grid(case1, sizeof(case1) / sizeof(case1[0]));
    CHECK(result == "..........\n"
                    "..........\n"
                    "..........\n"
                    "..........\n"
                    "..........\n"
                    "..........\n"
                    "...x......\n"
                    "..........\n"
                    "..........\n"
                    "X.........\n");
}

std::string check_args(int argc, char const *argv[])
{
    program_options opt;
    std::stringstream buffer;

    if (options(argc, argv, opt))
    {
        buffer << opt.name << ","
               << opt.width << ","
               << opt.height << ","
               << opt.delay_ms << ","
               << opt.iteration_count;
        return buffer.str();
    }
    else
    {
        return std::string("unparseable");
    }
}

TEST_CASE("Command line args", "[cmdline/args]")
{
    char const *args[] = {"progname"};
    CHECK(check_args(sizeof args / sizeof args[0], args) == "xkcd,40,20,333,100");

    char const *args1[] = {"progname", "--demo", "rover"};
    CHECK(check_args(sizeof args1 / sizeof args1[0], args1) == "rover,40,20,333,100");

    char const *args2[] = {"progname", "-d", "glider"};
    CHECK(check_args(sizeof args2 / sizeof args2[0], args2) == "glider,40,20,333,100");

    char const *args3[] = {"progname", "--width", "60"};
    CHECK(check_args(sizeof args3 / sizeof args3[0], args3) == "xkcd,60,20,333,100");

    char const *args4[] = {"progname", "--width", "x"};
    CHECK(check_args(sizeof args4 / sizeof args4[0], args4) == "unparseable");

    char const *args5[] = {"progname", "--width=60"};
    CHECK(check_args(sizeof args5 / sizeof args5[0], args5) == "xkcd,60,20,333,100");

    char const *args6[] = {"progname", "-w", "60"};
    CHECK(check_args(sizeof args6 / sizeof args6[0], args6) == "xkcd,60,20,333,100");

    char const *args7[] = {"progname", "-w", "x"};
    CHECK(check_args(sizeof args7 / sizeof args7[0], args7) == "unparseable");

    char const *args8[] = {"progname", "-w80"};
    CHECK(check_args(sizeof args8 / sizeof args8[0], args8) == "xkcd,80,20,333,100");
}
