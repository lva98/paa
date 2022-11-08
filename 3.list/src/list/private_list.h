#include "list.h"

typedef struct List_Node {
  void * data;
  struct List_Node * next;
  struct List_Node * prev;
} List_Node;

struct List {
  int length;
  size_t data_size;
  List_Node * front;
  List_Node * back;
  int (*compare_function)(const void * a, const void * b);
};

Boolean list_node_destroy (List_Node ** node);
List_Node * list_create_temp_node (List list, void * data);