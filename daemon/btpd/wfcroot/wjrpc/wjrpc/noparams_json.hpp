//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2016
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wjrpc/noparams.hpp>
#include <wjson/json.hpp>

namespace wjrpc{

struct noparams_json
{
  typedef ::wjson::object<
    noparams,
    ::wjson::member_list< >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
};

}