#include "hanoi.h"
#define TOWERS_TOTAL 11

typedef struct Hanoi_Disk {
  Hanoi_Color color;
  int index;
} Hanoi_Disk;

typedef struct Hanoi_Tower {
  Stack stack;
  Hanoi_Color color;
} Hanoi_Tower;

struct Hanoi_Game {
  Hanoi_Tower towers[TOWERS_TOTAL];
  Boolean used_tower[TOWERS_TOTAL];
  int size;
};