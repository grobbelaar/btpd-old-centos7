//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011-2016
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wjrpc/handler/aspect/tags.hpp>
#include <wjrpc/logger.hpp>
#include <iostream>

namespace wjrpc{

struct ad_initialize
{
  template<typename T, typename Opt>
  void operator()(T& t, const Opt& opt)
  {
    t._sender_handler = opt.sender_handler;
    t.get_aspect().template get<_target_>() = opt.target;
    t.get_aspect().template get<_peeper_>() = opt.peeper;
  }
};

} // wjrpc


