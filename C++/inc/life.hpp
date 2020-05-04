#ifndef __LIFE_H_INCLUDED__
#define __LIFE_H_INCLUDED__
/* things used in Game of Life C++ implementation
*/

enum cell_state
{
    born,  // will be live, next iteration
    live,  // live at end of pevious iteration
    dying, // will die and be removed
};

class Cell
{
    int x;
    int y;
    cell_state state;
    Cell(void) {} // private to prevent default construction
public:
    Cell(int x, int y) : x(x), y(y), state(born) {}
    void vivify(void) { state = live; }
    void kill() { state = dying; }
    cell_state get_state(void) { return state; }
    bool is_live(void) { return state == live || state == dying; }
    bool is_next_to(const Cell c) const { return abs(c.x - x) <= 1 && abs(c.y - y) <= 1; }
};

#endif // __LIFE_H_INCLUDED__