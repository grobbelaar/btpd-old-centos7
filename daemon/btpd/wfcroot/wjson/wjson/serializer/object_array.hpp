//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2008-2016
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wjson/predef.hpp>
#include <wjson/parser.hpp>
#include <wjson/error.hpp>

namespace wjson{

template<typename T, typename L>
class serializerT< object_array<T, L> >
{
  typedef object_array<T, L> object_type;
  typedef serializerT< object_array<T, L> > self;

public:

  template<typename P>
  P operator()( const T& t, P end) const
  {
    *(end++)='[';
    end = self::serialize_members(t, end, L() );
    *(end++)=']';
    return end;
  }

  template<typename P>
  P operator()( T& t, P beg, P end, json_error* e) const
  {
    if ( parser::is_null(beg, end) )
    {
      t = T();
      return parser::parse_null(beg, end, e);
    }

    if (beg==end) 
      return create_error<error_code::UnexpectedEndFragment>(e, end);

    if ( *beg != '[' ) 
      return create_error<error_code::ExpectedOf>(e, end, "[", std::distance(beg, end)  );
    ++beg;

    beg = parser::parse_space(beg, end, e);
    if ( beg==end ) 
      return create_error<error_code::UnexpectedEndFragment>(e, end);

    
    if ( *beg != ']')
    {
       beg = self::unserialize_members(t, beg, end, L(), e );
       if ( beg==end ) 
         return create_error<error_code::UnexpectedEndFragment>(e, end);
       beg = parser::parse_space(beg, end, e);
       if ( beg==end ) 
         return create_error<error_code::UnexpectedEndFragment>(e, end);
    }

    if (beg==end) 
      return create_error<error_code::UnexpectedEndFragment>(e, end);

    if ( *(beg++) != ']' ) 
      return create_error<error_code::ExpectedOf>(e, end,"]", std::distance(beg, end) + 1 );

    return beg;
  }

private:

  template<typename P, typename C, typename R>
  static P serialize_members( const T& t, P end, fas::type_list<C, R> )
  {
    end = self::serialize_member(t, end, C());
    *(end++)=',';
    return self::serialize_members(t, end, R() );
  }

  template<typename P, typename C>
  static P serialize_members( const T& t, P end, fas::type_list<C, fas::empty_list> )
  {
    return self::serialize_member(t, end, C());
  }

  template<typename P>
  static P serialize_members( const T&, P end, fas::empty_list )
  {
    return end;
  }

  template<typename P, typename G, typename M, M G::* m, typename W >
  static P serialize_member( const T& t, P end, const member_array< G, M, m, W>& memb )
  {
    typedef typename member_array< G, M, m, W>::serializer serializer;
    return serializer()( memb.ref(t), end );
  }

  template<typename P, typename N, typename G, typename M, M G::* m, typename W >
  static P serialize_member( const T& t, P end, const member<N, G, M, m, W>& memb )
  {
    typedef typename member<N, G, M, m, W>::serializer serializer;
    return serializer()( memb.ref(t), end );
  }

  template<typename P, typename N, typename G, typename M, typename GT, typename W >
  static P serialize_member( const T& t, P end, const member_p<N, G, M, GT, W>& memb )
  {
    typedef typename member_p<N, G, M, GT, W>::serializer serializer;
    return serializer()( memb.get(t), end );
  }

  template<typename P, typename ML, typename MR, bool RU >
  static P serialize_member( const T& t, P end, const member_if<ML, MR, RU>& )
  {
    typedef typename ML::type typeL;
    if ( !( self::_get_value(t, ML()) == typeL() ) )
      return self::serialize_member( t, end, ML() );
    return self::serialize_member( t, end, MR() );
  }

private:

  template<typename N, typename G, typename M, M G::* m, typename W >
  static M _get_value( const T& t, member<N, G, M, m, W> memb )
  {
    return memb.ref(t);
  }

  template<typename N, typename G, typename M, typename GT, typename W >
  static M _get_value( const T& t, member_p<N, G, M, GT, W> memb )
  {
    return memb.get(t);
  }

  template<typename P, typename C, typename R>
  static P unserialize_members( T& t, P beg, P end, fas::type_list<C, R>, json_error* e )
  {
    beg = self::unserialize_member( t, beg, end, C(), e );
    beg = parser::parse_space(beg, end, e);

    if (beg==end) 
      return create_error<error_code::UnexpectedEndFragment>(e, end);

    if ( *beg == ',' )
    {
      ++beg;
      beg = parser::parse_space(beg, end, e);
      beg = self::unserialize_members( t, beg, end, R(), e );
    }

    if (beg==end) 
      return create_error<error_code::UnexpectedEndFragment>(e, end);

    if ( *beg != ']' )
      return create_error<error_code::ExpectedOf>(e, end,"]", std::distance(beg, end) );

    return beg;
  }


  template<typename P>
  static P unserialize_members( T& , P beg, P , fas::empty_list, json_error* )
  {
    return beg;
  }


  template<typename P, typename G, typename M, M G::* m, typename W >
  static P unserialize_member( T& t, P beg, P end, member_array<G, M, m, W> memb, json_error* e )
  {
    typedef typename member_array<G, M, m, W>::serializer serializer;
    return serializer()( memb.ref(t), beg, end, e);
  }

  
  template<typename P, typename N, typename G, typename M, M G::* m, typename W >
  static P unserialize_member( T& t, P beg, P end, member<N, G, M, m, W> memb, json_error* e )
  {
    typedef typename member<N, G, M, m, W>::serializer serializer;
    return serializer()( memb.ref(t), beg, end, e);
  }

  template<typename P, typename N, typename G, typename M, typename GT, typename W >
  static P unserialize_member( T& t, P beg, P end, member_p<N, G, M, GT, W> memb, json_error* e )
  {
    typedef typename member_p<N, G, M, GT, W>::serializer serializer;
    M value = M();
    beg = serializer()( value, beg, end, e);
    memb.set(t, value);
    return beg;
  }


  template<typename P, typename ML, typename MR >
  static P unserialize_member( T& t, P beg, P end, member_if<ML, MR, true>, json_error* e )
  {
    static const char *snull = "null";
    json_error ee;
    P itr = self::unserialize_member(t, beg, end, MR(), &ee);
    if ( !ee )
    {
      typename ML::serializer()(ML().ref(t), snull, snull+4, 0);
      return itr;
    }

    typename MR::serializer()(MR().ref(t), snull, snull+4, 0);
    return self::unserialize_member(t, beg, end, ML(), e);
  }

  template<typename P, typename ML, typename MR >
  static P unserialize_member( T& t, P beg, P end, member_if<ML, MR, false>, json_error* e )
  {
    static const char *snull = "null";
    json_error ee;
    P itr = self::unserialize_member(t, beg, end, ML(), &ee);
    if ( !ee )
    {
      typename MR::serializer()(MR().ref(t), snull, snull+4, 0);
      return itr;
    }

    typename ML::serializer()(ML().ref(t), snull, snull+4, 0);
    return self::unserialize_member(t, beg, end, MR(), e);
  }

};

}
