#include "utils.h"

int str_len (char * str) {
  int i;
  for (i = 0; str[i] != '\0'; ++i);
  return i;
}

void str_split (char ** rest, char delimiter, char ** token) {
  *token = NULL;

  if (*rest == NULL) {
    return;
  }

  *token = *rest;
  int base_length = str_len(*rest);

  for (int i = 0; i < base_length; i++) {
    if ((*rest)[i] == delimiter) {
      (*rest)[i] = '\0';
      if (i + 1 < base_length && i != base_length - 1) {
        *rest += i + 1;
        return;
      }
    }
  }

  *rest = NULL;
}

Boolean str_between (char ** str, char init_char, char end_char) {
  int init_index = 0, end_index = 0;
  for (int i = 0; (*str)[i] != '\0'; i++) {
    if ((*str)[i] == init_char) {
      init_index = i;
    }

    if ((*str)[i] == end_char) {
      end_index = i;
      break;
    }
  }

  if (end_index > init_index && end_index - init_index >= 2) {
    *str += init_index;
    (*str)[end_index] = '\0';
    return TRUE;
  }

  return FALSE;
}
