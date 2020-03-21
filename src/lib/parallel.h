#ifndef DZ_PARALLEL_H
#define DZ_PARALLEL_H

#include "utils.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

int search_for_borders(const int *array, int *border_array, int size, int child_count);
int parallel(const char * filename, int child_count);
void child_working(const int* array, const int *border_array,int *parent, int *child, int child_id);

#endif //DZ_PARALLEL_H
