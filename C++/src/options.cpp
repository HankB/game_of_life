/** Use getopts() to fetch long and short arguments
*/
#include <getopt.h>
#include <string>
#include <sstream>
#include <cstring>

#include "life.hpp"

/** set defaults and unpack command line args
 * return true if no problems with inputs are detected.
 */
bool options(int argc, char const *argv[], program_options &opts)
{
    int c;
    // int digit_optind = 0;

    optind = 1; // force getopts_long to restart scanning vector

    // provide defaults
    opts.name = std::string("xkcd");
    opts.width = 40,
    opts.height = 20;
    opts.delay_ms = 333;
    opts.iteration_count = 100;

    while (1)
    {
        //int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"demo", required_argument, 0, 0},
            {"width", required_argument, 0, 'w'},
            {"height", required_argument, 0, 'h'},
            {"timing", required_argument, 0, 't'},
            {"iterations", required_argument, 0, 'i'},
            {0, 0, 0, 0}};

        c = getopt_long(argc, (char **)argv, "d:w:h:t:i:", // "w:h:t:i:",
                        long_options, &option_index);
        //std::cout << "getopt_long()" << c << std::endl;
        if (c == -1)
            break;
        try
        {
            switch (c)
            {
            case 0:
                /*
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");
                */
                // WARNING:
                // 'option_index' depends on order of elements in long_options[]
                switch (option_index)
                {
                case 0: //demo
                    opts.name = std::string(optarg);
                    break;
                case 1: //width
                    opts.width = std::stoi(optarg);
                    break;
                case 2: //height
                    opts.height = std::stoi(optarg);
                    break;
                case 3: //timing AKA delay_ms
                    opts.delay_ms = std::stoi(optarg);
                    break;
                case 4: //iterations
                    opts.iteration_count = std::stoi(optarg);
                    break;
                }
                break;

            case 'd': //demo
                //printf("option d with value '%s'\n", optarg);
                opts.name = std::string(optarg);
                break;

            case 'w': //width
                //printf("option w with value '%s'\n", optarg);
                opts.width = std::stoi(optarg);
                break;

            case 'h': //height
                //printf("option h with value '%s'\n", optarg);
                opts.height = std::stoi(optarg);
                break;

            case 't': //timing AKA delay_ms
                //printf("option h with value '%s'\n", optarg);
                opts.delay_ms = std::stoi(optarg);
                break;

            case 'i': //iterations
                //printf("option h with value '%s'\n", optarg);
                opts.iteration_count = std::stoi(optarg);
                break;

            case '?':
                //printf("Usage ...\n");
                return false;
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
                break;
            }
        }
        catch (...)
        {
            return false;
        }
    }

    /* do we care?
    if (optind < argc)
    {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }
*/
    return true;
}

/** Validate command line options. Return true if all OK or false if not
 * and stuff a message in `msg` to hilp identify the problem.
 */
bool validate_options(program_options &opt, std::string &msg)
{
    std::stringstream buffer;

    if (opt.width < min_width || opt.width > max_width)
    {
        buffer << min_width << " <= width <= " << max_width;
        msg = buffer.str();
        return false;
    }

    if (opt.height < min_height || opt.height > max_height)
    {
        buffer << min_height << " <= height <= " << max_height;
        msg = buffer.str();
        return false;
    }

    return true;
}