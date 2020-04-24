/**
Header for functions shared between application and tests
*/

typedef struct {
    int row;
    int col;
} locus;

// calculate offset into universe
#define OFFSET(loc,dim) (loc.row*dim + loc.col)

bool *get_universe(unsigned int dim);
void release_universe(bool* u); 
int init_universe(bool * universe, uint dim, const locus coordinates[]);
void print_top(uint width, char * buffer, size_t buffer_len);
void print_line(uint width, uint row, char * buffer, size_t buffer_len, bool * universe);
