cmake_minimum_required(VERSION 2.8)

set(LOCK_TYPES_TEST_ROOT "lock_lib/lock_types")
set(LOCK_TYPES_TEST_SRC_DIR "${NLS_TESTS_DIR}/${LOCK_TYPES_TEST_ROOT}/test")

set(LOCK_TYPES_TEST_SRC
	${LOCK_TYPES_TEST_SRC_DIR}/lock_types_def_test_case.cpp
	${LOCK_TYPES_TEST_SRC_DIR}/lock_types_io_test_case.cpp
	${LOCK_TYPES_TEST_SRC_DIR}/lock_types_operation_test_case.cpp
)

set(GLOBAL_TEST_SRC ${GLOBAL_TEST_SRC}
	${LOCK_TYPES_TEST_SRC}
)

include_directories("${NLS_ROOT}/interfaces/${LOCK_TYPES_TEST_ROOT}")

add_executable(run_lock_types_test ${LOCK_TYPES_TEST_SRC})
target_link_libraries(run_lock_types_test ${GTEST_BOTH_LIBRARIES})
