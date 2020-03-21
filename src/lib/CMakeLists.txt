add_library(Utils STATIC utils.h utils.c )
add_library(Parallel SHARED utils.h utils.c parallel.c parallel.h )
add_library(Sequential STATIC utils.h utils.c sequential.c sequential.h )