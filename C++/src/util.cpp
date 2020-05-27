/* Uility functions (not core logic)
*/

#include "life.hpp"

#include <string>
#include <vector>

std::ostream &operator<<(std::ostream &str, const Cell &c)
{
    str << c.get_x() << " " << c.get_y() << ":" << char(c.get_state());
    return str;
}

static const char empty_cell = '.';
static const char born_cell = 'o';
static const char live_cell = 'X';
static const char dying_cell = 'x';

const char representation(cell_state st)
{
    switch (st)
    {
    case born:
        return born_cell;
    case live:
        return live_cell;
    case dying:
        return dying_cell;
    default:
        throw std::runtime_error("unknown state");
    }
}

// TODO:
// handle cells outside bounds
// variable bounds - from min/max cell coordinates.
std::ostream &operator<<(std::ostream &str, const Universe &u)
{
    std::vector<std::string> grid = std::vector<std::string>(u.dim_y());
    std::list<Cell>::const_iterator c;

    // init grid
    for (uint i = 0; i < u.dim_y(); i++)
        grid[i] = std::string(u.dim_x(), empty_cell);

    for (c = u.begin(); c != u.end(); c++)
    {
        if (c->get_x() >= u.origin_x() &&
            c->get_x() < u.origin_x() + int(u.dim_x()) &&
            c->get_y() >= u.origin_y() &&
            c->get_y() < u.origin_y() + int(u.dim_y()))
        {
            grid[u.dim_y() - 1 - c->get_y()][c->get_x()] = representation(c->get_state());
        }
    }

    for (uint i = 0; i < u.dim_y(); i++)
        str << grid[i] << std::endl;

    //std::cout << str <<
    return str;
}
