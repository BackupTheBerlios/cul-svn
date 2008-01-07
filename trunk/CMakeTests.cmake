ADD_TEST(cul_vector-test ${CMAKE_CTEST_COMMAND}
	--build-and-test
	${CMAKE_CURRENT_SOURCE_DIR}/tests
	${CMAKE_CURRENT_BINARY_DIR}/tests
	--build-two-config
	--build-generator ${CMAKE_GENERATOR}
	--build-makeprogram ${CMAKE_MAKE_PROGRAM}
	--build-project CUL_TEST_MATRIX
	--build-options -DCUL_CONFIG_DIR=${CUL_CONFIG_DIR} -DCUL_INCLUDE_DIR=${CUL_HEADERS_DIR} -DCUL_LIBRARY_DIR=${LIBRARY_OUTPUT_PATH}
	--test-command ${CMAKE_CURRENT_BINARY_DIR}/tests/cul_vector-test)

ADD_TEST(cul_matrix-test ${CMAKE_CTEST_COMMAND}
	--build-and-test
	${CMAKE_CURRENT_SOURCE_DIR}/tests
	${CMAKE_CURRENT_BINARY_DIR}/tests
	--build-two-config
	--build-generator ${CMAKE_GENERATOR}
	--build-makeprogram ${CMAKE_MAKE_PROGRAM}
	--build-project CUL_TEST_MATRIX
	--build-options -DCUL_CONFIG_DIR=${CUL_CONFIG_DIR} -DCUL_INCLUDE_DIR=${CUL_HEADERS_DIR} -DCUL_LIBRARY_DIR=${LIBRARY_OUTPUT_PATH}
	--test-command ${CMAKE_CURRENT_BINARY_DIR}/tests/cul_matrix-test)

ADD_TEST(cul_rng-test ${CMAKE_CTEST_COMMAND}
	--build-and-test
	${CMAKE_CURRENT_SOURCE_DIR}/tests
	${CMAKE_CURRENT_BINARY_DIR}/tests
	--build-two-config
	--build-generator ${CMAKE_GENERATOR}
	--build-makeprogram ${CMAKE_MAKE_PROGRAM}
	--build-project CUL_TEST_RNG
	--build-options -DCUL_CONFIG_DIR=${CUL_CONFIG_DIR} -DCUL_INCLUDE_DIR=${CUL_HEADERS_DIR} -DCUL_LIBRARY_DIR=${LIBRARY_OUTPUT_PATH}
	--test-command ${CMAKE_CURRENT_BINARY_DIR}/tests/cul_rng-test)

ADD_TEST(cul_str-test ${CMAKE_CTEST_COMMAND}
	--build-and-test
	${CMAKE_CURRENT_SOURCE_DIR}/tests
	${CMAKE_CURRENT_BINARY_DIR}/tests
	--build-two-config
	--build-generator ${CMAKE_GENERATOR}
	--build-makeprogram ${CMAKE_MAKE_PROGRAM}
	--build-project CUL_TEST_STR
	--build-options -DCUL_CONFIG_DIR=${CUL_CONFIG_DIR} -DCUL_INCLUDE_DIR=${CUL_HEADERS_DIR} -DCUL_LIBRARY_DIR=${LIBRARY_OUTPUT_PATH}
	--test-command ${CMAKE_CURRENT_BINARY_DIR}/tests/cul_str-test)
