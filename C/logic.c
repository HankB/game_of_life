#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "life.h"

bool *get_universe(unsigned int dim)
{
    bool * universe = (bool *)malloc((sizeof (bool))*dim*dim);
    if(universe != NULL) {
        for( int i=0; i< dim*dim; i++) {
            universe[i] = false;
        }
    }

    return universe;
}


int init_universe(bool * universe, uint dim, const locus coordinates[])
{
    int     i = 0;

    while (coordinates[i].row >= 0 && coordinates[i].col >= 0) {
        //printf("%d [%d][%d]\n", i, coordinates[i].row, coordinates[i].col);
        if (coordinates[i].row >= dim || coordinates[i].col >= dim) {
            return -1;
        }
        universe[OFFSET(coordinates[i],dim)] = true;
        i++;
    }
    return 0;
}

/* Print the top line of the grid
*/
void print_top(uint width, char * buffer, size_t buffer_len)
{
    int print_len = width*2+1;
    
    if(print_len+1 > buffer_len) {
        print_len = buffer_len-1;
    }
    //memset(void *s, int c, size_t n);
    memset(buffer, '_', print_len);
    buffer[print_len] = '\0';     
}

void release_universe(bool* u)
{
    free(u);
}
