#ifndef VNS
#define VNS

void VNSmethod(dataset_t *d_s, sol_t *starting_sol, int k_max);
node_t *getZFromSolution(dataset_t *d_s, sol_t *starting_sol);
sol_t * shakingSolution(dataset_t *d_s, sol_t *starting_sol,  node_t *Z, int k_curr);
int operationPermitted(node_t *curr_node, node_t *z_val);

#endif
