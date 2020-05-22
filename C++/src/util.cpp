/* Uility functions (not core logic)
*/

#include "life.hpp"

std::ostream &operator<<(std::ostream &str, const Cell &c)
{
    str << c.get_x() << " " << c.get_y() << ":" << char(c.get_state());
    return str;
}
