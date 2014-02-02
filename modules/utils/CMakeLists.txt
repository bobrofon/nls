cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS filesystem system REQUIRED)

set(UTILS_SRC
	"src/global_config.cpp"
)

if(UNIX AND NOT APPLE)
	set(CXXFLAGS "${CXXFLAGS} -fPIC")
endif()

set_source_files_properties(${UTILS_SRC} PROPERTIES COMPILE_FLAGS "${CXXFLAGS}")

include_directories(${Boost_INCLUDE_DIRS})
include_directories("include")

add_library(utils STATIC ${UTILS_SRC})

target_link_libraries(utils ${Boost_LIBRARIES})
