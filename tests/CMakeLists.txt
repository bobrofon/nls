cmake_minimum_required(VERSION 2.8)

find_package(GTest REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

set(NLS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(NLS_TESTS_DIR "${NLS_ROOT}/tests")

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${NLS_ROOT}/interfaces)

include("${NLS_TESTS_DIR}/lock_lib/lock_types/test/CMakeLists.txt")
include("${NLS_TESTS_DIR}/lock_lib/lock_logic/test/CMakeLists.txt")

add_executable(run_all_test ${GLOBAL_TEST_SRC})
target_link_libraries(run_all_test ${GTEST_BOTH_LIBRARIES} ${Boost_LIBRARIES})
