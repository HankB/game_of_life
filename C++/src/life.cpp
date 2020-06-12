/** Main for the program that supports Conway's Game of Life
 * 
 */
#include <unistd.h>
#include <ctime>
#include <sstream>

#include "life.hpp"

void output_results(const Universe &u, uint born, uint died)
{
    static uint iteration_count = -1;
    static time_t update_time = 0;
    static uint accumulate_born = 0;
    static uint accumulate_died = 0;
    static std::stringstream buffer; // for stats

    time_t time_now = time(0);
    accumulate_born += born;
    accumulate_died += died;
    iteration_count++;

    if (update_time != time_now) // update stats every second
    {
        buffer.clear();
        buffer.str("");
        buffer << iteration_count << " iterations "
               << u.cell_count() << " cells "
               << born << " born "
               << died << " died";
        update_time = time_now;
        accumulate_born = accumulate_died = 0;
    }
    std::cout << "\033[2J" << u << std::endl;
    std::cout << buffer.str() << std::endl;
}

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
            output_results(u, 0, 0); // display initial conditions
            if (load_demo(it, u))
            {
                if (opt.delay_ms > 0)
                    usleep(opt.delay_ms * 1000);
                for (uint i = 0;
                     opt.iteration_count == 0 || i < opt.iteration_count;
                     i++)
                {
                    u.evaluate_live_cells();
                    uint born = u.evaluate_empty_neighbors();
                    uint died = u.finish_generation();
                    //std::cout << "\033[2J" << u << std::endl;
                    output_results(u, born, died); // display initial conditions

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