#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "life.h"

bool *get_universe(unsigned int dim) {
    return (bool *)malloc((sizeof (bool))*dim*dim);
}

void release_universe(bool* u) {
    free(u);
}

int main( int argc, char** argv) {
    printf("hello life\n");
    bool * universe = get_universe(3);
    release_universe(universe);
}