#ifndef SOLUTION
#define SOLUTION

#include <stdlib.h>

typedef int bool;
#define TRUE  1
#define FALSE 0

typedef struct sol_bin
{
  float *items;
  int n;
  float size;
  float sum;
  float slack;
} bin_t;

void initialize_bin(bin_t *b, float b_size, int num_items);
void free_bin(bin_t *b);
void add_item_to_bin(bin_t *b, float item);
int get_bin_slack(bin_t *b);
bool add_item_to_bin_if_fits(bin_t *b, float item);
void print_bin(bin_t *bin);

typedef struct sol
{
  int n;
  float bin_size;
  int max_num_el;
  bin_t *bins;
} sol_t;

void initialize_solution(sol_t *s, float b_size, int num_item, int max_num_el);
void add_new_bin(sol_t *s);
void free_solution(sol_t *s);
void print_solution(sol_t *s);

#endif
