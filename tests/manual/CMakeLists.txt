cmake_minimum_required(VERSION 2.8)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../modules/lock_service ${CMAKE_CURRENT_BINARY_DIR}/lock_service)

add_executable(run main.cpp)

target_link_libraries(run nls)
