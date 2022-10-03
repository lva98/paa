#include <stdio.h>
#include <stdlib.h>

#ifndef BOOLEAN_H 
#define BOOLEAN_H 
#include "../boolean/public_boolean.h"
#endif

typedef struct Stack * Stack;
Boolean create (Stack *);
Boolean push (Stack, void *);
Boolean pop (Stack);
Boolean top (Stack, void **);
Boolean destroy (Stack *);
Boolean length (Stack, int *);