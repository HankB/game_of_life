/** Main for the program that supports Conway's Game of Life
 * 
 */
#include <unistd.h>

#include "life.hpp"

int main(int argdc, char** argv)
{
    //int case1[][2] = {{1, 0}, {1, 1}, {1, 2}}; // 3 cell cyclic
    int case1[][2] = {
        {5, 5},
        {7, 5},
        {5, 6},
        {7, 6},
        {6, 7},
        {9, 7},
        {4, 8},
        {6, 8},
        {8, 8},
        {3, 9},
        {5, 9},
        {6, 9},
        {7, 9},
        {6, 10},
        {5, 11},
        {7, 11},
        {5, 12},
        {7, 12},
        {5, 13},
        {6, 13},
        {7, 13},
    };
    Universe u = Universe(20, 20);

    for (uint i = 0; i < (sizeof case1/sizeof case1[0]); i++)
    {
        u.add_cell(case1[i][0], case1[i][1], live);
    }

    for(int i=0; i<30; i++) {
        u.evaluate_live_cells();
        u.evaluate_empty_neighbors();
        u.finish_generation();
        std::cout << "\033[2J" << u << std::endl;
        usleep(100000);
    }

}