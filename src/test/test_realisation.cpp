#include <gtest/gtest.h>
#include "test_realisation.h"

TEST(test_interval, invalid_data) {
    int result = search_for_borders(NULL, NULL, 0, 0);

    EXPECT_EQ(result, ERROR_CODE);

    int array[] = {1, 2, 3};

    result = search_for_borders(NULL, array, 0, 0 );
    EXPECT_EQ(result, ERROR_CODE);

    result = search_for_borders(array, array, 0, 0);
    EXPECT_EQ(result, ERROR_CODE);

}

TEST(test_interval, valid_data) {
    int border_array[5] = {0},
        array[] = {1, 2, 3, 4},
        result = search_for_borders(array, border_array , 4, 4);

    EXPECT_EQ(result, 1);

    int array1[] = {0, 1, 2, -1, 2, 3, 4, 5};

    result = search_for_borders(array1, border_array, 8, 4);
    EXPECT_EQ(result, 2);
}

TEST(test_realisation, small_file) {

    const char *filename = "../src/test/files/test_1.txt";
    int result_parallel,
        result_sequential;
    {
        TimeWork()
        result_parallel = parallel(filename, get_nprocs());
    }

    {
        TimeWork()
        result_sequential = sequential(filename);
    }

    EXPECT_EQ(result_parallel,result_sequential);
}

TEST(test_realisation, large_file) {
    const char *filename = "../src/test/files/stress_test.txt";
    int result_parallel,
            result_sequential;

    {
        TimeWork()
        result_parallel = parallel(filename, get_nprocs());
    }

    {
        TimeWork()
        result_sequential = sequential(filename);
    }

    EXPECT_EQ(result_parallel,result_sequential);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
