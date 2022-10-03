#include "public_stack.h"

struct Stack {
  int length;
  struct StackNode * head;
};

struct Stack_Node {
  void * data;
  struct StackNode * next;
};