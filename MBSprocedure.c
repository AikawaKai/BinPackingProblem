#include "linkedList.h"
#include "hashset.h"
#include "MBSprocedure.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int bernoulli(float p){
    if(p < 0 || p > 1) return -1;
    float x = (float)rand()/(float)(RAND_MAX/1);
    if(p < x) return 0;
    return 1;
}

node_t * prob_sorting(node_t ** head_pointer, node_t * head, int sum, int num_el)
{
  float p_i = 0.0;
  node_t *head2=NULL,*previous=NULL;

  while(head!=NULL)
  {
      node_t * temp = (node_t *) malloc (sizeof(node_t));
      node_t * to_delete;
      p_i = (head->val * head->val) / (float) sum;
      temp->id=head->id;
      temp->val=head->val;
      temp->next=NULL;

      if(head2==NULL)
      {
          if (bernoulli(p_i))
          {
            //printf("%f\n",p_i);
            head2=temp;
            previous=temp;
            sum -= (temp->val * temp->val);
            to_delete = head;
            head = head->next;
            remove_by_node_value(head_pointer, to_delete);
          }
          else
          {
            head=head->next;
          }
      }
      else
      {
          if (bernoulli(p_i))
          {
            //printf("%f\n",p_i);
            previous->next=temp;
            previous=temp;
            to_delete = head;
            head = head->next;
            remove_by_node_value(head_pointer, to_delete);
            if (p_i ==1.0)
            {
              break;
            }
            sum -= (temp->val * temp->val);
          }
          else
          {
            head=head->next;
          }
      }
      if (head == NULL && num_el >0 )
      {
        head = *head_pointer;
      }
  }
  return head2;
}

void MBSsearch(int index, int n_max, int min_value, node_t *curr_node, hashset_t curr_set, hashset_t curr_best_set)
{
  if (curr_set->slack >= min_value)
  {
    for (int i=index; i<n_max; i++)
    {

      // EL_i = curr_nod   al primo giro
      if (curr_node->val <= curr_set->slack) // if el_i <= S(A)
      {
        //updateA(curr_set, curr_node, i); // A = A U {i}
        hashset_add(curr_set, curr_node);
        MBSsearch(i+1, n_max, min_value, curr_node->next, curr_set, curr_best_set); //MBSsearch(i+1)
        hashset_remove(curr_set, curr_node);
        //deleteAi(curr_set, curr_node, i); // A = A / {i}
        if (curr_best_set->slack ==0) // if(s(A*)==0) esco dalla procedura
        {
          return;
        }
      }
      curr_node = curr_node->next;
    }
  }
  if(curr_set->slack < curr_best_set->slack) // if(s(A)<s(A*)) aggiorno se migliore
  {
    // printf("S(A*): %d S(A):%d\n", curr_best_set->slack, curr_set->slack);
    deepCopy(curr_best_set, curr_set);
  }
}

void MBS(dataset_t *d_s, sol_t *sol)
{
  node_t ** head_pointer;
  head_pointer = &(d_s->head);
  hashset_t best_A_set = hashset_create(d_s->bin_size);
  hashset_t curr_A_set = hashset_create(d_s->bin_size);
  int elem_to_insert = d_s->n;
  while (elem_to_insert>0)
  {
    add_new_bin(sol);
    MBSsearch(0, elem_to_insert, d_s->sorteditems[(d_s->n)-1], d_s->head, curr_A_set, best_A_set);
    for(int i=0; i<best_A_set->nitems; i++)
    {
      //printf("elem %d: %d |",i, ((node_t **)best_A_set->items)[i]->val);
      //printf("%d\n", ((node_t **)best_A_set->items)[i]->val);
      add_item_to_bin(&(sol->bins[(sol->n)-1]), ((node_t **)best_A_set->items)[i]->val);
      remove_by_node_value(head_pointer, ((node_t **)best_A_set->items)[i]);
    }
    elem_to_insert = elem_to_insert-best_A_set->nitems;
    hashset_destroy(best_A_set);
    hashset_destroy(curr_A_set);
    best_A_set = hashset_create(d_s->bin_size);
    curr_A_set = hashset_create(d_s->bin_size);
  }
  hashset_destroy(best_A_set);
  hashset_destroy(curr_A_set);
}

void MBSmodified(dataset_t *d_s, sol_t *sol)
{
  node_t ** head_pointer;
  head_pointer = &(d_s->head);
  hashset_t best_A_set = hashset_create(d_s->bin_size);
  hashset_t curr_A_set = hashset_create(d_s->bin_size);
  int elem_to_insert = d_s->n;
  while (elem_to_insert>0)
  {
    hashset_add(curr_A_set, d_s->head);
    hashset_add(best_A_set, d_s->head);
    add_new_bin(sol);
    MBSsearch(1, elem_to_insert, d_s->sorteditems[(d_s->n)-1], d_s->head->next, curr_A_set, best_A_set);
    for(int i=0; i<best_A_set->nitems; i++)
    {
      //printf("elem %d: %d |",i, ((node_t **)best_A_set->items)[i]->val);
      //printf("%d\n", ((node_t **)best_A_set->items)[i]->val);
      add_item_to_bin(&(sol->bins[(sol->n)-1]), ((node_t **)best_A_set->items)[i]->val);
      remove_by_node_value(head_pointer, ((node_t **)best_A_set->items)[i]);
    }
    //printf("\n");
    elem_to_insert = elem_to_insert-best_A_set->nitems;
    hashset_destroy(best_A_set);
    hashset_destroy(curr_A_set);
    best_A_set = hashset_create(d_s->bin_size);
    curr_A_set = hashset_create(d_s->bin_size);
  }
  hashset_destroy(best_A_set);
  hashset_destroy(curr_A_set);
}

sol_t * MBSsampling(dataset_t *d_s)
{
  FILE *fp;
  int max_attempts = 100;
  char fileinput[] = "pseudorandseednumbers.txt";
  char buff[8];
  int seed;
  int curr_best = d_s->n;
  int sum=0;
  int num_el = d_s->n;
  int max_num_elem = (d_s->bin_size / d_s->sorteditems[(d_s->n)-1])+1;
  node_t *ordered_list_head = copy(d_s->head);
  node_t *next = malloc(sizeof(node_t));
  sol_t *sol = malloc(sizeof(sol_t));
  initialize_solution(sol, d_s->bin_size, d_s->n, max_num_elem);

  // sum for the proability sorting
  next = d_s->head;
  sum += (next->val * next->val);
  for(int i=1; i<d_s->n;i++)
  {
    next = next->next;
    sum+= (next->val * next->val);
  }
  //initialize_solution(best_sol, d_s->bin_size, d_s->n, max_num_elem);
  fp = fopen(fileinput, "r");

  while(max_attempts>0)
  {
    sol_t *tmp = malloc(sizeof(sol_t));
    initialize_solution(tmp, d_s->bin_size, d_s->n, max_num_elem);
    fscanf(fp, "%s", buff);
    seed = atoi(buff);
    srand(seed);
    d_s->head = prob_sorting(&(d_s->head),d_s->head, sum, num_el);
    MBSmodified(d_s, tmp);
    if(tmp->n<curr_best)
    {
      free_solution(sol);
      sol = tmp;
      curr_best = sol->n;
    }
    d_s->head = copy(ordered_list_head);
    max_attempts--;
  }
  fclose(fp);
  return sol;
}
