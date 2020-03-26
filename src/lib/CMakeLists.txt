add_library(Utils STATIC utils.h utils.c code_error.h code_error.c)
add_library(Parallel SHARED utils.h utils.c parallel.c parallel.h code_error.h code_error.c)
add_library(Sequential STATIC utils.h utils.c sequential.c sequential.h code_error.h code_error.c)