#include "app.h"

int main () {
  create_queues();
  read_input();
  solve();
  destroy_queues();
  return 0;
}