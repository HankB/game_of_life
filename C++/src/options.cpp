/** Use getopts() to fetch long and short arguments
*/
#include <getopt.h>
#include <string>

#include "life.hpp"

/** set defaults and unpack command line args
 * return true if no problems with inputs are detected
 */
bool options(int argc, const char **argv, program_options &opts)
{
    // provide defaults
    opts.name = std::string("xkcd");
    opts.width = 40,
    opts.height = 20;
    opts.delay_ms = 333;
    opts.iteration_count = 100;

    return true;
}