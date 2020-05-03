/* things used in Game of Life C++ implementation
*/

enum  cell_state {
    live,           // live at end of pevious iteration
    born,           // will be live, next iteration
    dieing,         // will die and be removed
};

