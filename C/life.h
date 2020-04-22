/**
Header for functions shared between application and tests
*/

typedef struct {
    int row;
    int col;
} locus;

bool *get_universe(unsigned int dim);
void release_universe(bool* u); 
int init_universe(locus coordinates[]);
