#include "private_web_tree.h"

Boolean wt_create_node (Web_Tree web_tree, Web_Tree_Node ** node, int level) {
  *node = (Web_Tree_Node *) malloc(sizeof(Web_Tree_Node));
  if (*node == NULL) {
    return FALSE;
  }

  (*node)->level = level;
  // Se for folha
  if (level == web_tree->max_level) {
    for (int i = 0; i < MAX_DIRECTIONS; ++i) {
      (*node)->values[i] = malloc(web_tree->data_size);
      if ((*node)->values[i] == NULL) {
        return FALSE;
      }
      void * data = web_tree->create_value_fn(web_tree->index_count);
      // printf("%d -> %d\n", level, *((int *) data));
      memcpy((*node)->values[i], data, web_tree->data_size);
      ++web_tree->index_count;
    }
  }

  return TRUE;
}

Boolean wt_generate (Web_Tree web_tree, Web_Tree_Node * parent) {
  // Caso base = nó atual for folha 
  if (parent->level >= web_tree->max_level) {
    return TRUE;
  }

  // Se não
  for (int i = 0; i < MAX_DIRECTIONS; i++) {
    if (wt_create_node(web_tree, &parent->childs[i], parent->level + 1) == FALSE) {
      return FALSE;
    }

    if (wt_generate(web_tree, parent->childs[i]) == FALSE) {
      return FALSE;
    }
  }

  return TRUE;
}


Boolean wt_create (Web_Tree * web_tree, size_t data_size, int max_level, void* (*create_value_fn)(int index), Boolean (*equality_operator_fn)(void *, void *)) {
  *web_tree = (Web_Tree) malloc(sizeof(struct Web_Tree));
  if (*web_tree == NULL) {
    return FALSE;
  }

  (*web_tree)->max_level = max_level;
  (*web_tree)->create_value_fn = create_value_fn;
  (*web_tree)->index_count = 0;
  (*web_tree)->data_size = data_size;
  (*web_tree)->equality_operator_fn = equality_operator_fn;
  (*web_tree)->search_path = malloc(sizeof(unsigned short) * (max_level + 1));

  // Cria o nó raíz
  if (wt_create_node(*web_tree, &((*web_tree)->root), 0) == FALSE) {
    return FALSE;
  }

  return wt_generate(*web_tree, (*web_tree)->root);
}

Web_Tree_Node * wt_find_value_recursive (Web_Tree web_tree, Web_Tree_Node * node, void * value) {
  if (node->level == web_tree->max_level) {
    for (int i = 0; i < MAX_DIRECTIONS; i++) {
      if (web_tree->equality_operator_fn(node->values[i], value)) {
        web_tree->search_path[node->level] = i;
        return node;
      }
    }
    return NULL;
  }

  for (int i = 0; i < MAX_DIRECTIONS; i++) {
    web_tree->search_path[node->level] = i;
    Web_Tree_Node * found = wt_find_value_recursive(web_tree, node->childs[i], value);
    if (found != NULL) {
      return found;
    }
  }

  return NULL;
}

Boolean wt_find_value (Web_Tree web_tree, void * value, short int ** result, int * length) {
  *result = (short int *) malloc(sizeof(short int) * (web_tree->max_level + 1));
  if (*result == NULL) {
    return FALSE;
  }

  Web_Tree_Node * node = wt_find_value_recursive(web_tree, web_tree->root, value);
  if (node == NULL) {
    return FALSE;
  }

  memcpy(*result, web_tree->search_path, sizeof(short int) * (web_tree->max_level + 1));
  *length = web_tree->max_level + 1;
  return TRUE;
}
