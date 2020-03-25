#include "sequential.h"

// Последовательная реализация поиска максимальной строго возрастающей последовательности в массиве
int sequential(const char* filename, int* status)
{
    int size = 0;
    int* array = input_array(filename, &size, status);
    if (error_checking(*status) != 1)
    {
        return -1;
    }

    int result = found_max_sequence(array, 0, size, status);
    if (error_checking(*status) != 1)
    {
        return -1;
    }

    free(array);

    return result;
}

