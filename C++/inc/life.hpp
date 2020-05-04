/* things used in Game of Life C++ implementation
*/

enum  cell_state {
    live,           // live at end of pevious iteration
    born,           // will be live, next iteration
    dieing,         // will die and be removed
};

class Cell {
    cell_state      state;
public:
    void set_state(cell_state s) {state=s;}
    cell_state get_state(void) {return state;}
};

