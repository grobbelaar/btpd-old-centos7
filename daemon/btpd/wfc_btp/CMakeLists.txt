cmake_minimum_required(VERSION 2.8)

project(wfc_btp)

include_directories(package)
include_directories(libbtp)

add_subdirectory(libbtp)
add_subdirectory(package)

