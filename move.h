
typedef struct item {
  int bin_index;
  int item_index_bin;
  float val;
} item_t;


typedef struct move_s {
  item_t * item1;
  item_t * item2;
} swap_t;

typedef struct move_m {
  item_t *item1;
  int index_bin;
} transfer_t;
