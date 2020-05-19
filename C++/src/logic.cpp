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

/* Evaluate all live cells in the grid. Count live neighbors and determine 
* if the cell lives or dies.
*  Return the number of remaining live cells
*/

uint Universe::evaluate_live_cells(void)
{
    std::list<Cell>::iterator c;
    uint live_count = 0;

    for (c = universe.begin(); c != universe.end(); c++)
    {
        uint neighbor_count = count_neighbors(*c);
        //std::cout << std::endl << (*c) << " count >" << neighbor_count << std::endl;
        if(neighbor_count <= 1 || neighbor_count >= 4)
            (*c).kill();
        else
            live_count++;
    }
    return live_count;
}

/* Evaluate all empty cells next to live cells in the grid. 
* 1) count live neighbors and determine if the cell should come
* alive.
*  Return the number of newly live cells.
*/

uint Universe::evaluate_empty_neighbors(void)
{
    std::list<Cell>::iterator c;
    uint vivify_count = 0;

    for (c = universe.begin(); c != universe.end(); c++)
    {
        // really need a find_cell() member function here.
    }
    return vivify_count;
}
