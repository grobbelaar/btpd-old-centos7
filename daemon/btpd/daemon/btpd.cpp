#include <wfc/wfc.hpp>
#include <wfcroot/wfcroot.hpp>
#include "btpd_build_info.h"
#include "btp_package.hpp"


int main(int argc, char* argv[])
{
  return wfc::wfc<btpd_build_info>( wfc::wfcroot({
    std::make_shared< wamba::btp::btp_package>()
  })).run(argc, argv);
}
