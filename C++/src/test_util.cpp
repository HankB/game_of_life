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

    char const *args9[] = {"progname", "--height", "60"};
    CHECK(check_args(sizeof args9 / sizeof args9[0], args9) == "xkcd,40,60,333,100");

    char const *argsA[] = {"progname", "-h", "30"};
    CHECK(check_args(sizeof argsA / sizeof argsA[0], argsA) == "xkcd,40,30,333,100");

    char const *argsB[] = {"progname", "-y", "35"};
    CHECK(check_args(sizeof argsB / sizeof argsB[0], argsB) == "unparseable");

    char const *argsC[] = {"progname", "--timing", "250"};
    CHECK(check_args(sizeof argsC / sizeof argsC[0], argsC) == "xkcd,40,20,250,100");

    char const *argsD[] = {"progname", "-t", "150"};
    CHECK(check_args(sizeof argsD / sizeof argsD[0], argsD) == "xkcd,40,20,150,100");

    char const *argsE[] = {"progname", "--iterations", "250"};
    CHECK(check_args(sizeof argsE / sizeof argsE[0], argsE) == "xkcd,40,20,333,250");

    char const *argsF[] = {"progname", "-i", "150"};
    CHECK(check_args(sizeof argsF / sizeof argsF[0], argsF) == "xkcd,40,20,333,150");

    // max uint? 18446744073709551615
    char const *argsG[] = {"progname", "-i", "2147483647"};
    CHECK(check_args(sizeof argsG / sizeof argsG[0], argsG) == "xkcd,40,20,333,2147483647");

}

/** Check validation of cmd line arguments
 * process the arguments, compare the message (if options() returns false)
 * and return the status returned by options()
 */
bool check_validation(int argc, char const *argv[], std::string msg)
{
    program_options opt;
    std::string warning = std::string();
    bool rc;

    REQUIRE(options(argc, argv, opt)); // parse args
    rc = validate_options(opt, warning);
    if (!rc)
        CHECK(warning == msg);

    return rc;
}

TEST_CASE("Validate command args", "[cmdline/validate]")
{

    // no args
    char const *args[] = {"progname"};
    REQUIRE(check_validation(sizeof args / sizeof args[0], args,
                             std::string()) == true);

    // width
    char const *args1[] = {"progname", "-w", "4"};
    REQUIRE(check_validation(sizeof args1 / sizeof args1[0], args1,
                             std::string("5 <= width <= 200")) == false);

    char const *args2[] = {"progname", "-w", "5"};
    REQUIRE(check_validation(sizeof args2 / sizeof args2[0], args2,
                             std::string()) == true);

    char const *args3[] = {"progname", "-w", "200"};
    REQUIRE(check_validation(sizeof args3 / sizeof args3[0], args3,
                             std::string()) == true);

    char const *args4[] = {"progname", "-w", "-1"};
    REQUIRE(check_validation(sizeof args4 / sizeof args4[0], args4,
                             std::string("5 <= width <= 200")) == false);

    char const *args5[] = {"progname", "-w", "201"};
    REQUIRE(check_validation(sizeof args5 / sizeof args5[0], args5,
                             std::string("5 <= width <= 200")) == false);

    // height
    char const *args7[] = {"progname", "-h", "4"};
    REQUIRE(check_validation(sizeof args7 / sizeof args7[0], args7,
                             std::string("5 <= height <= 200")) == false);

    char const *args8[] = {"progname", "-h", "5"};
    REQUIRE(check_validation(sizeof args8 / sizeof args8[0], args8,
                             std::string()) == true);

    char const *args9[] = {"progname", "-h", "200"};
    REQUIRE(check_validation(sizeof args9 / sizeof args9[0], args9,
                             std::string()) == true);

    char const *argsA[] = {"progname", "-h", "-1"};
    REQUIRE(check_validation(sizeof argsA / sizeof argsA[0], argsA,
                             std::string("5 <= height <= 200")) == false);

    char const *argsB[] = {"progname", "-h", "201"};
    REQUIRE(check_validation(sizeof argsB / sizeof argsB[0], argsB,
                             std::string("5 <= height <= 200")) == false);

    // timing
    char const *argsC[] = {"progname", "-t", "-1"};
    REQUIRE(check_validation(sizeof argsC / sizeof argsC[0], argsC,
                             std::string("0 <= timing <= 20000")) == false);

    char const *argsD[] = {"progname", "-t", "0"};
    REQUIRE(check_validation(sizeof argsD / sizeof argsD[0], argsD,
                             std::string()) == true);

    char const *argsE[] = {"progname", "-t", "20000"};
    REQUIRE(check_validation(sizeof argsE / sizeof argsE[0], argsE,
                             std::string()) == true);

    char const *argsF[] = {"progname", "-t", "20001"};
    REQUIRE(check_validation(sizeof argsF / sizeof argsF[0], argsF,
                             std::string("0 <= timing <= 20000")) == false);

    // iterations

}
