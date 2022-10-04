#include "stack.h"
typedef struct Stack_Node {
  void * data;
  struct Stack_Node * next;
} Stack_Node ;

struct Stack {
  int length;
  size_t data_size;
  Stack_Node * head;
};