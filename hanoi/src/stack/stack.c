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
  if (stack_empty(stack) == FALSE) {
    *ptr_data = NULL;
    *ptr_data = (void *) malloc(stack->data_size);
    if (*ptr_data == NULL) {
      return FALSE;
    }
    memcpy(*ptr_data, stack->head->data, stack->data_size);
    free(stack->head->data);
    stack->head->data = NULL;

    if (stack->head->next != NULL) {
      Stack_Node * old_head = stack->head;
      stack->head = stack->head->next;
      free(old_head);
      old_head = NULL;
    } else {
      free(stack->head);
      stack->head = NULL;
    }

    --stack->length;
  }
  return TRUE;
}

Boolean stack_top (Stack stack, void ** top) {
  memcpy(*top, stack->head->data, stack->data_size);
  return TRUE;
}

Boolean stack_empty (Stack stack) {
  return stack->head == NULL;
}

Boolean stack_node_destroy (Stack_Node ** node) {
  free((*node)->data);
  (*node)->data = NULL;
  free(*node);
  *node = NULL;
  return TRUE;
}

Boolean stack_destroy (Stack * stack) {
  while (stack_empty(*stack) == FALSE) {
    if ((*stack)->head->next) {
      Stack_Node * old_head = (*stack)->head;
      (*stack)->head = (*stack)->head->next;
      stack_node_destroy(&old_head);
    } else {
      stack_node_destroy(&((*stack)->head));
    }
  }

  free(*stack);
  (*stack) = NULL;

  return TRUE;
}