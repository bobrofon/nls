cmake_minimum_required(VERSION 2.8)

set(UTILS_TEST_ROOT "utils")
set(UTILS_TEST_SRC_DIR "${NLS_TESTS_DIR}/${UTILS_TEST_ROOT}/test")

set(UTILS_TEST_SRC
	${UTILS_TEST_SRC_DIR}/config_test_case.cpp
)

set(GLOBAL_TEST_SRC ${GLOBAL_TEST_SRC}
	${UTILS_TEST_SRC}
)

set(GLOBAL_TEST_LDADD ${GLOBAL_TEST_LDADD}
	utils
)

add_subdirectory(${NLS_ROOT}/modules/utils ${CMAKE_CURRENT_BINARY_DIR}/utils)

add_executable(run_utils_test ${UTILS_TEST_SRC})
target_link_libraries(run_utils_test ${GTEST_BOTH_LIBRARIES} ${GLOBAL_TEST_LDADD} utils)


