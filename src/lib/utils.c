#include "utils.h"


int check_file(const char* filename) {
    FILE *file = fopen(filename, "r");

    if(file == NULL) {
        return 0;
    }

    int size;

    fscanf(file,"%d", &size);
    fclose(file);

    return size;
}

int* input_array(const char* filename, int size) {

    int *array = malloc(size * sizeof(int));

    if(!check_array(array)) {
        return NULL;
    }


    FILE *file = fopen(filename, "r");

    int elem;
    fscanf(file,"%d",&elem);

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);

    return array;
}

int check_array(const int *array) {
    if(array == NULL) {
        return 0;
    }

    return 1;
}

int found_max_sequence(const int *array, int head, int tail) {
    int sequence_size = 1,
        buffer_size = 1;

    if(!check_array(array)) {
        return 0;
    }

    if(head > tail || head == tail) {
        return 0;
    }

    for(int i = head; i < tail; i++) {
        if (array[i] < array[i + 1] && (i + 1) < tail) {
            buffer_size++;
            continue;
        }

        if (array[i] > array[i + 1] && (i + 1) < tail) {
            sequence_size = sequence_size < buffer_size ? buffer_size : sequence_size;
            buffer_size = 1;
            continue;
        }

        if (i + 1 == tail) {
            if (array[i - 1] < array[i] && buffer_size > sequence_size) {
                sequence_size = buffer_size;
                continue;
            }
        }
    }

    return sequence_size;
}
