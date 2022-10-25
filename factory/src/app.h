#include "queue/queue.h"
#include "utils/utils.h"

#define TOTAL_COLORS 11

typedef enum Factory_Color {
  M, // molde
  AZ,
  AM,
  AN,
  PR,
  BR,
  VE,
  VO,
  LI,
  RO,
  LJ
} Factory_Color;

Queue queues[TOTAL_COLORS];
Factory_Color str2color (char * str);
char * color2str (Factory_Color color);
void create_queues ();
void destroy_queues ();
void read_input ();
void solve ();

