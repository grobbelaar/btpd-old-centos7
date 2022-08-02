//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011-2016
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wjrpc/incoming/incoming_holder.hpp>
#include <wjrpc/outgoing/outgoing_holder.hpp>
#include <wjrpc/method/aspect/tags.hpp>
#include <wjrpc/errors.hpp>
#include <wjrpc/logger.hpp>
#include <fas/aop/metalist.hpp>
#include <functional>
#include <memory>

namespace wjrpc{
  
template<typename JParams, typename JResult, typename JError = error_json>
struct remote_call
{
  typedef fas::metalist::advice metatype;
  typedef _call_ tag;
  typedef remote_call<JParams, JResult, JError> advice_class;

  advice_class& get_advice() { return *this;}
  const advice_class& get_advice() const { return *this;}
  
  typedef JParams params_json_t;
  typedef JResult result_json_t;
  typedef JError  error_json_t;
  typedef typename params_json_t::target params_type;
  typedef typename result_json_t::target result_type;
  typedef typename error_json_t::target  error_type;
  
  typedef typename std::unique_ptr<params_type> params_ptr;
  typedef typename std::unique_ptr<result_type> result_ptr;
  typedef typename std::unique_ptr<error_type>  error_ptr;
  
  template<typename T, typename TT>
  void operator()(
    T& t, 
    TT& tt, 
    params_ptr req, 
    std::function< void (result_ptr, error_ptr)> callback
  ) const
  {
    using namespace std::placeholders;
    
    // notify serializer
    std::function<data_ptr(const char* name, params_ptr)> ns
      = std::bind( TT::template serialize_notify<T, params_json_t>, _1, _2);

    // request serializer
    std::function<data_ptr(const char* name, params_ptr, call_id_t )> rs;
    // response handler
    std::function<void(incoming_holder holder)> rh;
    
    if ( callback!=nullptr )
    {
      rs  = std::bind( TT::template serialize_request<T, params_json_t>, _1, _2, _3);
      rh = std::bind( TT::template process_response<T, result_json_t, error_json_t>, _1, callback);
    }

    t.perform_send( 
      tt.name(), 
      std::move(req),
      std::move(ns),
      std::move(rs),
      std::move(rh)
    );
  }

private:

};

} // wjrpc


