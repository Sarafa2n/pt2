#include "parallel.h"

// Паралельная реализация поиска максимальной строго возрастающей последовательности в массиве
int parallel(const char* filename, int child_count, int* status)
{
    if (child_count == 0)
    {
        error_checking(CHILD_ERROR);
        return -1;
    }

    int parent[2] = {}, child[2] = {};
    pipe(parent);
    pipe(child);

    int size = 0;
    int* array = input_array(filename, &size, status);
    if (error_checking(*status) != 1)
    {
        return -1;
    }

    int* border_array = mmap(NULL, (child_count + 1) * sizeof(long int), PROT_READ | PROT_WRITE,
                             MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    *status = check_array(border_array);
    if (error_checking(*status) != 1)
    {
        return -1;
    }

    search_for_borders(array, border_array, size, child_count, status);
    child_count = counting_number_children(border_array, child_count, status);
    if (error_checking(*status) != 1)
    {
        return -1;
    }

    pid_t pid;
    pid_t* shut_down = malloc(child_count * sizeof(pid_t));
    *status = check_array(shut_down);
    if (error_checking(*status) != 1)
    {
        return -1;
    }

    int* status_array = mmap(NULL, child_count * sizeof(long int), PROT_READ | PROT_WRITE,
                             MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    *status = check_array(status_array);
    if (*status != 1)
    {
        return -1;
    }

    for (int i = 0; i < child_count; ++i)
    {
        pid = fork();
        if (pid < 0)
        {
            printf("Error with fork()\n");
            break;
        }

        if (pid == 0)
        {
            child_working(array, border_array, parent, child, i);
            exit(EXIT_SUCCESS);
        }
        else
        {
            shut_down[i] = pid;
        }
    }

    int child_in_work = child_count, current_sequence = 0, max_sequence = 0;

    if (pid > 0)
    {
        while (child_in_work)
        {
            write(parent[1], &child_in_work, sizeof(int));
            read(child[0], &current_sequence, sizeof(int));

            max_sequence = max_sequence < current_sequence ? current_sequence : max_sequence;
            child_in_work--;
        }

        int status = 0;
        for (int i = 0; i < child_count; ++i)
        {
            waitpid(shut_down[i], &status, 0);
            if (WIFSIGNALED(status))
            {
                printf("Error\n");
            }
        }

        free(shut_down);
        free(array);
        munmap(border_array, 5000);
    }


    return max_sequence;
}

//поиск родителем отрезков для работы детей
void search_for_borders(const int* array, int* border_array, int size, int child_count, int* status)
{
    if (!check_array(array) || !check_array(border_array) || !size)
    {
        status[child_count] = PARAMETER_ERROR;
        return;
    }

    int first_point = 0, step = size / child_count, second_point = step;

    for (int i = 0; i < child_count; ++i)
    {
        if (i == child_count)
        {
            border_array[i + 1] = size;
            break;
        }

        while (array[second_point] < array[second_point + 1])
        {
            second_point++;
            if (second_point + 1 == size)
            {
                break;
            }
        }

        border_array[i] = first_point;
        border_array[i + 1] = ++second_point;

        if (second_point == size)
        {
            break;
        }

        first_point = second_point;
        second_point += step;

        if (second_point >= size)
        {
            border_array[i + 1] = first_point;
            border_array[i + 2] = size;
            break;
        }
    }
}

//подсчет количеста детей, которых нужно задействовать
int counting_number_children(const int* border_array, int child_count, int* status)
{

    int buffer_count = child_count;

    if (!check_array(border_array) || child_count == 0)
    {
        *status = PARAMETER_ERROR;
        return 0;
    }

    for (int i = child_count; i >= 0; --i)
    {
        if (border_array[i] == 0 && i > 0)
        {
            buffer_count = i - 1;
        }
    }
    return buffer_count;
}


//работа ребенка на отрезке массива
void child_working(const int* array, const int* border_array, int* parent, int* child, int child_id)
{
    int command = 0;
    read(parent[0], &command, sizeof(int));

    int head = border_array[child_id], tail = border_array[child_id + 1];

    int status = 0;
    int result = found_max_sequence(array, head, tail, &status);
    write(child[1], &result, sizeof(int));

    if (error_checking(status) != 1)
    {
        exit(EXIT_FAILURE);
    }
}
