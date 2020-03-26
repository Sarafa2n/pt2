#include <stdio.h>
#include "lib/sequential.h"
#include "lib/parallel.h"
#include <sys/sysinfo.h>

int main(int argc, char const* argv[])
{

    if (argc < 2)
    {
        printf("%d", argc);
        printf("Файл не передан");
        return -1;
    }

    const char* filename = argv[1];

    int child_count = get_nprocs(), status = 0, result = parallel(filename, child_count, &status);
    if (status > 0)
    {
        printf("\nParalell result = %d\n", result);
    }

    result = sequential(filename, &status);
    if (status > 0)
    {
        printf("\nSequential result = %d\n", result);
    }

    return 0;
}
