//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2016
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wjrpc/outgoing/outgoing_notify.hpp>
#include <wjrpc/outgoing/version_member.hpp>
#include <wjson/name.hpp>
#include <wjson/json.hpp>
#include <memory>
namespace wjrpc{

template<typename T>
struct outgoing_notify_json
{
  typedef typename T::target target;
  typedef outgoing_notify<target> request_type;
  typedef typename request_type::version_type version_type;
  typedef ::wjson::pointer<std::unique_ptr<target>, T> params_json;

  JSON_NAME(method)
  JSON_NAME(params)

  typedef ::wjson::object<
    request_type,
    ::wjson::member_list<
      version_member::type,
      ::wjson::member<n_method, request_type, std::string, &request_type::method>,
      ::wjson::member<n_params, request_type, std::unique_ptr<target>, &request_type::params, params_json >
    >
  > type;

  typedef typename type::serializer serializer;
};

}
