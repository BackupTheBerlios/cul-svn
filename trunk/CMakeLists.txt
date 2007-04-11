PROJECT(CUL)

###
# Version information
###

SET(CUL_MAJOR_VERSION 0)
SET(CUL_MINOR_VERSION 0)
SET(CUL_PATCH_VERSION 16)
SET(CUL_VERSION "${CUL_MAJOR_VERSION}.${CUL_MINOR_VERSION}.${CUL_PATCH_VERSION}")

###
# Platform checks
###

INCLUDE (CheckFunctionExists)

CHECK_FUNCTION_EXISTS(asprintf HAVE_ASPRINTF)

###
# Configure build type
###

# possibilities: Debug RelWithDebInfo MinSizeRel Release
SET(CMAKE_BUILD_TYPE Debug)

# set warning flags
IF(CMAKE_BUILD_TYPE STREQUAL Debug)
	SET(CMAKE_C_FLAGS "-Wall -Wextra -Wmissing-declarations -Werror -std=c99")
ELSE(CMAKE_BUILD_TYPE STREQUAL Debug)
	SET(CMAKE_C_FLAGS "-std=c99")
ENDIF(CMAKE_BUILD_TYPE STREQUAL Debug)


###
# Sources
###

SET(CUL_SOURCES
	src/cul_arg.c
	src/cul_file.c
	src/cul_error.c
	src/cul_slist.c
	src/cul_list.c
	src/cul_log.c
	src/cul_matrix.c
	src/cul_mem.c
	src/cul_random.c
	src/cul_rng.c
	src/cul_tree.c
	src/cul_tree_bb.c
	src/cul_vector.c
	src/cul_io.c
	src/cul_iof.c
	src/cul_str.c
	src/cul_str_type.c
	src/cul_string.c

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

# headers directories
SET(CUL_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(CUL_HEADERS_PRIVATE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/private")
SET(CUL_CONFIG_DIR "${PROJECT_BINARY_DIR}")

# more directories
SET(CUL_LIBRARY_DIR "${LIBRARY_OUTPUT_PATH}")
SET(CUL_EXECUTABLE_DIR "${EXECUTABLE_OUTPUT_PATH}")

# create configuration
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cul_config.h.in "${CUL_CONFIG_DIR}/cul/cul_config.h" ESCAPE_QUOTES)

# set compiler variables
INCLUDE_DIRECTORIES(${CUL_CONFIG_DIR} ${CUL_HEADERS_DIR} ${CUL_HEADERS_PRIVATE_DIR})

# add target
ADD_LIBRARY(cul ${CUL_SOURCES})
SET_TARGET_PROPERTIES(cul PROPERTIES
	LINKER_LANGUAGE C
	VERSION ${CUL_VERSION}
	DEFINE_SYMBOL CUL_MODULE=\\"cul\\"
)

GET_TARGET_PROPERTY(CUL_BUILD_TYPE cul TYPE)
IF("${CUL_BUILD_TYPE}" STREQUAL "STATIC_LIBRARY")
	MESSAGE(STATUS "Building static library -- using data and function sections")
	SET(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
ENDIF("${CUL_BUILD_TYPE}" STREQUAL "STATIC_LIBRARY")

# testing
ENABLE_TESTING()
ADD_SUBDIRECTORY(tests)
