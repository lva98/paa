#include "web_tree/web_tree.h"
#include "utils/utils.h"

typedef enum App_Type {
  APP_INT,
  APP_FLOAT,
  APP_CHAR
} App_Type;

Web_Tree web_tree;
App_Type app_type = APP_INT;
int step = -1;
int level = -1;
size_t data_size = 0;

char * direction2text (unsigned short i) {
  switch (i) {
    case N:  return "N";
    case NE: return "NE";
    case E:  return "E";
    case SE: return "SE";
    case S:  return "S";
    case SW: return "SO";
    case W:  return "O";
    case NW: return "NO";
  }
  perror("direction2text\n");
  exit(1);
}

void * create_value_fn (int index) {
  if (app_type == APP_INT) {
    int * ret = malloc(sizeof(int));
    *ret = (index + 1) * step;
    return ret;
  }

  if (app_type == APP_FLOAT) {
    float * ret = malloc(sizeof(float));
    *ret = (index + 1) * step;
    return ret;
  }

  if (app_type == APP_CHAR) {
    char * ret = malloc(sizeof(char));
    *ret = (char) (index + 1) * step;
    return ret;
  }

  return NULL;
}

Boolean equality_operator_fn (void * a, void * b) {
  if (app_type == APP_INT) {
    data_size = sizeof(int);
    return (*((int *) a) == *((int *) b));
  }

  if (app_type == APP_FLOAT) {
    data_size = sizeof(float);
    return (*((float *) a) == *((float *) b));
  }

  if (app_type == APP_CHAR) {
    data_size = sizeof(char);
    return (*((char *) a) == *((char *) b));
  }

  return FALSE;
}
App_Type text2app_type (char * str) {
  if (strcmp(str, "int")   == 0) return APP_INT;
  if (strcmp(str, "float") == 0) return APP_FLOAT;
  if (strcmp(str, "char")  == 0) return APP_CHAR;
  perror("text2app_type\n");
  exit(1);
}

void operation_pd (char str[]) {
  char * value_str;
  void * search_data = NULL;
  str_split(&str, ';', &value_str);

  if (app_type == APP_INT) {
    int data = atoi(value_str);
    search_data = (void *) &data;
  }

  if (app_type == APP_FLOAT) {
    float data = atof(value_str);
    search_data = (void *) &data;
  }

  if (app_type == APP_CHAR) {
    char data = value_str[0];
    search_data = (void *) &data;
  }

  if (search_data == NULL) {
    perror("operation_pd");
    exit(1);
  }

  short int * result;
  int length;
  printf("PD=");
  if (wt_find_value(web_tree, search_data, &result, &length)) {
    for (int i = 0; i < length; i++) {
      if (i < length - 1) {
        printf(";");
      } 
      printf("%s", direction2text(result[i]));
    }
    printf("\n");
  } else {
    printf("-1;\n");
  }
}

void read_input () {
  char str_type[6];
  if (scanf("t=%s", str_type) != 1) {
    perror("read_input\n");
    exit(1);
  }
  str_type[strlen(str_type) - 1] = '\0';
  app_type = text2app_type(str_type); 

  if (scanf("p=%d;", &step)) {
    perror("read_input\n");
    exit(1);
  }
  printf("%d\n", step);

  if (scanf("n=%d;", &level)) {
    perror("read_input\n");
    exit(1);
  }
  printf("%d\n", level);

  wt_create(&web_tree, data_size, level, create_value_fn, equality_operator_fn);

  char * str_op = (char *) malloc(sizeof(char) * 2048);
  for (; scanf("%s", str_op) != EOF;) {
    char * op;
    str_split(&str_op, '=', &op);
    if (strcmp(op, "PD") == 0) {
      operation_pd(str_op);
    }
  }
}

unsigned short text2direction (char * str) {
  if (strcmp(str, "N")  == 0) return N;
  if (strcmp(str, "NE") == 0) return NE;
  if (strcmp(str, "E")  == 0) return E;
  if (strcmp(str, "SE") == 0) return SE;
  if (strcmp(str, "S")  == 0) return S;
  if (strcmp(str, "SO") == 0) return SW;
  if (strcmp(str, "O")  == 0) return W;
  if (strcmp(str, "NO") == 0) return NW;
  perror("text2direction\n");
  exit(1);
}

int main () {
  read_input();
  /*
  Web_Tree web_tree;
  wt_create(&web_tree, sizeof(int), 1, create_value_fn, equality_operator_fn);
  int value = 25;
  short int * result;
  int length;
  if (wt_find_value(web_tree, (void *) &value, &result, &length)) {
    for (int i = 0; i < length; i++) {
      printf("%s ", direction2text(result[i]));
    }
    printf("\n");
  } else {
    printf("-1\n");
  }
  */

  return 0;
}
