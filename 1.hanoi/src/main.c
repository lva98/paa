#include "io.h"

int main () {
  Hanoi_Game hanoi;
  create_hanoi_game(&hanoi);
  read_input(hanoi);
  solve(hanoi);
  show(hanoi, print_tower, print_disk, next_tower);
  destroy_hanoi(&hanoi);
  return 0;
}