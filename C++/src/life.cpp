/** Main for the program that supports Conway's Game of Life
 * 
 */
#include <unistd.h>

#include "life.hpp"

int main(int argdc, char** argv)
{
    int case1[][2] = {{1, 0}, {1, 1}, {1, 2}};
    Universe u = Universe();

    for (uint i = 0; i < (sizeof case1/sizeof case1[0]); i++)
    {
        u.add_cell(case1[i][0], case1[i][1], live);
    }

    for(int i=0; i<10; i++) {
        u.evaluate_live_cells();
        u.evaluate_empty_neighbors();
        u.finish_generation();
        std::cout << u << std::endl;
        sleep(1);
    }

}