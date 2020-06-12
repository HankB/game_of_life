/** Main for the program that supports Conway's Game of Life
 * 
 */
#include <unistd.h>

#include "life.hpp"

int main(int argc, char **argv)
{
    std::vector<demo>::const_iterator it;
    program_options opt;

    if (options(argc, (const char **)argv, opt))
    {
        std::string warning = std::string();
        if (validate_options(opt, warning))
        {
            it = find_demo(opt.name);
            Universe u = Universe(opt.width, opt.height);
            if (load_demo(it, u))
            {
                std::cout << "\033[2J" << u << std::endl; // display initial conditions
                if (opt.delay_ms > 0)
                    usleep(opt.delay_ms * 1000);
                for (uint i = 0; opt.iteration_count == 0 || i < opt.iteration_count; i++)
                {
                    u.evaluate_live_cells();
                    u.evaluate_empty_neighbors();
                    u.finish_generation();
                    std::cout << "\033[2J" << u << std::endl;
                    if (opt.delay_ms > 0)
                        usleep(opt.delay_ms * 1000);
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