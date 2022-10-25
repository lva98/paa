#include "io.h"

Hanoi_Color str2color (char * str) {
  if (strcmp(str, "Pt") == 0) return C_TE;
  if (strstr(str, "az") != NULL) return C_AZ;
  if (strstr(str, "am") != NULL) return C_AM;
  if (strstr(str, "an") != NULL) return C_AN;
  if (strstr(str, "br") != NULL) return C_BR;
  if (strstr(str, "li") != NULL) return C_LI;
  if (strstr(str, "lj") != NULL) return C_LJ;
  if (strstr(str, "ve") != NULL) return C_VE;
  if (strstr(str, "vo") != NULL) return C_VO;
  if (strstr(str, "pr") != NULL) return C_PR;
  if (strstr(str, "ro") != NULL) return C_RO;
  perror("[str2color] not defined str\n");
  exit(1);
}

char * color2str (Hanoi_Color color) {
  if (color == C_TE) return "t";
  if (color == C_AZ) return "az";
  if (color == C_AM) return "am";
  if (color == C_AN) return "an";
  if (color == C_BR) return "br";
  if (color == C_LI) return "li";
  if (color == C_LJ) return "lj";
  if (color == C_VE) return "ve";
  if (color == C_VO) return "vo";
  if (color == C_PR) return "pr";
  if (color == C_RO) return "ro";
  perror("[color2str] not defined color\n");
  exit(1);
}

Boolean read_input (Hanoi_Game hanoi) {
  int n;
  if (scanf("N=%d;", &n) != 1) {
    return FALSE;
  }

  char * input_text;
  for (; scanf("%ms", &input_text) != EOF; ) {
    char * ptr_input_text = input_text;
    char * tower_str = NULL;
    int disk_index;
    Hanoi_Color tower_color, disk_color;
    str_split(&input_text, '=', &tower_str);
    tower_color = str2color(tower_str);

    if (str_between(&input_text, '[', ']')) {
      char * disk_str;
      do {
        str_split(&input_text, ';', &disk_str);
        if (disk_str != NULL) {
          disk_color = str2color(disk_str);
          sscanf(disk_str, "%*[^0123456789]%d", &disk_index); // https://stackoverflow.com/a/13399812
          add_disk(hanoi, tower_color, disk_color, disk_index);
        }
      } while (disk_str != NULL);
    };

    free(ptr_input_text);
  }

  return TRUE;
}

void print_tower (Hanoi_Color tower_color) {
  if (tower_color != C_TE) {
    char * color_str = color2str(tower_color);
    printf("PC%s=[", color_str);
  } else {
    printf("Pt=[");
  }
}

void print_disk (Hanoi_Color disk_color, int index, Boolean first, int count) {
  if (!first) {
    printf(";");
  }
  char * color_str = color2str(disk_color);
  printf("p%s%d", color_str, count);
}

void next_tower () {
  printf("];\n");
}