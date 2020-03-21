#ifndef DZ_UTILS_H
#define DZ_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int check_file(const char* filename);
int* input_array(const char* filename, int size);
int check_array(const int *array);
int found_max_sequence(const int *array, int head, int tail);
int * get_array_from_file(const char *filename);

#endif //DZ_UTILS_H
