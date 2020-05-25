/** test various utlity functions
 */

#include <string>
#include <sstream>
#include <catch.hpp>

#include "life.hpp"

using namespace std;

string cout_Cell(const Cell c)
{
    //string s();
    stringstream buffer;
    buffer << c;
    return buffer.str();
}

TEST_CASE("Cell stream inserter", "[Cell/cout]")
{
    Cell c(3, 5);
    CHECK(cout_Cell(c) == "3 5:b");
}
