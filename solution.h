#include <stdlib.h>

typedef struct sol_bin
{
  int *items;
  int n;
  int size;
  int sum;
  int slack;
} bin;

void initialize_bin(bin *b, int size);
void add_item_to_bin(bin *b, int item);
