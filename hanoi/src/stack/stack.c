#include "private_stack.h"

Boolean create (Stack * stack) {
  *stack = (Stack) malloc(sizeof(struct Stack));
  if (*stack == NULL) {
    return FALSE;
  }

  (*stack)->head = NULL;
  (*stack)->length = 0;

  return TRUE;
}

Boolean push (Stack, void *) {
  struct Stack_Node * temp_node
}

