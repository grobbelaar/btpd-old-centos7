
find_package(Boost COMPONENTS system filesystem REQUIRED)

add_library(
  btpstorage
  storage.cpp
  key_aggregator.cpp
  key_cache.cpp
  key_storage.cpp
  key_rocksdb.cpp
  data_storage.cpp
  data_rocksdb.cpp
  shard_rocksdb.cpp
  data_storage.cpp
  aux.cpp
)

target_link_libraries(btpstorage wrtstat rocksdb ${Boost_LIBRARIES})
add_dependencies(btpstorage facebook-rocksdb )
