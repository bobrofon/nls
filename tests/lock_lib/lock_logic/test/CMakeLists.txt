cmake_minimum_required(VERSION 2.8)

set(LOCK_LOGIC_TEST_ROOT "lock_lib/lock_logic")
set(LOCK_LOGIC_TEST_SRC_DIR "${NLS_TESTS_DIR}/${LOCK_LOGIC_TEST_ROOT}/test")

set(LOCK_LOGIC_TEST_SRC
	${LOCK_LOGIC_TEST_SRC_DIR}/lock_type_set_test_case.cpp
)

set(GLOBAL_TEST_SRC ${GLOBAL_TEST_SRC}
	${LOCK_LOGIC_TEST_SRC}
)

include_directories("${NLS_ROOT}/modules/${LOCK_LOGIC_TEST_ROOT}/include")

add_executable(run_lock_logic_test ${LOCK_LOGIC_TEST_SRC})
target_link_libraries(run_lock_logic_test ${GTEST_BOTH_LIBRARIES})
