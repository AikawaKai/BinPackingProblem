#ifndef VNS
#define VNS
#include "move.h"

sol_t* VNSmethod(dataset_t *d_s, sol_t *starting_sol, int k_max);
node_t *getZFromSolution(dataset_t *d_s, sol_t *starting_sol);
int getZbinNotFullFromSolution(node_t *items, sol_t *starting_sol, int *bins_not_full, int *num_bin);
void shakingSolution(dataset_t *d_s, sol_t *starting_sol,  node_t *Z, int k_curr);
void localSearch(dataset_t *d_s, sol_t *curr_sol);
int fillArrayTransferWithMoves(int *num_transf, node_t *curr_node, transfer_t *list_transfers, bin_t *bin, int j);
int fillArraySwapWithMoves(int *num_swap, node_t *curr_node, node_t *curr_node_j, swap_t *list_swaps, bin_t *bins);
float getAndPerformBestMove(bin_t *bins, node_t *Z, sol_t *solution, int num_el, int *bins_not_full, int num_bin_not_full);

#endif
