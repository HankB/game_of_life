/**
Header for functions shared between application and tests
*/

typedef struct {
    int col;
    int row;
} locus;

// calculate offset into universe from locus and dimension
#define OFFSET(loc,dim) (loc.row*dim + loc.col)
#define OFFSET_COORD(col,row,dim) ((row)*(dim) + (col))

bool *get_universe(unsigned int dim);
void release_universe(bool* u); 
int init_universe(bool * universe, uint dim, const locus coordinates[]);
uint print_top(uint width, char * buffer, size_t buffer_len);
uint print_line(uint width, uint row, char * buffer, size_t buffer_len, bool * universe);
uint print_universe(uint width, char * buffer, size_t buffer_len, bool * universe);
uint count_neighbors(const bool * const universe, locus l, uint width);
int calc_next_gen(const bool * const u_in, bool * u_out, uint width );
