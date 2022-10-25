#include <stdio.h>
#include <stdlib.h>

#ifndef BOOLEAN_H 
#define BOOLEAN_H 
#include "../boolean/boolean.h"
#endif

typedef struct Stack * Stack;
Boolean stack_create (Stack *, size_t);
Boolean stack_push (Stack, void *);
Boolean stack_pop (Stack, void **);
Boolean stack_top (Stack, void **);
Boolean stack_empty (Stack);
Boolean stack_destroy (Stack *);