#include "parallel.h"


int parallel(const char* filename, int child_count) {

    int parent[2],
        child[2];

    pipe(parent);
    pipe(child);

    int size = check_file(filename);

    if(!size) {
        return 0;
    }

    int *array = input_array(filename, size),
        *border_array = mmap(NULL, (child_count + 1) * sizeof(long int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

    pid_t pid,
          shut_down[child_count];

    int need_child = search_for_borders(array, border_array, size, child_count);

    for(int i = 0; i < need_child; ++i) {

        pid = fork();

        if(pid < 0){
            printf("Error with fork()\n");
        }

        if(pid == 0) {
            child_working(array, border_array, parent, child, i);
            exit(EXIT_SUCCESS);
        } else {
            shut_down[i] = pid;
        }
    }

    int child_in_work = need_child,
        current_sequence = 0,
        max_sequence = 0;

    if(pid > 0) {
        while(child_in_work) {

            write(parent[1], &child_in_work, sizeof(int));
            read(child[0], &current_sequence, sizeof(int));

            max_sequence = max_sequence < current_sequence ? current_sequence : max_sequence;
            child_in_work--;
        }

        int status;

        for(int i = 0; i < need_child; ++i) {

            waitpid(shut_down[i], &status, 0);

            if(WIFSIGNALED(status)) {
                printf("Error\n");
            }
        }

        free(array);
        munmap(border_array, 5000);
    }


    return max_sequence;
}

int search_for_borders(const int *array, int *border_array, int size, int child_count) {

    if(!check_array(array) || !check_array(border_array) || !size) {
        return 0;
    }

    int first_point = 0,
        step = size / child_count,
        second_point = step,
        border_count = 0;

    for(int i = 0; i < child_count; ++i) {

        if(i == child_count) {
            border_array[i + 1] = size;
            border_count++;
            break;
        }

        while (array[second_point] < array[second_point + 1]) {
            second_point++;
            if (second_point + 1 == size) {
                break;
            }
        }

        border_array[i] = first_point;
        border_array[i + 1] = ++second_point;
        border_count++;

        if(second_point == size) {
            break;
        }

        first_point = second_point;
        second_point += step;

        if(second_point >= size) {
            border_array[i + 1] = first_point;
            border_array[i + 2] = size;
            border_count++;
            break;
        }
    }

    return border_count;
}

void child_working(const int* array, const int *border_array,int *parent, int *child, int child_id) {

    int command = 0;
    read(parent[0], &command, sizeof(int));

    int head = border_array[child_id],
        tail = border_array[child_id + 1];

    int result = found_max_sequence(array, head, tail);

    write(child[1], &result, sizeof(int));
}
