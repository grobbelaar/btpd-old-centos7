//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011, 2013, 2014
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_TYPE_LIST_N_HPP
#define FAS_TYPE_LIST_TYPE_LIST_N_HPP

#include <fas/type_list/organize.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>


namespace fas{
  
#if __cplusplus >= 201103L

namespace detail
{
  template<typename ...Args>
  struct type_list_helper;

  template<typename Head, typename ...Args>
  struct type_list_helper<Head, Args...>
  {
    typedef type_list<Head, typename type_list_helper<Args...>::type > type;
  };

  template<>
  struct type_list_helper<>
  {
    typedef empty_list type;
  };
  
} //  namespace detail

template<typename ...Args>
struct type_list_n_nocheck
{
  typedef typename detail::type_list_helper< Args... >::type type;
};


template<typename ...Args>
struct type_list_n
{
  typedef typename organize<
    typename type_list_n_nocheck< Args... >::type
  >::type type;
};


#else

template<typename T>
struct ignore_empty;

template<typename L, typename R>
struct ignore_empty< type_list<L, R> >
{
  typedef type_list<L, typename ignore_empty<R>::type > type;
};

template<typename R>
struct ignore_empty< type_list< empty_list, R> >
{
  typedef typename ignore_empty<R>::type type;
};

template<>
struct ignore_empty<empty_list>
{
  typedef empty_list type;
};


template< typename T1 = empty_list,  typename T2 = empty_list,  typename T3 = empty_list,  
          typename T4 = empty_list,  typename T5 = empty_list,  typename T6 = empty_list,
          typename T7 = empty_list,  typename T8 = empty_list,  typename T9 = empty_list,  
          typename T10 = empty_list, typename T11 = empty_list, typename T12 = empty_list,
          typename T13 = empty_list, typename T14 = empty_list, typename T15 = empty_list, 
          typename T16 = empty_list, typename T17 = empty_list, typename T18 = empty_list,
          typename T19 = empty_list, typename T20 = empty_list, typename T21 = empty_list, 
          typename T22 = empty_list, typename T23 = empty_list, typename T24 = empty_list,
          typename T25 = empty_list, typename T26 = empty_list
>
struct type_list_n_nocheck
{

  typedef 
      type_list< T1,  type_list< T2,  type_list< T3,  type_list< T4,
      type_list< T5,  type_list< T6,  type_list< T7,  type_list< T8,
      type_list< T9,  type_list< T10, type_list< T11, type_list< T12,
      type_list< T13, type_list< T14, type_list< T15, type_list< T16,
      type_list< T17, type_list< T18, type_list< T19, type_list< T20,
      type_list< T21, type_list< T22, type_list< T23, type_list< T24,
      type_list< T25, type_list< T26
      > >
          > > > >
                  > > > > > >
            > >
                  > > > > > >
          > > > >
      > >
  bar;
  
  typedef typename ignore_empty<bar>::type type;

};


template< typename T1 = empty_list,  typename T2 = empty_list,  typename T3 = empty_list,  
          typename T4 = empty_list,  typename T5 = empty_list,  typename T6 = empty_list,
          typename T7 = empty_list,  typename T8 = empty_list,  typename T9 = empty_list,  
          typename T10 = empty_list, typename T11 = empty_list, typename T12 = empty_list,
          typename T13 = empty_list, typename T14 = empty_list, typename T15 = empty_list, 
          typename T16 = empty_list, typename T17 = empty_list, typename T18 = empty_list,
          typename T19 = empty_list, typename T20 = empty_list, typename T21 = empty_list, 
          typename T22 = empty_list, typename T23 = empty_list, typename T24 = empty_list,
          typename T25 = empty_list, typename T26 = empty_list
>
struct type_list_n
{

  typedef typename type_list_n_nocheck<
    T1,   T2,   T3,   T4,
    T5,   T6,   T7,   T8,
    T9,   T10,  T11,  T12,
    T13,  T14,  T15,  T16,
    T17,  T18,  T19,  T20,
    T21,  T22,  T23,  T24,
    T25,  T26
  >::type bar;
  
  typedef typename organize<bar>::type type;

};

#endif

}

#endif
