/**
 * File including the main() fuction for the Game of Life implementation.
 *
 * Current version is more or less set aside until functionality and unit 
 * tests are complete
 */
#include <stdbool.h>

#include "life.h"

int main( int argc, char** argv)
{
    bool * universe = get_universe(3);
    release_universe(universe);
}