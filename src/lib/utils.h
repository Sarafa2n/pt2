#ifndef DZ_UTILS_H
#define DZ_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "code_error.h"


int check_file(const char* filename);
int* input_array(const char* filename, int* size, int * status);
int check_array(const int *array);
int found_max_sequence(const int *array, int head, int tail, int *status);


#endif //DZ_UTILS_H
