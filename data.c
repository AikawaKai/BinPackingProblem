#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void load_dataset(char *filename, dataset *d_s)
{
  FILE *fp;
  char buff[255];
  int num_cases;
  char problem_identifier[255];
  char problem_header[255];
  int bin_size;
  int num_items;
  int best_solution;
  int tmp;

  // apertura del file
  printf("\nOpening File: %s\n", filename);
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    fprintf(stderr,"File %s could not be opened!\n", filename);
    exit(-1);
  }
  // numero di casi di test nel file
  fscanf(fp, "%s", buff);
  num_cases = atoi(buff);
  printf("Number of test cases : %d\n\n", num_cases);
  printf("######################\n\n");

  // nome del caso di test specifico
  fscanf(fp, "%s", buff);
  strcpy(problem_identifier, buff);
  printf("Problem string: %s\n", problem_identifier);

  // bin capacity del caso di test
  fscanf(fp, "%s", buff);
  bin_size = atoi(buff);
  printf("bin_size: %d\n", bin_size);

  // numero di oggetti del caso di test
  fscanf(fp, "%s", buff);
  num_items = atoi(buff);
  printf("Items number: %d\n", num_items);

  // miglior soluzione fino ad ora
  fscanf(fp, "%s", buff);
  best_solution = atoi(buff);
  printf("Best Solution: %d\n", best_solution);

  // carico tutti gli oggetti
  int items[num_items];
  for(int i=0; i<num_items; i++)
  {
    fscanf(fp, "%s", buff);
    tmp = atoi(buff);
    items[i] = tmp;
  }
  d_s->name = malloc(strlen(problem_identifier) * sizeof(d_s->name));
  strcpy(d_s->name, problem_identifier);
  d_s->bin_size = bin_size;
  d_s->best_sol = best_solution;
  d_s->n = num_items;
  d_s->items = malloc(num_items * sizeof(d_s->items));
  d_s->inserted = malloc(0 * sizeof(d_s->inserted));
  d_s->to_insert = malloc(num_items * sizeof(d_s->to_insert));
  for(int i=0; i<num_items; i++)
  {
    d_s->items[i] = items[i];
    d_s->to_insert[i] = d_s->items[i];
  }
  printf("Items Loading done.\n");
}

void free_dataset(dataset *d_s)
{
  // libero lo spazio occupato
  free(d_s->name);
  free(d_s->items);
  free(d_s->inserted);
  free(d_s->to_insert);
  d_s->n = 0;          
  d_s->bin_size = 0;
  d_s->best_sol = 0;
  printf("free(dataset) ok\n");
}
