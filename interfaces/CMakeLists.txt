project (NLS)

cmake_minimum_required(VERSION 2.8.6)

set(NLS_INC
	"lock_service/lock_client_interface.hpp"
	"lock_service/lock_query_interface.hpp"
	"lock_lib/lock_types/lock_types_def.hpp"
)

include(GNUInstallDirs)
install(FILES ${NLS_INC} DESTINATION ${DESTDIR}${CMAKE_INSTALL_INCLUDEDIR}/nls COMPONENT devel)
