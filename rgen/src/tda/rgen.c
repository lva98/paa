#include "pri_rgen.h"

short create_rgen (PP_Rgen pp_rgen, char * data_type, size_t data_size, short (*callback_reverse)(char *, void *)) {
  *pp_rgen = (P_Rgen) malloc(sizeof(Rgen));
  if ((*pp_rgen) == NULL) {
    return FALSE;
  }

  (*pp_rgen)->head = NULL;
  (*pp_rgen)->tail = NULL;
  (*pp_rgen)->data_size = data_size;
  (*pp_rgen)->data_type = data_type;
  (*pp_rgen)->callback_reverse = callback_reverse;
  return TRUE;
}

short add_node (P_Rgen p_rgen, void * data) {
  RgenNode * temp_node = (RgenNode *) malloc(sizeof(RgenNode));
  temp_node->data = malloc(p_rgen->data_size);
  temp_node->next = NULL;
  
  if (temp_node->data == NULL) {
    return FALSE;
  }
  
  memcpy(temp_node->data, data, p_rgen->data_size);
  free(data);

  if (p_rgen->head == NULL) {
    p_rgen->head = temp_node;
  }

  if (p_rgen->tail == NULL) {
    p_rgen->tail = temp_node;
  } else {
    p_rgen->tail->next = temp_node;
    p_rgen->tail = temp_node;
  }

  return TRUE;
}

short reverse_free (PP_Rgen r_gen) {
  reverse_free_recursive(*r_gen, (*r_gen)->head);
  free(*r_gen);
  return TRUE;
}

short reverse_free_recursive (P_Rgen r_gen, RgenNode * node) {
  if (node == NULL) {
    return TRUE;
  }
  reverse_free_recursive(r_gen, node->next);
  r_gen->callback_reverse(r_gen->data_type, node->data);
  free(node->data);
  free(node);
  return TRUE;
}