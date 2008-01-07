INCLUDE_DIRECTORIES(${CUL_CONFIG_DIR} ${CUL_INCLUDE_DIR})
LINK_DIRECTORIES(${CUL_LIBRARY_DIR})

# set CFLAGS
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_C_FLAGS "-std=c99")

PROJECT(CUL_TEST_MATRIX)
ADD_EXECUTABLE(cul_vector-test "cul_vector-test.c")
TARGET_LINK_LIBRARIES(cul_vector-test cul)

PROJECT(CUL_TEST_MATRIX)
ADD_EXECUTABLE(cul_matrix-test "cul_matrix-test.c")
TARGET_LINK_LIBRARIES(cul_matrix-test cul)

PROJECT(CUL_TEST_RNG)
ADD_EXECUTABLE(cul_rng-test "cul_rng-test.c")
TARGET_LINK_LIBRARIES(cul_rng-test cul "-lm")

PROJECT(CUL_TEST_STR)
ADD_EXECUTABLE(cul_str-test "cul_str-test.c")
TARGET_LINK_LIBRARIES(cul_str-test cul)
