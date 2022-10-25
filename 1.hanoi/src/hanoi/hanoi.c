#include "private_hanoi.h"

Boolean create_hanoi_game (Hanoi_Game * hanoi_game) {
  (*hanoi_game) = (Hanoi_Game) malloc(sizeof(struct Hanoi_Game));
  if (*hanoi_game == NULL) {
    return FALSE;
  }

  for (int i = 0; i < TOWERS_TOTAL; i++) {
    Stack * stack = &((*hanoi_game)->towers[i].stack);
    if (!stack_create(stack, sizeof(Hanoi_Disk))) {
      return FALSE;
    }
    (*hanoi_game)->towers[i].color = i;
    (*hanoi_game)->used_tower[i] = FALSE;
  }

  (*hanoi_game)->used_tower[0] = TRUE;

  return TRUE;
}

Boolean add_disk (Hanoi_Game hanoi_game, Hanoi_Color tower_color, Hanoi_Color disk_color, int disk_index) {
  Hanoi_Disk disk;
  disk.color = disk_color;
  disk.index = disk_index;
  hanoi_game->used_tower[tower_color] = TRUE;
  Stack tower_stack = hanoi_game->towers[tower_color].stack;
  if (!stack_push(tower_stack, &disk)) {
    return FALSE;
  }
  return TRUE;
}

Boolean solve (Hanoi_Game hanoi_game) {
  // Passo 1: Desempilha das torres coloridas -> empilha nas pilhas temporárias
  Stack temp_tower_stack = hanoi_game->towers[C_TE].stack;
  for (int i = 1; i < TOWERS_TOTAL; i++) {
    if (hanoi_game->used_tower[i]) {
      Stack curr_stack = hanoi_game->towers[i].stack;
      while (stack_empty(curr_stack) == FALSE) {
        Hanoi_Disk * disk;
        stack_pop(curr_stack, (void **) &disk);
        stack_push(temp_tower_stack, disk);
        free(disk);
        disk = NULL;
      }
    }
  }

  // Passo 2: Desempilha da torre temporária -> empilha nas torres coloridas
  while (stack_empty(temp_tower_stack) == FALSE) {
    Hanoi_Disk * disk;
    stack_pop(temp_tower_stack, (void **) &disk);
    Stack target_stack = hanoi_game->towers[disk->color].stack;
    stack_push(target_stack, disk);
    free(disk);
    disk = NULL;
  }

  return TRUE;
}

Boolean show (Hanoi_Game hanoi_game, void (*f1)(Hanoi_Color), void (*f2)(Hanoi_Color, int, Boolean, int), void (*f3)()) {
  for (int i = 0; i < TOWERS_TOTAL; i++) {
    if (hanoi_game->used_tower[i]) {
      Hanoi_Tower tower = hanoi_game->towers[i];
      f1(tower.color);
      Boolean first = TRUE;

      int count = 0;
      while (stack_empty(tower.stack) == FALSE) {
        Hanoi_Disk * disk = NULL;
        stack_pop(tower.stack, (void **) &disk);
        f2(disk->color, disk->index, first, ++count);
        first = FALSE;
        free(disk);
      }
      f3();
    }
  }
  return TRUE;
}

Boolean destroy_hanoi (Hanoi_Game * hanoi_game) {
  for (int i = 0; i < TOWERS_TOTAL; i++) {
    stack_destroy(&((*hanoi_game)->towers[i].stack));
  }
  free(*hanoi_game);
  *hanoi_game = NULL;
  return TRUE;
}