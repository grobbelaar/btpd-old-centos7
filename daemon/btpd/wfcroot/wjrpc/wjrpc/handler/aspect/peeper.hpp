//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011-2016
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wjrpc/handler/aspect/tags.hpp>
#include <fas/aop.hpp>
#include <memory>

namespace wjrpc{
 
/*
 * Отслеживает открытие и закрытие источников
 */
template<typename I>
struct peeper
  : fas::value<_peeper_, std::shared_ptr<I> >
{
};

} // wjrpc


