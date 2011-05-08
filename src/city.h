/* 
 *	geoip.cc - node.JS to C++ glue code for the GeoIP C library
 *	Written by Joe Vennix on March 15, 2011
 *	For the GeoIP C library, go here: http://www.maxmind.com/app/c
 *		./configure && make && sudo make install
 */
#ifndef NODE_GEOIP_CITY_H
#define NODE_GEOIP_CITY_H

#include <v8.h>
#include <node.h>
#include "node_geoip.h"

using namespace v8;
using namespace node;

namespace geoip {
  class City: ObjectWrap
  {
    private:
      GeoIP *db;
      int db_edition;
    public:
      static Persistent<FunctionTemplate> constructor_template;

      static void Init(Handle<Object> target);

      static Handle<Value> New(const Arguments& args);

      static Handle<Value> lookupSync(const Arguments &args);

      static Handle<Value> lookup(const Arguments& args);

      static int EIO_City(eio_req *req);

      static int EIO_AfterCity(eio_req *req);

      static Handle<Value> close(const Arguments &args);
  };

}
struct city_baton_t {
  geoip::City *c;
  char host_cstr[256];  // standard length of ipv4
  GeoIPRecord *record;
  int increment_by;
  int sleep_for;
  Persistent<Function> cb;
};

#endif /* NODE_GEOIP_CITY_H */