#include <stdlib.h>

typedef int bool;
#define TRUE  1
#define FALSE 0

typedef struct sol_bin
{
  int *items;
  int n;
  int size;
  int sum;
  int slack;
} bin_t;

void initialize_bin(bin_t *b, int b_size);
void free_bin(bin_t *b);
void add_item_to_bin(bin_t *b, int item);
int get_bin_slack(bin_t *b);
bool add_item_to_bin_if_fits(bin_t *b, int item);

typedef struct sol
{
  int n;
  int bin_size;
  bin_t *bins;
} sol_t;

void initialize_solution(sol_t *s, int b_size);
void add_new_bin(sol_t *s);
void free_solution(sol_t *s);
