cmake_minimum_required(VERSION 2.8)

set(LOCK_TYPES_TEST_ROOT "lock_lib/lock_types")

set(LOCK_TYPES_TEST_SRC
	lock_types_def_test_case.cpp
)

set_source_files_properties(${LOCK_TYPES_TEST_SRC} PROPERTIES COMPILE_FLAGS "${CXXFLAGS}")

add_library(lock_types_test STATIC ${LOCK_TYPES_TEST_SRC})

include_directories("${NLS_ROOT}/interfaces/${LOCK_TYPES_TEST_ROOT}" ${GTEST_INCLUDE_DIR})
