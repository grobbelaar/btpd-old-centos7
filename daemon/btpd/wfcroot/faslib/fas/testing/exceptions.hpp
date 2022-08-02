//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_EXCEPTIONS_HPP
#define FAS_TESTING_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace fas{ namespace testing{

class exception
  : public std::logic_error
{
public:
  explicit exception(const std::string& what_="")
    : std::logic_error(what_)
  {}
};

// abort current unit
class fail_error
  : public exception
{
public:
  explicit fail_error(const std::string& what_="")
    : exception(what_)
  {}
};

// abort current suite or all tests
class fatal_error
  : public exception
{
public:
  explicit fatal_error(const std::string& what_="")
    : exception(what_)
  {}
};

}}

#endif
