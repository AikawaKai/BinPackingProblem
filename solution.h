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
void free_bin(bin *b);
void add_item_to_bin(bin *b, int item);
int get_bin_slack(bin *b);

typedef struct sol
{
  int n;
  bin *bins;
} sol;

void initialize_solution(sol *s);
void free_solution(sol *s);
