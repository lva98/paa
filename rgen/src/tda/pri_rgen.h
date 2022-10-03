#include "pub_rgen.h"
#include <string.h>

typedef struct RgenNode {
  struct RgenNode * next;
  void * data;
} RgenNode;

typedef struct Rgen {
  char * data_type;
  size_t data_size;
  short (*callback_reverse)(char *, void *);
  RgenNode * head;
  RgenNode * tail;
} Rgen;

short reverse_free_recursive (P_Rgen, RgenNode *);