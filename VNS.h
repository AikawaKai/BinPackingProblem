#ifndef VNS
#define VNS

void VNSmethod(dataset_t *d_s, sol_t *starting_sol, int k_max);
node_t *getZFromSolution(dataset_t *d_s, sol_t *starting_sol);
sol_t * shakingSolution(sol_t *starting_sol,  node_t **Z, int k_curr);

#endif
