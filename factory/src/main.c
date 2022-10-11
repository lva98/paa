#include "queue/queue.h"

int main () {
  Queue queue;
  queue_create(&queue, sizeof(int));

  int n = 10;
  queue_push(queue, (void **) &n);
  int m = 20;
  queue_push(queue, (void **) &m);

  queue_pop(queue, NULL);
  queue_pop(queue, NULL);
}