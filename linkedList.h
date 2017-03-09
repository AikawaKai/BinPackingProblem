typedef struct node {
    int val;
    struct node * next;
} node_t;

int pop(node_t ** head);
int remove_by_index(node_t ** head, int n);
void push(node_t * head, int val);
void print_list(node_t * head);
