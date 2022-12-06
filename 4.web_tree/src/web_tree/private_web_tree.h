#include "web_tree.h"
#include "string.h"
#define MAX_DIRECTIONS 8

typedef struct Web_Tree_Node {
  struct Web_Tree_Node * childs[8];
  void * values[8];
  int level;
} Web_Tree_Node;

struct Web_Tree {
  int max_level;
  void * (*create_value_fn)(const int index);
  Boolean (*equality_operator_fn)(void *, void *);
  size_t data_size;
  Web_Tree_Node * root;
  unsigned short * search_path;
  int index_count;
};

Boolean wt_generate (Web_Tree, Web_Tree_Node *);
Boolean wt_create_node (Web_Tree, Web_Tree_Node **, int);
Web_Tree_Node * wt_find_value_recursive (Web_Tree web_tree, Web_Tree_Node * node, void * value);
