#ifndef DZ_PARALLEL_H
#define DZ_PARALLEL_H

#include "utils.h"
#include "code_error.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

void search_for_borders(const int *array, int *border_array, int size, int child_count, int *status);
int parallel(const char* filename, int child_count, int *status);
void child_working(const int* array, const int *border_array,int *parent, int *child, int child_id);
int counting_number_children(const int * border_array, int child_count, int *status);

#endif //DZ_PARALLEL_H
