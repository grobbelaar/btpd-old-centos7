//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011-2016
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wjrpc/method/aspect/tags.hpp>
#include <wjrpc/logger.hpp>
#include <wjson/error.hpp>
#include <wjson/strerror.hpp>
#include <fas/aop.hpp>
#include <memory>

namespace wjrpc{
  
struct process_response
  : fas::type<_process_response_, process_response>
{
  template<typename T, typename JResult, typename JError>
  static inline void process(
    incoming_holder holder, 
    std::function< void (
      std::unique_ptr<typename JResult::target>, 
      std::unique_ptr<typename JError::target>
    )> callback
  ) 
  {
    // получатель
    if ( holder.is_response() )
    {
      ::wjson::json_error e;
      auto pres = holder.template get_result<JResult>(&e);
      if ( !e )
      {
        callback( std::move(pres), nullptr);
      }
      else
      {
        callback( nullptr, nullptr);
      }
    }
    else if ( holder.is_error() )
    {
      ::wjson::json_error e;
      auto perr = holder.template get_error<JError>(&e);
      if ( !e )
      {
        callback( nullptr, std::move(perr) );
      }
      else
      {
        callback( nullptr, nullptr);
      }
    }
    else
    {
      callback( nullptr, nullptr);
    }
  }
};

struct process_response_proxy
  : fas::type<_process_response_, process_response_proxy>
{
  template<typename T, typename JResult, typename JError>
  static inline void process(
    incoming_holder holder, 
    std::function< void(
      std::unique_ptr<typename JResult::target>, 
      std::unique_ptr<typename JError::target>
    )> callback
  ) 
  {
    return T::aspect::template advice_cast<_process_response_>::type
            ::template process<T, JResult, JError>( 
                std::move(holder), 
                std::move(callback) 
              );
  }
};


} // wjrpc


