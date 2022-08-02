//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011-2016
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wjrpc/method/aspect/call.hpp>
#include <wjrpc/method/aspect/name.hpp>
#include <wjrpc/method/mem_fun/invoke_mem_fun2.hpp>
#include <wjrpc/method/method.hpp>
#include <memory>
#include <functional>

namespace wjrpc{

template<
  typename TgName, 
  typename JParams, 
  typename JResult, 
  typename Params2, 
  typename Result2, 
  typename Target, 
  void (Target::*mem_ptr)( 
    std::unique_ptr<typename JParams::target>, 
    std::function< void(std::unique_ptr<typename JResult::target>) >, 
    size_t, 
    std::function< void(
      std::unique_ptr<Params2>, 
      std::function< void(std::unique_ptr<Result2>) >  
    ) >
  ),
  typename Itf,
  void (Itf::*mem_ptr2)( 
    std::unique_ptr<Params2>, 
    std::function< void(std::unique_ptr<Result2>) >
  ),
  typename ...Args
>
struct basic_dual_method2: basic_method< 
  name<TgName>,
  invoke_mem_fun2< 
    JParams, 
    JResult, 
    Params2, 
    Result2, 
    Target, 
    mem_ptr, 
    Itf, 
    mem_ptr2
  >,
  remote_call<JParams, JResult>,
  Args...
>
{};

  
template<
  typename TgName, 
  typename JParams, 
  typename JResult, 
  typename Params2, 
  typename Result2, 
  typename Target, 
  void (Target::*mem_ptr)( 
    std::unique_ptr<typename JParams::target>, 
    std::function< void(std::unique_ptr<typename JResult::target>) >, 
    size_t, 
    std::function< void(
      std::unique_ptr<Params2>, 
      std::function< void(std::unique_ptr<Result2>) >  
    ) >
  ),
  typename Itf,
  void (Itf::*mem_ptr2)( 
    std::unique_ptr<Params2>, 
    std::function< void(std::unique_ptr<Result2>) >
  ),
  typename ...Args
>
struct dual_method2: method< 
  name<TgName>,
  invoke_mem_fun2< 
    JParams, 
    JResult, 
    Params2, 
    Result2, 
    Target, 
    mem_ptr, 
    Itf, 
    mem_ptr2
  >,
  remote_call<JParams, JResult>,
  Args...
>
{};


} // wjrpc


