#include "queue/queue.h"
#include <stdio.h>

int main () {
  Queue queue;
  queue_create(&queue, sizeof(int));

  for (int i = 0; i < 10; i++) {
    queue_push(queue, &i);
  }

  while (queue_empty(queue) == FALSE) {
    int front;
    queue_front(queue, &front);
    printf("%d\n", front);
    queue_pop(queue, NULL);
  }

  queue_destroy(&queue);

  return 0;
}