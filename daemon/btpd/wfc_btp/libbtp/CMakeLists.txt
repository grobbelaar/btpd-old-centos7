cmake_minimum_required(VERSION 2.8)

project(libbtp)

include_directories(${CMAKE_SOURCE_DIR}/wfcroot/wrtstat)
include_directories(.)

add_subdirectory(btp)

if ( BUILD_TESTING OR BTP_BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
