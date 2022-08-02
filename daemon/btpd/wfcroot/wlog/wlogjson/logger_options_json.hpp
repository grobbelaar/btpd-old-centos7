//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlogjson/basic_logger_options_json.hpp>
#include <wlogjson/custom_logger_options_json.hpp>
#include <wlog/logger/logger_options.hpp>
#include <wjson/json.hpp>
#include <wjson/name.hpp>

namespace wlog{
struct logger_options_json
{
  JSON_NAME(customize)
  typedef wjson::object<
    logger_options,
    wjson::member_list<
      wjson::base<basic_logger_options_json>,
      wjson::member<n_customize, logger_options, logger_options::customize_list, &logger_options::customize, wjson::vector_of<custom_logger_options_json> >
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}
