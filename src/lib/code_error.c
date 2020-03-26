#include "code_error.h"

int error_checking(int status)
{
    switch (status)
    {
        case FILE_EMPTY:
            printf("Файл пуст\n");
            break;
        case ARRAY_EMPTY:
            printf("Передан пустой массив\n");
            break;
        case PARAMETER_ERROR:
            printf("Ошибка передачи параметров в функцию\n");
            break;
        case CHILD_ERROR:
            printf("Ошибка передачи количества детей в функцию\n");
            break;

    }

    return status;
}

