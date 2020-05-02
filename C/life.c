/**
 * File including the main() fuction for the Game of Life implementation.
 *
 * Present version has a hard coded time delay between generations (ts)
 * Initial patterns are a glider that collides with an exploder and
 * eventually reaches a stable (cyclic) state.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "life.h"

int main( int argc, char** argv)
{
    static const uint width = 30;
    static const size_t buf_len = (width+1)*(width+1)*2+3;
    char buffer[buf_len];
    bool * u1 = get_universe(width);
    bool * u2 = get_universe(width);
    bool flip = false;
    struct timespec ts;

    ts.tv_sec = 0;
    ts.tv_nsec = 100 * 1000000;

    locus glider[] = {
        {2,1},
        {3,2},
        {1,3},
        {2,3},
        {3,3},
        {-1,-1},
    };

    locus exploder[] = {
        {14, 13},
        {13, 14},
        {14, 14},
        {15, 14},
        {13, 15},
        {15, 15},
        {14, 16},
        {-1,-1},
    };

    init_universe(u1, width, exploder);
    init_universe(u1, width, glider);

    print_universe(width, buffer, buf_len, u1);
    printf("%s\n", buffer);

    for(int i=0; i<100; i++) {
        calc_next_gen(flip?u2:u1, flip?u1:u2, width );
        print_universe(width, buffer, buf_len, flip?u1:u2);
        printf("\033[2J");
        printf("%s\n", buffer);
        flip = !flip;
          
        nanosleep(&ts, &ts);
    }

    release_universe(u1);
}