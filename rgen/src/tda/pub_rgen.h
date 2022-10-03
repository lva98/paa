#include <stdio.h>
#include <stdlib.h>

#if !defined(TRUE) || !defined(FALSE)
#define TRUE 1
#define FALSE 0
#endif

typedef struct Rgen *P_Rgen, **PP_Rgen;

short create_rgen (PP_Rgen, char *, size_t, short (char *, void *));
short add_node (P_Rgen, void *);
short reverse_free (PP_Rgen r_gen);