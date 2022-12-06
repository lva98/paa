#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BOOLEAN_H 
#define BOOLEAN_H 
#include "../boolean/boolean.h"
#endif

typedef struct Web_Tree * Web_Tree;

typedef enum Directions {
  N,
  NE,
  E,
  SE,
  S,
  SW,
  W,
  NW
} Directions;

Boolean wt_create (
  Web_Tree * web_tree,
  size_t data_size,
  int max_level,
  void* (*create_value_fn)(int index),
  Boolean (*equality_operator_fn)(void *, void *)
);
Boolean wt_find_value (Web_Tree web_tree, void * value, short int ** result, int * length);
