#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef BOOLEAN_H 
#define BOOLEAN_H
#include "../boolean/boolean.h"
#endif

int str_len (char * str);
void str_split (char ** rest, char delimiter, char ** token);
Boolean str_between (char ** str, char init_char, char end_char);