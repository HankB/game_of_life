#ifndef __LIFE_H_INCLUDED__
#define __LIFE_H_INCLUDED__
/* things used in Game of Life C++ implementation
*/

#include <list>
#include <vector>
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
    int grid_origin_x;
    int grid_origin_y;
    uint grid_dim_x;
    uint grid_dim_y;
    static const uint default_dim_x = 10;
    static const uint default_dim_y = 10;

public:
    Universe(uint x_dim = default_dim_x, uint y_dim = default_dim_y) : universe(),
                                                                       grid_origin_x(0),
                                                                       grid_origin_y(0),
                                                                       grid_dim_x(x_dim),
                                                                       grid_dim_y(y_dim)
    {
    }
    int origin_x(void) const { return grid_origin_x; }
    int origin_y(void) const { return grid_origin_y; }
    uint dim_x(void) const { return grid_dim_x; }
    uint dim_y(void) const { return grid_dim_y; }
    ~Universe(void) {}
    uint cell_count(void) { return universe.size(); }
    int add_cell(int x, int y, cell_state st = born);
    void dump(void) const;
    uint count_live_neighbors(const Cell c) const;
    uint evaluate_live_cells(void);
    uint evaluate_empty_neighbors(void);
    uint finish_generation(void);
    std::list<Cell>::const_iterator find_cell(int x, int y);
    std::list<Cell>::const_iterator begin(void) const { return universe.begin(); };
    std::list<Cell>::const_iterator end(void) const { return universe.end(); };
};

std::ostream &operator<<(std::ostream &str, const Universe &c);

// encapsulate data to init the universe, identified by name.
typedef struct
{
    uint count;       // number of points
    std::string name; // name of pattern
    char point[][3];  // coordiunates of live points
} pattern;

// encapsulate program options to be set in options()
typedef struct
{
    std::string name;     // starting pattern
    uint width;           // dimensions of grid
    uint height;          //
    uint delay_ms;        // delay between generations
    uint iteration_count; // number of iterations to perform
} program_options;

bool options(int argc, char const *argv[], program_options &opts);
bool validate_options(program_options &opt, std::string &msg);

// limits for program options
static const int min_width = 5;
static const int max_width = 200;

static const int min_height = 5;
static const int max_height = 200;

static const int min_delay_ms = 0;
static const int max_delay_ms = 20000;

// struct and fuinctions to support predefined (demo)
// patterns

typedef struct
{
    std::string name;
    std::vector<Cell> cells;
} demo;

std::vector<std::string> available_demos(void);

#endif // __LIFE_H_INCLUDED__
