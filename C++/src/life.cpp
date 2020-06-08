/** Main for the program that supports Conway's Game of Life
 * 
 */
#include <unistd.h>

#include "life.hpp"

int main(int argdc, char **argv)
{
    Universe u = Universe(20, 20);
    std::vector<demo>::const_iterator it;
    it = find_demo("xkcd");
    if (load_demo(it, u))
    {
        for (int i = 0; i < 30; i++)
        {
            u.evaluate_live_cells();
            u.evaluate_empty_neighbors();
            u.finish_generation();
            std::cout << "\033[2J" << u << std::endl;
            usleep(100000);
        }
    }
    else
    {
        std::cout << "could not load demo" << std::endl;
    }
}