
include_directories(..)
include_directories(../wfc_btp/package)
add_executable(btpd btpd.cpp)

target_link_libraries(btpd wfc_btp wfcroot)
add_dependencies(btpd wfc_btp wfcroot )

include(BuildInfo)

build_info(btpd btpd)
