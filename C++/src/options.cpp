/** Use getopts() to fetch long and short arguments
*/
#include <getopt.h>
#include <string>
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
            {"width", required_argument, 0, 0},
            {"height", required_argument, 0, 0},
            {"timing", required_argument, 0, 'c'},
            {"iterations", required_argument, 0, 0},
            {0, 0, 0, 0}};

        c = getopt_long(argc, (char **)argv, "d:w:", // "w:h:t:i:",
                        long_options, &option_index);
        std::cout << "getopt_long()" << c << std::endl;
        if (c == -1)
            break;
        try
        {
            switch (c)
            {
            case 0:
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");
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
                }
                case 2: //height
                    opts.height = std::stoi(optarg);
                    break;
                }
                break;

            case 'd':
                printf("option d with value '%s'\n", optarg);
                opts.name = std::string(optarg);
                break;

            case 'w':
                printf("option w with value '%s'\n", optarg);
                opts.width = std::stoi(optarg);
                break;

            case 'h':
                printf("option w with value '%s'\n", optarg);
                opts.width = std::stoi(optarg);
                break;

            case '?':
                printf("Usage ...\n");
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

    if (optind < argc)
    {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    return true;
}