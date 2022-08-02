#include "key_storage.hpp"
#include "key_rocksdb.hpp"
//#include "key_info_json.hpp"
/*#include <wjson/json.hpp>
#include <wjson/name.hpp>
*/
#include <wjson/strerror.hpp>
#include <iostream>
namespace wamba{ namespace btp{

key_storage::~key_storage()
{
  this->close(nullptr);
}

bool key_storage::open(const key_storage_options& opt, std::string* err)
{
  _rocksdb = std::make_shared<key_rocksdb>();
  bool res = _rocksdb->open(opt, err);
  return res;
}

bool key_storage::close( std::string* err )
{
  bool res = _rocksdb->close(err);
  _rocksdb = nullptr;
  return res;
}


bool key_storage::set(const std::string& name, const stored_key& data, std::string* err)
{
  return _rocksdb->set(name, data, err);
}

bool key_storage::get(const std::string& name, stored_key* data, std::string* err)
{
  return _rocksdb->get(name, data, err);
 }

bool key_storage::compact(std::string* err)
{
  return _rocksdb->compact(err);
}

bool key_storage::load(size_t step, std::function< void( std::vector<stored_name> ) > fun, std::string* err )
{
  using namespace std::placeholders;
  if ( step == 0 )
    step = 16;
  std::vector<stored_name> data;
  data.reserve(step);
  auto handler = [fun, step, &data] ( std::string name, stored_key value )
  {
    data.push_back( stored_name() );
    data.back().name = std::move(name);
    static_cast<stored_key&>( data.back() ) = std::move(value);
    if ( data.size() == step )
      fun( std::move(data) );
  };
  
  bool res = _rocksdb->load( std::move(handler), err);
  // остатки сладки если есть 
  if ( !data.empty() )
    fun( std::move(data) );
  return res;

}


}}
