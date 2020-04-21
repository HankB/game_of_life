#include <stdbool.h>

#include "life.h"

int main( int argc, char** argv) {
    bool * universe = get_universe(3);
    release_universe(universe);
}