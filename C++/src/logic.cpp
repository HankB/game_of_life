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
        if (neighbor_count <= 1 || neighbor_count >= 4)
            (*c).kill();
        else
            live_count++;
    }
    return live_count;
}

#if defined SET_ASIDE
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
        std::cout << "checking " << (*c) << std::endl;
        for (ix = c->get_x() - 1; ix <= c->get_x() + 1; ix++) // for each live cell
        {
            for (iy = c->get_y() - 1; iy <= c->get_y() + 1; iy++)
            {
                uint live_neighbor_count = 0;
                std::cout << "neighbors for " << ix << " " << iy << std::endl;

                for (int check_x = ix - 1; check_x <= ix + 1; check_x++) // for cells surrounding each cell
                {
                    for (int check_y = iy - 1; check_y <= iy + 1; check_y++) 
                    {
                        if (!(check_x == ix && check_y == iy))
                        {
                            if (find_cell(check_x, check_y) == universe.end()) // empty cell
                            {
                                std::list<Cell>::const_iterator neighbor = find_cell(ix, iy);
                                if (neighbor != end())
                                {
                                    live_neighbor_count++;
                                }
                                std::cout << check_x << " " << check_y << " " << live_neighbor_count << std::endl;
                            }
                        } // not this cell
                    }
                }
                if (live_neighbor_count == 3)
                {
                    vivify_count++;
                    universe.insert(c, Cell(ix, iy));
                    // add cell to list here
                }
            }
        }
    }
    return vivify_count;
}
#endif

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
