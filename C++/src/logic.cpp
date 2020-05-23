/* core logic  (not already included in headers)
*/
#include "life.hpp"

int Universe::add_cell(int x, int y, cell_state st)
{
    universe.push_back(Cell(x, y, st));
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

uint Universe::count_live_neighbors(const Cell c) const
{
    uint count = 0;
    std::list<Cell>::const_iterator n;

    for (n = universe.begin(); n != universe.end(); n++)
        if (c.is_next_to(*n) && n->is_live())
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
        uint neighbor_count = count_live_neighbors(*c);

        if (neighbor_count <= 1 || neighbor_count >= 4)
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

    for (c = universe.begin(); c != universe.end(); c++) // for existing cells
    {
        int ix;
        int iy;

        for (ix = c->get_x() - 1; ix <= c->get_x() + 1; ix++) // for each live cell
        {
            for (iy = c->get_y() - 1; iy <= c->get_y() + 1; iy++)
            {
                if (!(ix == c->get_x() && iy == c->get_y()) && // not 'this' cell
                    find_cell(ix, iy) == universe.end())       // is not empty
                {
                    uint live_neighbor_count = count_live_neighbors(Cell(ix, iy));

                    if (live_neighbor_count == 3)
                    {
                        vivify_count++;
                        universe.insert(c, Cell(ix, iy));
                    }
                }
            }
        }
    }
    return vivify_count;
}

std::list<Cell>::const_iterator Universe::find_cell(int x, int y)
{
    std::list<Cell>::const_iterator c;

    for (c = universe.begin(); c != universe.end(); c++)
    {
        if (c->get_x() == x && c->get_y() == y)
            return c;
    }
    return c;
}
