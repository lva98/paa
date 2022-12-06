#include "app.h"

int compare_function (const void * a, const void * b) {
  return (int)*((int *)a) - (int)*((int *)b);
}

void create_list () {
  list_create(&list, sizeof(int), compare_function);
}

void read_input () {
  char * ptr_input_text;
  char * input_text = (char *) malloc(10240);
  ptr_input_text = input_text;

  if (scanf("%s", input_text) != 1) {
    perror("SCANF ERROR");
    exit(1);
  }

  if (str_between(&input_text, '[', ']')) {
    char * item_str;
    input_text++;
    do {
      str_split(&input_text, ';', &item_str);
      if (item_str != NULL) {
        int n = atoi(item_str);
        list_push_back(list, (void *) &n); 
      }
    } while (item_str != NULL);
  }

  free(ptr_input_text);
}

void solve () {
  list_swap(list, 1, 2);
  int n;
  for (; !list_empty(list); ) {
    list_pop_front(list, (void *) &n);
    printf("%d\n", n);
  }
  list_destroy(&list);
}