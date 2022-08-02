include(BuildInfo)

include_directories(${CMAKE_SOURCE_DIR}/wfcroot/wfc)
include_directories(.)

SET(
  btp_source_list
  btp_package.cpp
  
  rt/rt_module.cpp
  rt/domain/rt_domain.cpp
  rt/domain/rt_domain_multiton.cpp
  rt/service/rt_service_multiton.cpp
  
  ag/ag_module.cpp
  ag/domain/ag_domain.cpp
  ag/domain/ag_domain_multiton.cpp
  ag/service/ag_service_multiton.cpp
  ag/gateway/ag_gateway_multiton.cpp
  ag/deprecated/btp_deprecated_gateway_multiton.cpp
)

add_library(
  wfc_btp
  ${btp_source_list}
)

build_info(wfc_btp btp)

target_link_libraries(wfc_btp rocksdb btpstorage)
add_dependencies(wfc_btp facebook-rocksdb btpstorage)

install(TARGETS wfc_btp DESTINATION ${CMAKE_INSTALL_PREFIX})
