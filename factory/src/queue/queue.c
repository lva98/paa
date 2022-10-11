#include "private_queue.h"
#include "string.h"

Boolean queue_create (Queue * queue, size_t data_size) {
  *queue = (Queue) malloc(sizeof(struct Queue));
  if (*queue == NULL) {
    return FALSE;
  }

  (*queue)->front = NULL;
  (*queue)->back  = NULL;
  (*queue)->length = 0;
  (*queue)->data_size = data_size;
  return TRUE;
}

Boolean queue_push (Queue queue, void * data) {
  Queue_Node * temp_node = (Queue_Node *) malloc(sizeof(Queue_Node));
  if (temp_node == NULL) return FALSE;
  temp_node->next = NULL;
  temp_node->data = malloc(queue->data_size);
  if (temp_node->data == NULL) return FALSE;
  memcpy(temp_node->data, data, queue->data_size);

  if (queue->back != NULL) {
    queue->back->next = temp_node;
  } else {
    queue->front = temp_node;
  }
  queue->back = temp_node;
  ++queue->length;
  
  return TRUE;
}

Boolean queue_pop (Queue queue, void * ptr_data) {
  if (queue_empty(queue) == FALSE) {
    if (ptr_data != NULL) {
      memcpy(ptr_data, queue->front->data, queue->data_size);
    }
    free(queue->front->data);
    queue->front->data = NULL;

    if (queue->front != NULL) {
      Queue_Node * old_front = queue->front;
      queue->front = queue->front->next;
      free(old_front);
      old_front = NULL;
    } else {
      free(queue->front);
      queue->front = NULL;
    }

    --queue->length;
  }
  return TRUE;
}

Boolean queue_front (Queue queue, void * front) {
  memcpy(front, queue->front->data, queue->data_size);
  return TRUE;
}

Boolean queue_empty (Queue queue) {
  return queue->front == NULL;
}

Boolean queue_node_destroy (Queue_Node ** node) {
  free((*node)->data);
  (*node)->data = NULL;
  free(*node);
  *node = NULL;
  return TRUE;
}

Boolean queue_destroy (Queue * queue) {
  while (queue_empty(*queue) == FALSE) {
    if ((*queue)->front->next) { // has next
      Queue_Node * old_front = (*queue)->front;
      (*queue)->front = (*queue)->front->next;
      queue_node_destroy(&old_front);
    } else {
      queue_node_destroy(&((*queue)->front));
    }
  }

  free(*queue);
  (*queue) = NULL;

  return TRUE;
}