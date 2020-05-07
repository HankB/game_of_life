/* core logic  (not already included in headers)
*/
#include "life.hpp"

int Universe::add_cell(int x, int y)
{
    universe.push_back(Cell(x, y));
    return cell_count();
}

bool Cell::is_next_to(const Cell c) const
{
    if (c.x == x && c.y == y)
        return false;
    else
        return (abs(c.x - x) <= 1 && abs(c.y - y) <= 1);
}

void Universe::dump(void) const
{
    std::list<Cell>::const_iterator c;
    for (c = universe.begin(); c != universe.end(); c++)
        std::cout << (*c) << std::endl;
}

uint Universe::count_neighbors(const Cell c) const
{
    uint count = 0;
    std::list<Cell>::const_iterator n;

    for (n = universe.begin(); n != universe.end(); n++)
        if (c.is_next_to(*n))
            count++;

    return count;
}
