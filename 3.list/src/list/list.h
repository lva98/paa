#include <stdio.h>
#include <stdlib.h>

#ifndef BOOLEAN_H 
#define BOOLEAN_H 
#include "../boolean/boolean.h"
#endif

typedef struct List * List;
Boolean list_create (List *, size_t);

Boolean list_push_front (List, void *);
Boolean list_push_back (List, void *);
Boolean list_insert (List, int, void *);

Boolean list_pop_front (List, void *);
Boolean list_pop_back (List, void *);
Boolean list_erase (List, int, void *);

Boolean list_back (List, void *);
Boolean list_front (List, void *);

Boolean list_empty (List);
Boolean list_destroy (List *);