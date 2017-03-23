#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct node {
    int id; // bin index
    float val; // item value
    int item_index_bin; // item index in bin
    struct node * next;
} node_t;

int pop(node_t ** head);
int remove_by_index(node_t ** head, int n);
int remove_by_node_value(node_t **head, node_t *node);
void push(node_t * head, float val);
node_t * copy(node_t * head);
void print_list(node_t * head);
void free_list(node_t * head);
void sort_list(node_t * list, int size);

#endif
