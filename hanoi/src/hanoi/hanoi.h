#include "../stack/stack.h"

#ifndef BOOLEAN_H 
#define BOOLEAN_H
#include "../boolean/boolean.h"
#endif

typedef enum Hanoi_Color {
  C_TE, // Temporária
  C_AZ,
  C_AM,
  C_AN,
  C_BR,
  C_LI,
  C_LJ,
  C_VE,
  C_VO,
  C_PR,
  C_RO
} Hanoi_Color;

typedef struct Hanoi_Game * Hanoi_Game;
Boolean create_hanoi_game (Hanoi_Game * hanoi_game);
Boolean add_disk (Hanoi_Game hanoi_game, Hanoi_Color tower_color, Hanoi_Color disk_color, int disk_index);
Boolean solve (Hanoi_Game hanoi_game);
Boolean show (Hanoi_Game hanoi_game, void (Hanoi_Color), void (Hanoi_Color, int, Boolean, int), void ());
Boolean destroy_hanoi (Hanoi_Game * hanoi_game);