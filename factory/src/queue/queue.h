#include <stdio.h>
#include <stdlib.h>

#ifndef BOOLEAN_H 
#define BOOLEAN_H 
#include "../boolean/boolean.h"
#endif

typedef struct Queue * Queue;
Boolean queue_create (Queue *, size_t);
Boolean queue_push (Queue, void *);
Boolean queue_pop (Queue, void **);
Boolean queue_front (Queue, void **);
Boolean queue_empty (Queue);
Boolean queue_destroy (Queue *);