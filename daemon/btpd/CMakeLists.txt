cmake_minimum_required(VERSION 2.8)

project(btpd)

set(WFC_ENABLE_STAT ON)

if ( NOT WFC_READY )
  set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/wfcroot/wfc/cmake")
  include(Wfc)
endif()

include_directories(${CMAKE_SOURCE_DIR}/facebook-rocksdb)
include_directories(${CMAKE_SOURCE_DIR}/facebook-rocksdb/include)
include_directories(${CMAKE_SOURCE_DIR}/wfc_btp/package)
include_directories(${CMAKE_SOURCE_DIR}/wfcroot/wfc)
include_directories(${CMAKE_SOURCE_DIR}/wfcroot/wrtstat)

link_directories(${CMAKE_SOURCE_DIR}/facebook-rocksdb)
enable_testing()
add_subdirectory(utils)
add_subdirectory(wfc_btp)
add_subdirectory(daemon)
set(BUILD_TESTING OFF)
add_subdirectory(wfcroot)

# facebook-rocksdb
add_custom_target( 
  facebook-rocksdb
  COMMAND make shared_lib DEBUG_MODE=0 VERBOSE=1
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/facebook-rocksdb
  VERBATIM
)
link_directories(${CMAKE_SOURCE_DIR}/facebook-rocksdb)
include_directories(${CMAKE_SOURCE_DIR}/facebook-rocksdb)
include_directories(${CMAKE_SOURCE_DIR}/facebook-rocksdb/include)

