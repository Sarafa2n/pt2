#include "sequential.h"

int sequential(const char* filename) {

    int size = check_file(filename);

    if(!size) {
        return 0;
    }

    int *array = input_array(filename, size);

    if(!array) {
        return 0;
    }

    int result = found_max_sequence(array, 0, size);

    free(array);

    return result;
}

