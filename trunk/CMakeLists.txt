PROJECT(CUL)

###
# Version information
###

SET(CUL_MAJOR_VERSION 0)
SET(CUL_MINOR_VERSION 0)
SET(CUL_PATCH_VERSION 21)
SET(CUL_VERSION "${CUL_MAJOR_VERSION}.${CUL_MINOR_VERSION}.${CUL_PATCH_VERSION}")

###
# Platform checks
###

INCLUDE (CheckFunctionExists)

CHECK_FUNCTION_EXISTS(asprintf HAVE_ASPRINTF)

###
# Configure build type
###

# set compiler cflags
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -Wmissing-declarations -Werror")

# set one line errors from gcc
IF(CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)
IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

###
# Sources
###

SET(CUL_SOURCES
	src/cul_error.c
	src/cul_log.c
	src/cul_mem.c
	src/cul_stream.c

	src/cul_str.c
	src/cul_str_type.c
	src/cul_string.c

	src/cul_arg.c
	src/cul_file.c
	src/cul_slist.c
	src/cul_list.c
	src/cul_tree.c
	src/cul_bbtree.c

	src/base/cul_base_basic.c
	src/base/cul_base_alg.c
	src/base/cul_base_io.c

	src/cul_rng.c
	src/cul_random.c
	src/cul_permutation.c

	src/cul_vector.c
	src/cul_matrix.c
)

# set output directories
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# headers directories
SET(CUL_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
SET(CUL_HEADERS_PRIVATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/private)
SET(CUL_CONFIG_DIR ${PROJECT_BINARY_DIR}/include)

# create configuration
SET(CUL_CONFIG ${CUL_CONFIG_DIR}/cul/cul_config.h)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cul_config.h.in "${CUL_CONFIG}" ESCAPE_QUOTES)

# set compiler variables
INCLUDE_DIRECTORIES(${CUL_CONFIG_DIR} ${CUL_HEADERS_DIR} ${CUL_HEADERS_PRIVATE_DIR})

# add target
ADD_LIBRARY(cul SHARED ${CUL_SOURCES})
SET_TARGET_PROPERTIES(cul PROPERTIES
	LINKER_LANGUAGE C
	VERSION ${CUL_VERSION}
	SOVERSION ${CUL_MAJOR_VERSION}
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
INCLUDE(CMakeTests.txt)

# install target
FILE(GLOB CUL_HEADERS ${CUL_HEADERS_DIR}/cul/*h)
INSTALL(FILES ${CUL_CONFIG} DESTINATION include/cul)
INSTALL(FILES ${CUL_HEADERS} DESTINATION include/cul)
INSTALL(TARGETS cul LIBRARY DESTINATION lib)
