#ifndef MOVE
#define MOVE

typedef struct move_s {
  node_t * item1;
  node_t * item2;
} swap_t;

typedef struct move_m {
  node_t *item1;
  int index_bin;
} transfer_t;

void print_transfer_move(transfer_t *move);
void print_swap_move(swap_t *move);

#endif
