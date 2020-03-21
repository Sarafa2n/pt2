#include <stdio.h>
#include "lib/sequential.h"
#include "lib/parallel.h"
#include <sys/sysinfo.h>

int main(int argc, char const *argv[]) {

    if(argc < 2) {
        printf("%d", argc);
        printf("Файл не передан");
        return -1;
    }

    const char* filename = argv[1];

    int child_count = get_nprocs(),
        result = parallel(filename, child_count);

    printf("\nParalell result = %d\n", result);

    result = sequential(filename);
    printf("\nSequential result = %d\n", result);

    return 0;
}
