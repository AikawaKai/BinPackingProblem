#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

int compareNode(const void *v1, const void *v2)
{
    const node_t *u1 = v1;
    const node_t *u2 = v2;
    if (u1->val > u2->val) return -1;
    else if (u1->val == u2->val) return 0;
    else return 1;
}

// rimuove la testa della lista linkata
int pop(node_t ** head) {
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

// rimuove l'elemento in base all'index
int remove_by_index(node_t ** head, int n) {
    int i = 0;
    int retval = -1;
    node_t * current = *head;
    node_t * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (int i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    temp_node = current->next;
    retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);

    return retval;

}

int remove_by_node_value(node_t ** head, node_t *node_ind) {
    int i = 0;
    int retval = -1;
    node_t * current = *head;
    node_t * prec;
    node_t * tmp_node = NULL;

    if (node_ind == *head) {
        tmp_node = (*head)->next;
        pop(head);
        return 1;
    }
    prec = current;
    current = current->next;
    while (current!=NULL)
    {
      if (current->id == node_ind->id)
      {
        prec->next = current->next;
        current->val = 0;
        current->next = NULL;
        free(current);
        return 1;
      }
      prec = current;
      current = current->next;
    }
    return 0;

    /*
    for (int i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    temp_node = current->next;
    retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);

    return retval;*
*/
}

// aggiunge un elemento in coda alla lista linkata
void push(node_t * head, float val) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // adesso possiamo aggiungere una nuova variabile
    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

node_t * copy(node_t * head)
{
  node_t *head2=NULL,*previous=NULL;

  while(head!=NULL)
  {
      node_t * temp = (node_t *) malloc (sizeof(node_t));
      temp->id=head->id;
      temp->val=head->val;
      temp->next=NULL;

      if(head2==NULL)
      {
          head2=temp;
          previous=temp;
      }
      else
      {
          previous->next=temp;
          previous=temp;
      }
      head=head->next;
  }
  return head2;
}

// metodo per la print
void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%f\n", current->val);
        current = current->next;
    }
}

// metodo per liberare la lista linkata
void free_list(node_t *head){
  node_t *current = head;
  node_t *next;

  while (current != NULL){
    next = current->next;
    current->val = 0;
    current->id = 0;
    current->next = NULL;
    free(current);
    current = next;
  }
}

void sort_not_linked_list(node_t * list, int size)
{
  qsort(list, size, sizeof(node_t), compareNode);
}
