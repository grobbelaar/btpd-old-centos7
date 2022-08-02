#pragma once

#include <ag/iag.hpp>

struct ibtp: public wamba::btp::iag
{
  virtual void push( wfc::statistics::request::push::ptr , wfc::statistics::response::push::handler) {}
  virtual void del( wfc::statistics::request::del::ptr , wfc::statistics::response::del::handler) {}

  virtual void get( ::wamba::btp::request::get::ptr , ::wamba::btp::response::get::handler ) {}
  virtual void tree( ::wamba::btp::request::tree::ptr , ::wamba::btp::response::tree::handler ) {}
  virtual void select( ::wamba::btp::request::select::ptr , ::wamba::btp::response::select::handler ) {}
  virtual void get_names( ::wamba::btp::request::get_names::ptr , ::wamba::btp::response::get_names::handler ) {}
  virtual void multi_get( ::wamba::btp::request::multi_get::ptr , ::wamba::btp::response::multi_get::handler ) {}
};
