/** data for various demo patterns to start a run
 */

#include <vector>
#include <string>
#include <algorithm>

#include "life.hpp"

std::vector<demo> examples = {
    {
        "xkcd",
        std::vector<Cell>{
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
        },
    },
    {
        "glider",
        std::vector<Cell>{
            {2, 1},
            {3, 2},
            {1, 3},
            {2, 3},
            {3, 3},
        },
    },
    {
        "exploder",
        std::vector<Cell>{
            {14, 13},
            {13, 14},
            {14, 14},
            {15, 14},
            {13, 15},
            {15, 15},
            {14, 16}},
    },
    {
        "cyclic_3",
        std::vector<Cell>{
            {1, 0},
            {1, 1},
            {1, 2},
        },
    },
};

const std::vector<std::string> available_demos(void)
{
    std::vector<std::string> names;
    std::transform(examples.begin(), examples.end(), std::back_inserter(names),
                   [](demo const &p) -> std::string { return p.name; });

    return names;
}

std::vector<demo>::const_iterator find_demo(const std::string n)
{
    /*bool is_demo
    std::vector<demo>::const_iterator it = std::find_if;
    */
    std::vector<demo>::const_iterator it;
    it = find_if(examples.begin(), examples.end(),
                 [&n](const demo &obj) { return obj.name == n; });
    return it;
}

bool is_found(std::vector<demo>::const_iterator &it)
{
    return it != examples.end();
}

bool load_demo(std::vector<demo>::const_iterator it, Universe u)
{
    if (is_found(it))
    {
        std::vector<Cell>::const_iterator cell;
        for (cell = it->cells.begin(); cell != it->cells.end(); cell++)
            u.add_cell(cell->get_x(), cell->get_y(), live);
        return true;
    }
    else
    {
        return false;
    }
}