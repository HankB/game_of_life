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
uint print_top(uint width, char * buffer, size_t buffer_len)
{
    uint print_len = width*2+2;  // length of string, null terminator not included
    
    if(print_len+1 > buffer_len) {
        print_len = buffer_len-1;
    }

    memset(buffer, '_', print_len);
    buffer[print_len-1] = '\n';     
    buffer[print_len] = '\0';
    return print_len;
}

/* Print the a given line of the grid
*/
uint print_line(uint width, uint row, char * buffer, size_t buffer_len, bool * universe)
{
    int     print_width = width;        // actual number of cells to print
    uint    print_len = print_width*2+2;  // length of string, null terminator not included
    uint    i;
    locus   l = {0, row,};

    // prevent buffer overrun
    while(print_len > buffer_len) {
        print_width--;
        print_len = print_width*2+2;
    }

    if(print_width <= 0) {
        return 0;
    }

    buffer[0] = '|';

    for(i=0; i<print_width; i++) {
        l.col = i;
        buffer[1+2*i] = universe[OFFSET(l,width)]?'X':'_';
        buffer[2+2*i] = '|';
        //buffer[3+2*i] = '\0';
    }
    
    buffer[print_len-1] = '\n';
    buffer[print_len] = '\0';

    return print_len;
}

/* print all lines of the grid
*/
uint print_universe(uint width, char * buffer, size_t buffer_len, bool * universe)
{
    uint    buff_next = 0;              // index of next byte in output buffer

    buff_next = print_top(width, buffer, buffer_len);

    for(uint i=0; i<width; i++) {
        if(buff_next < buffer_len-1) {
            buff_next += 
                print_line(width, i, buffer+buff_next, buffer_len-buff_next-1, universe);
        }
    }

    return buff_next;
} 

/* Implicitly count live neighbors
* 
* gets sticky with edge and corner cases. But there are precisely
* eight neighbors to check. Longest possible loop is 3 so just
* dispense with that and examine each neighbor individually 
*/
uint count_neighbors(const bool * const universe, locus l, uint width)
{
    uint    count=0;

    // upper left
    if(l.col > 0 && l.row > 0 &&
        universe[OFFSET_COORD(l.col-1, l.row-1,width)] == true )
        count++;
    // upper
    if(l.row > 0 &&
        universe[OFFSET_COORD(l.col, l.row-1,width)] == true )
        count++;
    // upper right
    if(l.col < width-1 && l.row > 0 &&
        universe[OFFSET_COORD(l.col+1, l.row-1,width)] == true )
        count++;
    // left
    if(l.col > 0  &&
        universe[OFFSET_COORD(l.col-1, l.row,width)] == true )
        count++;
    // right
    if(l.col < width-1  &&
        universe[OFFSET_COORD(l.col+1, l.row,width)] == true )
        count++;
    // lower left
    if(l.col > 0 && l.row < width-1 &&
        universe[OFFSET_COORD(l.col-1, l.row+1,width)] == true )
        count++;
    // lower
    if(l.row < width-1 &&
        universe[OFFSET_COORD(l.col, l.row+1,width)] == true )
        count++;
    // lower right
    if(l.col < width-1 && l.row < width-1 &&
        universe[OFFSET_COORD(l.col+1, l.row+1,width)] == true )
        count++;
    return count;
}

void release_universe(bool* u)
{
    free(u);
}
