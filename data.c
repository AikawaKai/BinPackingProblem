#include "data.h"
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funzione di comparazione per l'ordinamento
int compare_function(const void* p1, const void* p2)
{
   float i1 = *(float*) p1;
   float i2 = *(float*) p2;
   if (i1 > i2) return -1;
   else if (i1 == i2) return 0;
   else return 1;
   /* or simply: return i1 - i2; */
 }

// funzione per caricare il dataset
void load_dataset(char *filename, dataset_t *d_s)
{
  node_t *tmpN;
  node_t *prec;
  FILE *fp;
  char buff[255];
  int num_cases;
  char *problem_identifier;
  float *sorteditems;
  float bin_size;
  int num_items;
  int best_solution;
  float tmp;

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
  problem_identifier = (char *)calloc(strlen(buff)+1, sizeof(char));
  strcpy(problem_identifier, buff);
  printf("Identifier: %s\n", problem_identifier);
  d_s->name = problem_identifier;

  // bin capacity del caso di test
  fscanf(fp, "%s", buff);
  bin_size = atof(buff);
  printf("bin_size: %f\n", bin_size);

  // numero di oggetti del caso di test
  fscanf(fp, "%s", buff);
  num_items = atoi(buff);
  printf("Items number: %d\n", num_items);

  // miglior soluzione fino ad ora
  fscanf(fp, "%s", buff);
  best_solution = atoi(buff);
  printf("Best Solution: %d\n", best_solution);

  // creo la lista di oggetti non ordinata
  d_s->items = (float *)calloc(num_items, sizeof(float));
  if(d_s->items == NULL)
  {
    printf("MALLOC FAILED load_dataset\n");
    exit(-1);
  }
  for(int i=0; i<num_items; i++)
  {
    fscanf(fp, "%s", buff);
    tmp = atof(buff);
    d_s->items[i] = tmp;
  }
  d_s->bin_size = bin_size;
  d_s->best_sol = best_solution;
  d_s->n = num_items;

  // creo la lista ordinata di oggetti
  sorteditems = (float *)calloc(num_items, sizeof(float));
  if(sorteditems == NULL)
  {
    printf("MALLOC FAILED load_dataset\n");
    exit(-1);
  }
  for(int i=0; i<num_items; i++)
  {
    sorteditems[i] = d_s->items[i];
  }
  qsort(sorteditems,num_items, sizeof(float), compare_function);
  d_s->sorteditems = sorteditems;

  // creo la lista linkata di oggetti
  d_s->head = malloc(sizeof(node_t));
  tmpN = malloc(sizeof(node_t));
  d_s->head->val = sorteditems[0];
  d_s->head->id = 0;
  d_s->head->next = tmpN;
  for(int i=1; i<num_items; i++)
  {
    tmpN->val = sorteditems[i];
    tmpN->id = i;
    prec = tmpN;
    tmpN = malloc(sizeof(node_t));
    prec->next = tmpN;
  }
  prec->next = NULL;
  free(tmpN);
  printf("Items Loading done.\n\n");
}

// funzione per liberare l'area di memoria occupata dalla struttura dati del dataset
void free_dataset(dataset_t *d_s)
{
  // libero lo spazio occupato
  free(d_s->name);
  free(d_s->items);
  free(d_s->sorteditems);
  d_s->items = NULL;
  d_s->n = 0;
  d_s->bin_size = 0;
  d_s->best_sol = 0;
  free_list(d_s->head);
  printf("free(dataset) ok\n");
}

// carica il dataset da un filepointer in input
void load_dataset_from_file_pointer(FILE *fp, dataset_t *d_s)
{
  char buff[255];
  char *problem_identifier;
  float *sorteditems;
  float bin_size;
  int num_items;
  int best_solution;
  float tmp;

  node_t *tmpN;
  node_t *prec;
  
  // nome del caso di test specifico
  fscanf(fp, "%s", buff);
  problem_identifier = (char *)calloc(strlen(buff)+1, sizeof(char));
  strcpy(problem_identifier, buff);
  printf("Identifier: %s\n", problem_identifier);
  d_s->name = problem_identifier;

  // bin capacity del caso di test
  fscanf(fp, "%s", buff);
  bin_size = atof(buff);
  printf("bin_size: %f\n", bin_size);

  // numero di oggetti del caso di test
  fscanf(fp, "%s", buff);
  num_items = atoi(buff);
  printf("Items number: %d\n", num_items);

  // miglior soluzione fino ad ora
  fscanf(fp, "%s", buff);
  best_solution = atoi(buff);
  printf("Best Solution: %d\n", best_solution);

  // creo la lista di oggetti non ordinata
  d_s->items = (float *)calloc(num_items, sizeof(float));
  if(d_s->items == NULL)
  {
    printf("MALLOC FAILED load_dataset\n");
    exit(-1);
  }
  for(int i=0; i<num_items; i++)
  {
    fscanf(fp, "%s", buff);
    tmp = atof(buff);
    d_s->items[i] = tmp;
  }
  d_s->bin_size = bin_size;
  d_s->best_sol = best_solution;
  d_s->n = num_items;

  // creo la lista ordinata di oggetti
  sorteditems = (float *)calloc(num_items, sizeof(float));
  if(sorteditems == NULL)
  {
    printf("MALLOC FAILED load_dataset\n");
    exit(-1);
  }
  for(int i=0; i<num_items; i++)
  {
    sorteditems[i] = d_s->items[i];
  }
  qsort(sorteditems,num_items, sizeof(float), compare_function);
  d_s->sorteditems = sorteditems;

  // creo la lista linkata di oggetti
  // int a = (int)malloc(sizeof(int));
  d_s->head = malloc(sizeof(node_t));
  tmpN = malloc(sizeof(node_t));
  d_s->head->val = sorteditems[0];
  d_s->head->id = 0;
  d_s->head->next = tmpN;
  for(int i=1; i<num_items; i++)
  {
    tmpN->val = sorteditems[i];
    tmpN->id = i;
    prec = tmpN;
    tmpN = malloc(sizeof(node_t));
    prec->next = tmpN;
  }
  prec->next = NULL;
  free(tmpN);
  printf("Items Loading done.\n\n");
}
