/* core logic  (not already included in headers)
*/
#include "life.hpp"

int Universe::add_cell(int x, int y)
{
    universe.push_back(Cell(x, y));
    return cell_count();
}
