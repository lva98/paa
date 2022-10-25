#include "stack.h"

typedef struct Stack_Node {
  void * data;
  struct Stack_Node * next;
} Stack_Node;

struct Stack {
  int length;
  size_t data_size;
  Stack_Node * head;
};

Boolean stack_node_destroy (Stack_Node ** node);