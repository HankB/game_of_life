#ifndef __LIFE_H_INCLUDED__
#define __LIFE_H_INCLUDED__
/* things used in Game of Life C++ implementation
*/

#include <list>
#include <iostream>

enum cell_state
{
    born = 'b',  // will be live, next iteration
    live = 'l',  // live at end of pevious iteration
    dying = 'd', // will die and be removed
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
    Cell(int x, int y, cell_state st = born) : x(x), y(y), state(st) {}
    void vivify(void) { state = live; }
    void kill(void) { state = dying; }
    cell_state get_state(void) const { return state; }
    bool is_live(void) const { return state == live || state == dying; }
    bool is_next_to(const Cell c) const;
    friend Universe;
};

std::ostream &operator<<(std::ostream &str, const Cell &c);

class Universe
{
    std::list<Cell> universe;

public:
    Universe(void) : universe() {}
    ~Universe(void) {}
    uint cell_count(void) { return universe.size(); }
    int add_cell(int x, int y, cell_state st = born);
    void dump(void) const;
    uint count_live_neighbors(const Cell c) const;
    uint evaluate_live_cells(void);
    uint evaluate_empty_neighbors(void);
    std::list<Cell>::const_iterator find_cell(int x, int y);
    std::list<Cell>::const_iterator end(void) const { return universe.end(); };
};
#endif // __LIFE_H_INCLUDED__
