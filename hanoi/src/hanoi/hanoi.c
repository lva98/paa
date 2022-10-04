#include "private_hanoi.h"

Boolean create_hanoi_game (Hanoi_Game * hanoi_game) {
  (*hanoi_game) = (Hanoi_Game) malloc(sizeof(struct Hanoi_Game));
  if (*hanoi_game == NULL) {
    return FALSE;
  }
  (*hanoi_game)->size = 0;

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
      int length;
      if (!stack_length(curr_stack, &length)) {
        return FALSE;
      }
      for (int j = 0; j < length; j++) {
        Hanoi_Disk * disk;
        stack_pop(curr_stack, (void **) &disk);
        stack_push(temp_tower_stack, disk);
        free(disk);
      }
    }
  }

  // Passo 2: Desempilha da torre temporária -> empilha nas torres coloridas
  int temp_length;
  if (!stack_length(temp_tower_stack, &temp_length)) {
    return FALSE;
  }
  for (int i = 0; i < temp_length; i++) {
    Hanoi_Disk * disk;
    stack_pop(temp_tower_stack, (void **) &disk);
    Stack target_stack = hanoi_game->towers[disk->color].stack;
    stack_push(target_stack, disk);
    free(disk);
  }

  return TRUE;
}

void recursive_show (Hanoi_Tower * tower, void (*f1)(Hanoi_Color), void (*f2)(Hanoi_Color, int, Boolean), Boolean first) {
  Hanoi_Disk * disk = NULL;
  stack_pop(tower->stack, (void **) &disk);
  
  if (disk == NULL) {
    f1(tower->color);
    return;
  }

  recursive_show(tower, f1, f2, FALSE);
  f2(disk->color, disk->index, first);
}

Boolean show (Hanoi_Game hanoi_game, void (*f1)(Hanoi_Color), void (*f2)(Hanoi_Color, int, Boolean), void (*f3)()) {
  for (int i = 0; i < TOWERS_TOTAL; i++) {
    if (hanoi_game->used_tower[i]) {
      recursive_show(&(hanoi_game->towers[i]), f1, f2, TRUE);
      f3();
    }
  }
  return TRUE;
}

Boolean destroy_hanoi (Hanoi_Game * hanoi_game) {
  free(*hanoi_game);
  return TRUE;
}