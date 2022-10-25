#include "queue.h"

typedef struct Queue_Node {
  void * data;
  struct Queue_Node * next;
} Queue_Node;

struct Queue {
  int length;
  size_t data_size;
  Queue_Node * front;
  Queue_Node * back;
};

Boolean queue_node_destroy (Queue_Node ** node);