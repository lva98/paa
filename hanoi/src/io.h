#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hanoi/hanoi.h"
#include "utils/utils.h"

// Formatação entrada
Hanoi_Color str2color (char * str);
char * color2str (Hanoi_Color color);
Boolean read_input (Hanoi_Game hanoi);

// Formatação saída
void print_tower (Hanoi_Color tower_color);
void print_disk (Hanoi_Color disk_color, int index, Boolean last);
void next_tower ();