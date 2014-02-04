cmake_minimum_required(VERSION 2.8)

set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS thread REQUIRED)
find_package(Threads REQUIRED)

set(NET_SYNCHRONIZE_SRC
	"src/net_synchronize.cpp"
	"src/lock_client.cpp"
)

if(UNIX AND NOT APPLE)
	set(CXXFLAGS "${CXXFLAGS} -fPIC")
endif()

set_source_files_properties(${NET_SYNCHRONIZE_SRC} PROPERTIES COMPILE_FLAGS "${CXXFLAGS}")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../utils ${CMAKE_CURRENT_BINARY_DIR}/utils)

include_directories(${Boost_INCLUDE_DIRS})
include_directories("include" "../../interfaces")
include_directories("/usr/include/soci")
include_directories("/usr/include/mysql")

add_library(nls STATIC ${NET_SYNCHRONIZE_SRC})

target_link_libraries(nls utils ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
