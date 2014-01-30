cmake_minimum_required(VERSION 2.8)

find_package(GTest REQUIRED)

set(NLS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")

set(NLS_TEST_SRC
	empty_stub.cpp
)

add_subdirectory("${NLS_ROOT}/modules/lock_lib/lock_types/test" "${CMAKE_CURRENT_BINARY_DIR}/lock_types")

set(NLS_TEST_LDADD
	${GTEST_LIBRARY}
	${GTEST_MAIN_LIBRARY}
	lock_types_test
)

add_executable(runUnitTests ${NLS_TEST_SRC})

target_link_libraries(runUnitTests ${NLS_TEST_LDADD})
