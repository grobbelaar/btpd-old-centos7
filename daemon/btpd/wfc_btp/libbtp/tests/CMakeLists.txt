set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${WFC_TEST_DIR})

SET(
  storage_test_source_list
    storage_suite.cpp
    key_cache_suite.cpp
    key_aggregator_suite.cpp
    key_storage_suite.cpp
    data_storage_suite.cpp
    storage_test.cpp
    ${FAS_TESTING_CPP}
)

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCONFIG_PATH='${CMAKE_SOURCE_DIR}/tests'" )

add_executable(
  storage_test
  ${storage_test_source_list}
)

add_dependencies(storage_test btpstorage)

target_link_libraries(storage_test btpstorage )

add_test(NAME storage_test COMMAND storage_test WORKING_DIRECTORY ${WFC_TEST_DIR} )


