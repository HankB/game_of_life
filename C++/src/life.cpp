/** Main for the program that supports Conway's Game of Life
 * 
 */
#include <unistd.h>

#include "life.hpp"

int main(int argc, char **argv)
{
    Universe u = Universe(20, 20);
    std::vector<demo>::const_iterator it;
    program_options opt;

    if (options(argc, (const char **)argv, opt))
    {
        std::string warning = std::string();
        if (validate_options(opt, warning))
        {
            it = find_demo(opt.name);
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
        else
        {
            std::cout << "problem validating args: " << warning << std::endl;
        }
        
    }
    else
    {
        std::cout << "Usage statement should be printed here" << std::endl;
        std::cout << "problem parsing args" << std::endl;
    }
}