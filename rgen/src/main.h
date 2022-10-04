#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tda/pub_rgen.h"

#define TRUE 1
#define FALSE 0

short calculate_data_size (size_t * data_size, char * data_type);
short read_and_compute_input (PP_Rgen);
short print_rgen_node (char * data_type, void * data);
short string_to_data_type (char * data_type, void * data);
short convert_to_data_type (char * data_type, size_t data_size, char * data, void ** converted_data);
void str_split (char ** rest, char delimiter, char ** token);

