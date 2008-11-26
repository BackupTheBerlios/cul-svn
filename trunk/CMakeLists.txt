CMAKE_MINIMUM_REQUIRED(VERSION 2.4.6)

###
# Project
###

PROJECT(CUL)

###
# Additional Modules
###

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE(CMakeTemplates.cmake)

###
# Version information
###

SET(CUL_VERSION "0.0.28")
SET(CUL_SO_VERSION "0")

###
# Platform checks
###

INCLUDE(CheckFunctionExists)

CHECK_FUNCTION_EXISTS(asprintf HAVE_ASPRINTF)
CHECK_FUNCTION_EXISTS(stpcpy HAVE_STPCPY)

###
# Configure build type
###

# set compiler flags
SET(CUL_FLAGS "-std=c99")
SET(CUL_WARNINGS "-Wall -Wextra -Wmissing-declarations -Werror")

# apply compiler cflags
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CUL_FLAGS} ")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CUL_FLAGS} ${CUL_WARNINGS}")

###
# Sources
###

SET(CUL_SOURCES
    src/cul_error.c
    src/cul_log.c
    src/cul_mem.c
    src/cul_stream.c

    src/private/cul_sort_prv.c
    src/private/cul_copy_prv.c

    src/cul_dnode.c
    src/cul_dlist.c

    src/cul_snode.c
    src/cul_slist.c

    src/cul_tree.c

    src/cul_str.c
    src/cul_str_type.c
    src/cul_string.c

    src/cul_arg.c
    src/cul_file.c

    src/cul_rng.c
    src/cul_random.c
    src/cul_permutation.c
    src/cul_permute.c

    src/cul_vector.c
    src/cul_matrix.c
)

# set output directories
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# headers directories
SET(CUL_HEADERS_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/include)
SET(CUL_HEADERS_PRIVATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/private)
SET(CUL_HEADERS_BUILD_DIR         ${PROJECT_BINARY_DIR}/include)
SET(CUL_HEADERS_BUILD_PRIVATE_DIR ${PROJECT_BINARY_DIR}/include/private)

# create configuration
SET(CUL_CONFIG ${CUL_HEADERS_BUILD_DIR}/cul/cul_config.h)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cul_config.h.in "${CUL_CONFIG}")

# process template headers
CUL_TEMPLATE_HEADER(
    ${CUL_HEADERS_PRIVATE_DIR}/cul_sort_prv.h.in
    ${CUL_HEADERS_BUILD_PRIVATE_DIR}
    "${TEMPLATE_ALL}")
CUL_TEMPLATE_HEADER(
    ${CUL_HEADERS_PRIVATE_DIR}/cul_copy_prv.h.in
    ${CUL_HEADERS_BUILD_PRIVATE_DIR}
    "${TEMPLATE_ALL}")
CUL_TEMPLATE_HEADER(
    ${CUL_HEADERS_DIR}/cul/cul_vector.h.in
    ${CUL_HEADERS_BUILD_DIR}/cul/
    "${TEMPLATE_ALL}")
CUL_TEMPLATE_HEADER(
    ${CUL_HEADERS_DIR}/cul/cul_vector_io.h.in
    ${CUL_HEADERS_BUILD_DIR}/cul/
    "${TEMPLATE_ALL}")
CUL_TEMPLATE_HEADER(
    ${CUL_HEADERS_DIR}/cul/cul_matrix.h.in
    ${CUL_HEADERS_BUILD_DIR}/cul/
    "${TEMPLATE_BASIC}")
CUL_TEMPLATE_HEADER(
    ${CUL_HEADERS_DIR}/cul/cul_matrix_io.h.in
    ${CUL_HEADERS_BUILD_DIR}/cul/
    "${TEMPLATE_BASIC}")

# set compiler variables
INCLUDE_DIRECTORIES(${CUL_HEADERS_DIR} ${CUL_HEADERS_PRIVATE_DIR}
    ${CUL_HEADERS_BUILD_DIR} ${CUL_HEADERS_BUILD_PRIVATE_DIR})

# add target
ADD_LIBRARY(cul SHARED ${CUL_SOURCES})
SET_TARGET_PROPERTIES(cul PROPERTIES
    LINKER_LANGUAGE C
    VERSION ${CUL_VERSION}
    SOVERSION ${CUL_SO_VERSION}
    DEFINE_SYMBOL CUL_MODULE=\\"cul\\"
)

# set sections for static library
GET_TARGET_PROPERTY(CUL_BUILD_TYPE cul TYPE)
IF("${CUL_BUILD_TYPE}" STREQUAL "STATIC_LIBRARY")
	MESSAGE(STATUS "Building static library -- using data and function sections")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
ENDIF("${CUL_BUILD_TYPE}" STREQUAL "STATIC_LIBRARY")

# testing
ENABLE_TESTING()
INCLUDE(CMakeTests.cmake)

# extract header files to install
FILE(GLOB CUL_HEADERS
    ${CUL_HEADERS_DIR}/cul/*.h
    ${CUL_HEADERS_BUILD_DIR}/cul/*.h)

# install files
INSTALL(FILES ${CUL_HEADERS} DESTINATION include/cul)
INSTALL(TARGETS cul LIBRARY DESTINATION lib)

