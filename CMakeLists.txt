cmake_minimum_required(VERSION 3.7)
project(DZ)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_executable(${PROJECT_NAME} src/main.c)

add_subdirectory(src/lib)
target_link_libraries(DZ Sequential Parallel)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_utils src/test/test_utils.cpp src/test/test_utils.h)
add_executable(test_realisation src/test/test_realisation.cpp src/test/test_realisation.h)

enable_testing()

add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/tests_gtest)

target_link_libraries(test_utils ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} Utils)
target_link_libraries(test_realisation ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} Sequential Parallel)