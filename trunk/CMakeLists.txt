PROJECT(CUL)

# make verbose compiling
SET(CMAKE_VERBOSE_MAKEFILE TRUE)

# possibilities: Debug RelWithDebInfo MinSizeRel Release
SET(CMAKE_BUILD_TYPE Debug)

# set warning flags
IF(CMAKE_BUILD_TYPE STREQUAL Debug)
	SET(CMAKE_C_FLAGS "-Wall -Wextra -Wmissing-declarations -std=c99")
ELSE(CMAKE_BUILD_TYPE STREQUAL Debug)
	SET(CMAKE_C_FLAGS "-std=c99")
ENDIF(CMAKE_BUILD_TYPE STREQUAL Debug)

SET(CUL_MAJOR_VERSION 0)
SET(CUL_MINOR_VERSION 0)
SET(CUL_PATCH_VERSION 15)

SET(CUL_VERSION "${CUL_MAJOR_VERSION}.${CUL_MINOR_VERSION}.${CUL_PATCH_VERSION}")

SET(CUL_SOURCES
	src/cul_arg.c
	src/cul_file.c
	src/cul_error.c
	src/cul_list.c
	src/cul_log.c
	src/cul_matrix.c
	src/cul_mem.c
	src/cul_tree.c
	src/cul_tree_bb.c
	src/cul_vector.c
	src/cul_stream.c
	src/cul_string.c
	src/cul_string_raw.c
	src/cul_string_type.c

	src/base/cul_base_balg_search.c
	src/base/cul_base_balg_sort.c
	src/base/cul_base_balg_unique.c
	src/base/cul_base_common.c
	src/base/cul_base_copy.c
	src/base/cul_base_io.c
	src/base/cul_base_minmax.c
	src/base/cul_base_oper.c
	src/base/cul_base_stat.c
)

# headers directory
SET(CUL_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(CUL_HEADERS_PRIVATE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/private")
SET(CUL_HEADERS_CONFIG "${PROJECT_BINARY_DIR}")

# create configuration
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cul_config.h.in "${CUL_HEADERS_CONFIG}/cul/cul_config.h" ESCAPE_QUOTES)

# set compiler variables
INCLUDE_DIRECTORIES(${CUL_HEADERS_CONFIG} ${CUL_HEADERS_DIR} ${CUL_HEADERS_PRIVATE_DIR})

# add target
ADD_LIBRARY(cul STATIC ${CUL_SOURCES})
#ADD_LIBRARY(cul SHARED ${CUL_SOURCES})
SET_TARGET_PROPERTIES(cul PROPERTIES
	LINKER_LANGUAGE C
	VERSION ${CUL_VERSION}
	DEFINE_SYMBOL CUL_MODULE=\\"Cul\\"
)
