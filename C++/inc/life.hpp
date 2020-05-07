#ifndef __LIFE_H_INCLUDED__
#define __LIFE_H_INCLUDED__
/* things used in Game of Life C++ implementation
*/

#include <list>
#include <iostream>

enum cell_state
{
    born,  // will be live, next iteration
    live,  // live at end of pevious iteration
    dying, // will die and be removed
};

class Universe;

class Cell
{
    int x;
    int y;
    cell_state state;
    Cell(void) {} // private to prevent default construction
public:
    int get_x(void) const { return x; }
    int get_y(void) const { return y; }
    Cell(int x, int y) : x(x), y(y), state(born) {}
    void vivify(void) { state = live; }
    void kill() { state = dying; }
    cell_state get_state(void) const { return state; }
    bool is_live(void) { return state == live || state == dying; }
    bool is_next_to(const Cell c) const { return abs(c.x - x) <= 1 && abs(c.y - y) <= 1; }
    friend Universe;
};

std::ostream& operator << (std::ostream & str, const Cell& c);

class Universe
{
    std::list<Cell> universe;

public:
    Universe(void) : universe() {}
    ~Universe(void) {}
    int cell_count(void) { return universe.size(); }
    int add_cell(int x, int y);
    void dump(void)
    {
        std::list<Cell>::iterator c;
        for (c = universe.begin(); c != universe.end(); c++)
            std::cout << (*c) << std::endl;
    }

};
#endif // __LIFE_H_INCLUDED__