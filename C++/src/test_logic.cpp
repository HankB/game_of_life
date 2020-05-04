#include <iostream>
#include <catch.hpp>

#include "life.hpp"

int construct_destroy_cell(void) 
{
    Cell    c;
    c.set_state(live);
    return c.get_state();
}

TEST_CASE( "constructor/destructor for cell", "[]" ) {
    REQUIRE( construct_destroy_cell() == live );
}