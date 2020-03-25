#include "utils.h"

//  проверка на существование файла
int check_file(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return FILE_EMPTY;
    }

    return OK;
}

//ввод массива из файла
int* input_array(const char* filename, int* size, int* status)
{
    *status = check_file(filename);
    if (*status != 1)
    {
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    fscanf(file, "%d", size);

    int* array = malloc(*size * sizeof(int));
    *status = check_array(array);
    if (*status != 1)
    {
        return NULL;
    }

    for (int i = 0; i < *size; i++)
    {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);

    return array;
}

// проверка массива
int check_array(const int* array)
{
    if (array == NULL)
    {
        return ARRAY_EMPTY;
    }

    return 1;
}

//поиск максмиальной строго возрастающей последовательности на отрезке
int found_max_sequence(const int* array, int head, int tail, int* status)
{
    int sequence_size = 1, buffer_size = 1;

    if (!check_array(array) || head > tail || head == tail)
    {
        *status = PARAMETER_ERROR;
        return -1;
    }

    for (int i = head; i < tail; i++)
    {
        if (array[i] < array[i + 1] && (i + 1) < tail)
        {
            buffer_size++;
            continue;
        }

        if (array[i] > array[i + 1] && (i + 1) < tail)
        {
            sequence_size = sequence_size < buffer_size ? buffer_size : sequence_size;
            buffer_size = 1;
            continue;
        }

        if (i + 1 == tail)
        {
            if (array[i - 1] < array[i] && buffer_size > sequence_size)
            {
                sequence_size = buffer_size;
                continue;
            }
        }
    }

    return sequence_size;
}