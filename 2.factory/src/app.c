#include "app.h"

Factory_Color str2color (char * str) {
  if (strcmp(str, "Fm") == 0) return M;
  if (strstr(str, "az") != NULL) return AZ;
  if (strstr(str, "am") != NULL) return AM;
  if (strstr(str, "an") != NULL) return AN;
  if (strstr(str, "br") != NULL) return BR;
  if (strstr(str, "li") != NULL) return LI;
  if (strstr(str, "lj") != NULL) return LJ;
  if (strstr(str, "ve") != NULL) return VE;
  if (strstr(str, "vo") != NULL) return VO;
  if (strstr(str, "pr") != NULL) return PR;
  if (strstr(str, "ro") != NULL) return RO;
  perror("[str2color] not defined str\n");
  exit(1);
}

char * color2str (Factory_Color color) {
  if (color == M)  return "t";
  if (color == AZ) return "az";
  if (color == AM) return "am";
  if (color == AN) return "an";
  if (color == BR) return "br";
  if (color == LI) return "li";
  if (color == LJ) return "lj";
  if (color == VE) return "ve";
  if (color == VO) return "vo";
  if (color == PR) return "pr";
  if (color == RO) return "ro";
  perror("[color2str] not defined color\n");
  exit(1);
}

void create_queues () {
  for (int i = 0; i < TOTAL_COLORS; i++) {
    queue_create(&queues[i], sizeof(int));
  }
}

void destroy_queues () {
  for (int i = 0; i < TOTAL_COLORS; i++) {
    queue_destroy(&queues[i]);
  }
}

void read_input () {
  int n;
  if (scanf("N=%d;", &n) != 1) {
    return;
  }

  char * input_text;
  for (; scanf("%ms", &input_text) != EOF;) {
    char * ptr_input_text = input_text;
    char * queue_color_str = NULL;

    str_split(&input_text, '=', &queue_color_str);
    Factory_Color current_queue_color = str2color(queue_color_str);
    Factory_Color item_color;

    if (str_between(&input_text, '[', ']')) {
      char * item_str;
      do {
        str_split(&input_text, ';', &item_str);
        if (item_str != NULL) {
          item_color = str2color(item_str);
          queue_push(queues[current_queue_color], (void *) &item_color);
        }
      } while (item_str != NULL);
    }

    free(ptr_input_text);
  }
}

void solve () {
  int cont = 0;
  printf("PC=[");
  for (int i = 0; !queue_empty(queues[0]); i++) {
    int mold_color, item_color;
    queue_pop(queues[0], (void *) &mold_color);
    
    if (queue_empty(queues[mold_color])) {
      cont++;
      continue;
    }

    queue_pop(queues[mold_color], (void *) &item_color);
    printf("p%s%d", color2str(item_color), i + 1);
    if (!queue_empty(queues[0])) {
      printf(";");
    }
  }
  printf("]\n");

  for (int i = 1; i < TOTAL_COLORS; i++) {
    for (; !queue_empty(queues[i]);) {
      queue_pop(queues[i], NULL);
      cont++;
    }
  }

  printf("PD=[");
  for (int i = 1; i < cont + 1; i++) {
    printf("d_%d", i);
    if (i != cont) {
      printf(";");
    }
  }
  printf("]\n");
}