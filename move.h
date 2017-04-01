#ifndef MOVE
#define MOVE

typedef struct move_s {
  node_t * item1; // item 1 to swap
  node_t * item2; // item 2 to swap
} swap_t;

typedef struct move_m {
  node_t *item1; // item to transfer in bin destination
  int index_bin; // bin destination
} transfer_t;


void performTransfMove(transfer_t *transf);
void performSwapMove(swap_t *transf);
void print_transfer_move(transfer_t *move);
void print_swap_move(swap_t *move);

#endif
