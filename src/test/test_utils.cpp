#include <gtest/gtest.h>
#include "test_utils.h"

TEST(read_func, incorrect_input) {
    int size = check_file(NULL);

    EXPECT_EQ(size, ERROR_CODE);
}

TEST(read_func, correct_input) {
    int size = check_file("../src/test/files/test_1.txt");

    EXPECT_EQ(size,11);
}

TEST(found_func, correct_data) {
    int array[] ={ 1, 2, 3, 4, 5 },
        result = found_max_sequence(array,0,5);

    EXPECT_EQ(result,5);
}

TEST(found_func, incorrect_data) {
    int result = found_max_sequence(NULL,0,0);

    EXPECT_EQ(result,ERROR_CODE);

    int array[] ={ 1, 2, 3, 4, 5 };

    result = found_max_sequence(array,10, 0);
    EXPECT_EQ(result,ERROR_CODE);

    result = found_max_sequence(array,0,0);
    EXPECT_EQ(result,ERROR_CODE);

}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}