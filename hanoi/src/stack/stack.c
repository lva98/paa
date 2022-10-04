#include "private_stack.h"
#include <string.h>

Boolean stack_create (Stack * stack, size_t data_size) {
  *stack = (Stack) malloc(sizeof(struct Stack));
  if (*stack == NULL) {
    return FALSE;
  }

  (*stack)->head = NULL;
  (*stack)->length = 0;
  (*stack)->data_size = data_size;
  return TRUE;
}

Boolean stack_push (Stack stack, void * data) {
  Stack_Node * temp_node = (Stack_Node *) malloc(sizeof(Stack_Node));
  if (temp_node == NULL) {
    return FALSE;
  }

  temp_node->data = malloc(stack->data_size);
  memcpy(temp_node->data, data, stack->data_size);

  if (temp_node->data == NULL) {
    return FALSE;
  }

  temp_node->next = NULL;
  if (stack->head != NULL) {
    temp_node->next = stack->head;
  }
  stack->head = temp_node;
  
  ++stack->length;
  return TRUE;
}

Boolean stack_pop (Stack stack, void ** ptr_data) {
  *ptr_data = NULL;
  if (stack->head != NULL) {
    *ptr_data = (void *) malloc(stack->data_size);
    if (*ptr_data == NULL) {
      return FALSE;
    }
    memcpy(*ptr_data, stack->head->data, stack->data_size);
    free(stack->head->data);

    if (stack->head->next != NULL) {
      Stack_Node * old_head = stack->head;
      stack->head = stack->head->next;
      free(old_head);
    } else {
      free(stack->head);
      stack->head = NULL;
    }

    --stack->length;
  }
  return TRUE;
}

Boolean stack_top (Stack stack, void ** data) {
  void * ptr = memcpy(*data, stack->head->data, stack->length);
  if (ptr == NULL) {
    return FALSE;
  }

  return TRUE;
}

Boolean stack_length (Stack stack, int * length) {
  *length = stack->length;
  return TRUE;
}

Boolean stack_destroy (Stack * stack) {
  free((*stack)->head);
  free(*stack);
  return TRUE;
}