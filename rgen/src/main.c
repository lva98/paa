#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main () {
  P_Rgen p_rgen;

  if (read_and_compute_input(&p_rgen) == FALSE) {
    printf("Erro ao executar 'read_input'\n");
    exit(1);
  }
}

short calculate_data_size (size_t * data_size, char * data_type) {
  if (strcmp(data_type, "int") == 0) {
    *data_size = sizeof(int);
    return TRUE;
  }

  if (strcmp(data_type, "char") == 0) {
    *data_size = sizeof(char);
    return TRUE;
  }

  if (strcmp(data_type, "float") == 0) {
    *data_size = sizeof(float);
    return TRUE;
  }

  if (strcmp(data_type, "double") == 0) {
    *data_size = sizeof(double);
    return TRUE;
  }

  return FALSE;
}

short print_rgen_node (char * data_type, void * data) {
  if (strcmp(data_type, "int") == 0) {
    printf("(%d);\n", *((int *) data));
    return TRUE;
  }

  if (strcmp(data_type, "char") == 0) {
    printf("(%c);\n", *((char *) data));
    return TRUE;
  }

  if (strcmp(data_type, "float") == 0) {
    printf("(%f);\n", *((float *) data));
    return TRUE;
  }

  if (strcmp(data_type, "double") == 0) {
    printf("(%lf);\n", *((double *) data));
    return TRUE;
  }

  return FALSE;
}

short convert_to_data_type (char * data_type, size_t data_size, char * data, void ** converted_data) {
  *converted_data = (void *) malloc(sizeof(data_size));

  if (strcmp(data_type, "int") == 0) {
    int data_int = atoi(data);
    memcpy(*converted_data, &data_int, data_size);
    return TRUE;
  }

  if (strcmp(data_type, "char") == 0) {
    char data_char = data[0];
    memcpy(*converted_data, &data_char, data_size);
    return TRUE;
  }

  if (strcmp(data_type, "float") == 0) {
    float data_float = atof(data);
    memcpy(*converted_data, &data_float, data_size);
    return TRUE;
  }

  if (strcmp(data_type, "double") == 0) {
    char * eptr;
    double data_double = strtod(data, &eptr);
    memcpy(*converted_data, &data_double, data_size);
    return TRUE;
  }

  return FALSE;
}

short read_and_compute_input (PP_Rgen pp_rgen) {
  char * data_type;
  size_t data_size;

  if (scanf("Tipo:%m[a-z];", &data_type) != 1) {
    return FALSE;
  };

  printf("Tipo_do_dado:%s;\n", data_type);

  if (calculate_data_size(&data_size, data_type) == FALSE) {
    return FALSE;
  }

  if (create_rgen(pp_rgen, data_type, data_size, print_rgen_node) == FALSE) {
    return FALSE;
  }

  char * input_values;
  for (; scanf("%ms", &input_values) != EOF;) {
    char * input_free_ref = input_values;
    char * token = NULL;
    do {
      str_split(&input_values, ';', &token);
      if (token != NULL) {
        void * converted;
        
        if (convert_to_data_type(data_type, data_size, token, &converted) == FALSE) {
          return FALSE;
        }
        
        if (add_node(*pp_rgen, converted) == FALSE) {
          return FALSE;
        }
      }
    } while (token != NULL);
    free(input_free_ref);
  }

  if (reverse_free(pp_rgen) == FALSE) {
    return FALSE;
  }

  free(data_type);
  return TRUE;
}

void str_split (char ** rest, char delimiter, char ** token) {
  *token = NULL;

  if (*rest == NULL) {
    return;
  }

  *token = *rest;
  int base_length = strlen(*rest);

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
