#include "private_list.h"
#include "string.h"

Boolean list_create (List * list, size_t data_size) {
  *list = (List) malloc(sizeof(struct List));
  if (*list == NULL) {
    return FALSE;
  }

  (*list)->front = NULL;
  (*list)->back  = NULL;
  (*list)->length = 0;
  (*list)->data_size = data_size;
  return TRUE;
}

List_Node * list_create_temp_node (List list, void * data) {
  List_Node * temp_node = (List_Node *) malloc(sizeof(List_Node));
  if (temp_node == NULL) return NULL;
  temp_node->next = NULL;
  temp_node->prev = NULL;
  temp_node->data = malloc(list->data_size);
  if (temp_node->data == NULL) return NULL;
  if (data != NULL) {
    memcpy(temp_node->data, data, list->data_size);
  }
  return temp_node; 
}

Boolean list_push_back (List list, void * data) {
  List_Node * temp_node = list_create_temp_node(list, data);
  if (temp_node == NULL) {
    return FALSE;
  }

  if (list->back != NULL) {
    list->back->next = temp_node;
    temp_node->prev = list->back;
  } else {
    list->front = temp_node;
    list->back = temp_node;
  }

  ++list->length;
  return TRUE;
}

Boolean list_push_front (List list, void * data) {
  List_Node * temp_node = list_create_temp_node(list, data);
  if (temp_node == NULL) {
    return FALSE;
  }

  if (list->front != NULL) {
    list->front->prev = temp_node;
    temp_node->next = list->front;
  } else {
    list->front = temp_node;
    list->back = temp_node;
  }

  ++list->length;
  return TRUE;
}

Boolean list_insert (List list, int index, void * data) {
  if (index < 0 || index > list->length) {
    return FALSE;
  }

  if (index == 0) {
    return list_push_front(list, data);
  }

  if (index == list->length) {
    return list_push_back(list, data);
  }

  List_Node * before_index_node = list->front;
  List_Node * after_index_node = NULL;
  for (int i = 0; i < index; i++) {
    before_index_node = before_index_node->next;
  }
  after_index_node = before_index_node->next;

  List_Node * temp_node = list_create_temp_node(list, data);
  if (temp_node == NULL) {
    return FALSE;
  }

  before_index_node->next = temp_node;
  after_index_node->prev = temp_node;
  temp_node->prev = before_index_node;
  temp_node->next = after_index_node;
}

Boolean list_pop_front (List list, void * data) {
  if (list_empty(list) == FALSE) {
    List_Node * old_front = list->front;

    if (data != NULL) {
      memcpy(data, old_front->data, list->data_size);
    }
    free(old_front->data);
    old_front->data = NULL;

    list->front = old_front->next;
    list->front->prev = NULL;
    free(old_front);
    old_front = NULL;

    --list->length;
  }
  return TRUE;
}

Boolean list_pop_back (List list, void * data) {
  if (list_empty(list) == FALSE) {
    List_Node * old_back = list->back;

    if (data != NULL) {
      memcpy(data, old_back->data, list->data_size);
    }
    free(old_back->data);
    old_back->data = NULL;

    list->back = old_back->prev;
    list->back->next = NULL;
    free(old_back);
    old_back = NULL;

    --list->length;
  }
  return TRUE;
}

Boolean list_front (List list, void * data) {
  memcpy(data, list->front->data, list->data_size);
  return TRUE;
}

Boolean list_back (List list, void * data) {
  memcpy(data, list->front->data, list->data_size);
  return TRUE;
}

Boolean list_empty (List list) {
  return list->front == NULL;
}

Boolean list_node_destroy (List_Node ** node) {
  free((*node)->data);
  (*node)->data = NULL;
  free(*node);
  *node = NULL;
  return TRUE;
}

Boolean list_destroy (List * list) {
  while (list_empty(*list) == FALSE) {
    if ((*list)->front->next) {
      List_Node * old_front = (*list)->front;
      (*list)->front = (*list)->front->next;
      list_node_destroy(&old_front);
    } else {
      list_node_destroy(&((*list)->front));
    }
  }

  free(*list);
  (*list) = NULL;

  return TRUE;
}