#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "life.h"

bool *get_universe(unsigned int dim)
{
    bool * universe = (bool *)malloc((sizeof (bool))*dim*dim);
    if(universe != NULL) {
        for( int i=0; i< dim*dim; i++) {
            universe[i] = false;
        }


int init_universe(locus coordinates[])
{
    int     i = 0;

    while (coordinates[i].row != -1) {
        printf("%d [%d][%d]\n", i, coordinates[i].row, coordinates[i].col);
        i++;
    }
    return 0;
}

void release_universe(bool* u)
{
    free(u);
}
