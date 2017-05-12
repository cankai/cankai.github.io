# pragma once

#include <arpc/service_api_cpp.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <json/json.h>

#include <iomanip>
#include <sstream>
#include <string.h>
#include <zlib.h>

using std::vector;
using std::string;

namespace dsn {
  namespace tmx {

    inline blob compress_string(const std::string& str,
                         int compressionlevel = Z_BEST_COMPRESSION)
    {
      z_stream zs;                        // z_stream is zlib's control structure
      memset(&zs, 0, sizeof(zs));
      
      if (deflateInit(&zs, compressionlevel) != Z_OK)
        throw(std::runtime_error("deflateInit failed while compressing."));

      zs.next_in = (Bytef*)str.data();
      zs.avail_in = str.size();           // set the z_stream's input

      int ret;

      char outbuffer[100] = {0};
      std::string outstring;
      int count = 0;
      do{
      zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
      zs.avail_out = sizeof(outbuffer);

      ret = deflate(&zs, Z_FINISH);

      if (zs.total_out > 100) {

        std::ostringstream oss;
        oss << "zlib compression size too bigger: (" << zs.total_out << ") ";
        throw(std::runtime_error(oss.str()));
      }
      if (count < zs.total_out) {
            // append the block to the output string
        outstring.append(outbuffer,
                       zs.total_out - outstring.size());
      }
      }while(ret == Z_OK);
      
      deflateEnd(&zs);

      if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
        oss<<"zs.total_out"<<zs.total_out;
        throw(std::runtime_error(oss.str()));
      }
      char *out = new char[zs.total_out];
      memmove(out, outstring.data(), outstring.size());
      std::shared_ptr<char> share(out, std::default_delete<char[]>{});      
      return blob(share, 0, zs.total_out);
    }

    /** Decompress an STL string using zlib and return the original data. */
    inline void decompress_string(blob& str, string& result)
    {
      z_stream zs;                        // z_stream is zlib's control structure
      memset(&zs, 0, sizeof(zs));
      result.clear();
      if (inflateInit(&zs) != Z_OK)
        throw(std::runtime_error("inflateInit failed while decompressing."));

      zs.next_in = (Bytef*)str.data();
      zs.avail_in = str.length();

      int ret;
      char outbuffer[500] = {0};

      do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = inflate(&zs, 0);

        if (result.size() < zs.total_out) {
          result.append(outbuffer,
                        zs.total_out - result.size());
        }
      } while (ret == Z_OK);

      inflateEnd(&zs);

      if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
            << zs.msg;
        throw(std::runtime_error(oss.str()));
      }
    }
        
    struct dispatch_req
    {
      string _tid;
      string _eid;
      string _etype;
      string _app;
      string _pload;

      string to_string()
      {
        string tmp;
        tmp.append("tid").append(":").append(_tid).append(",");
        tmp.append("eid").append(":").append(_eid).append(",");
        tmp.append("etype").append(":").append(_etype).append(",");
        tmp.append("app").append(":").append(_app).append(",");
        tmp.append("pload").append(":").append(_pload).append("");
        return tmp;
      }
    };

    struct dispatch_resp
    {
      int32_t _status;
      string _tid;
      string _eid;
      string _etype;
      string _app;
      string _res;

      string to_string()
      {
        string tmp;
        tmp.append("status").append(":").append(std::to_string(_status)).append(",");
        tmp.append("tid").append(":").append(_tid).append(",");
        tmp.append("eid").append(":").append(_eid).append(",");
        tmp.append("etype").append(":").append(_etype).append(",");
        tmp.append("app").append(":").append(_app).append(",");
        tmp.append("res").append(":").append(_res).append(",");
        return tmp;
      }
    };
    
    struct analyse_req
    {
      string _tid;
      string _eid;
      string _etype;
      string _app;
      string _pload;
      
      string to_string()
      {
        string tmp;
        tmp.append("tid").append(":").append(_tid).append(",");
        tmp.append("eid").append(":").append(_eid).append(",");
        tmp.append("etype").append(":").append(_etype).append(",");
        tmp.append("app").append(":").append(_app).append(",");
        tmp.append("pload").append(":").append(_pload).append("");
        return tmp;
      }
    };

    struct analyse_resp
    {
      int32_t _status;
      string _tid;
      string _eid;
      string _etype;
      string _app;
      string _res;

      string to_string()
      {
        string tmp;
        tmp.append("status").append(":").append(std::to_string(_status)).append(",");
        tmp.append("tid").append(":").append(_tid).append(",");
        tmp.append("eid").append(":").append(_eid).append(",");
        tmp.append("etype").append(":").append(_etype).append(",");
        tmp.append("app").append(":").append(_app).append(",");
        tmp.append("res").append(":").append(_res).append("");
        return tmp;        
      }
    };

    struct decise_req
    {
      string _tid;
      string _eid;
      string _etype;
      string _app;
      string _pload;
      
      string to_string()
      {
        string tmp;
        tmp.append("tid").append(":").append(_tid).append(",");
        tmp.append("eid").append(":").append(_eid).append(",");
        tmp.append("etype").append(":").append(_etype).append(",");
        tmp.append("app").append(":").append(_app).append(",");
        tmp.append("pload").append(":").append(_pload).append(",");
        return tmp;        
      }
    };

    struct decise_resp
    {
      int32_t _status;
      string _tid;
      string _eid;
      string _etype;
      string _app;
      string _res;

      string to_string()
      {
        string tmp;
        tmp.append("status").append(":").append(std::to_string(_status)).append(",");
        tmp.append("tid").append(":").append(_tid).append(",");
        tmp.append("eid").append(":").append(_eid).append(",");
        tmp.append("etype").append(":").append(_etype).append(",");
        tmp.append("app").append(":").append(_app).append(",");
        tmp.append("res").append(":").append(_res).append("");
        return tmp;
      }
    };
    
    inline void unmarshall(::dsn::binary_reader& reader, dispatch_req& val)
    {
      unmarshall(reader, val._tid);
      unmarshall(reader, val._eid);
      unmarshall(reader, val._etype);
      unmarshall(reader, val._app);
      blob bb ;
      unmarshall(reader, bb);
      if(bb.length() > 0)
        decompress_string(bb, val._pload);
    };

    inline void marshall(::dsn::binary_writer& writer, const dispatch_resp& val)
    {
      marshall(writer, val._status);
      marshall(writer, val._tid);
      marshall(writer, val._eid);
      marshall(writer, val._etype);
      marshall(writer, val._app);
      marshall(writer, val._res);
    };
    
    inline void marshall(::dsn::binary_writer& writer, const analyse_req& val)
    {

      marshall(writer, val._tid);
      marshall(writer, val._eid);
      marshall(writer, val._etype);
      marshall(writer, val._app);
      blob&& bb = compress_string(val._pload);
      marshall(writer, bb);
    };

    inline void unmarshall(::dsn::binary_reader& reader,  analyse_req& val)
    {
      unmarshall(reader, val._tid);
      unmarshall(reader, val._eid);
      unmarshall(reader, val._etype);
      unmarshall(reader, val._app);
      blob bb;
      unmarshall(reader, bb);
      if(bb.length() > 0)
        decompress_string(bb, val._pload);
    };
    
    inline void unmarshall(::dsn::binary_reader& reader,  analyse_resp& val)
    {
      unmarshall(reader, val._status);
      unmarshall(reader, val._tid);
      unmarshall(reader, val._eid);
      unmarshall(reader, val._etype);
      unmarshall(reader, val._app);
      blob bb;
      dinfo("unmarshall analyse resp");
      unmarshall(reader, bb);
      dinfo("bb size =%d", bb.length());
      if(bb.length() > 0)
        decompress_string(bb, val._res);
    };

    inline void marshall(::dsn::binary_writer& writer, const analyse_resp& val)
    {
      marshall(writer, val._status);
      marshall(writer, val._tid);
      marshall(writer, val._eid);
      marshall(writer, val._etype);
      marshall(writer, val._app);
      blob && bb = compress_string(val._res);
      marshall(writer, bb);
    };
    
    inline void marshall(::dsn::binary_writer& writer, const decise_req& val)
    {
      marshall(writer, val._tid);
      marshall(writer, val._eid);
      marshall(writer, val._etype);
      marshall(writer, val._app);
      blob && bb = compress_string(val._pload);
      marshall(writer, bb);
    };

    inline void unmarshall(::dsn::binary_reader& reader, decise_req& val)
    {
      unmarshall(reader, val._tid);
      unmarshall(reader, val._eid);
      unmarshall(reader, val._etype);
      unmarshall(reader, val._app);

      blob bb;
      unmarshall(reader, bb);
      if(bb.length() > 0)
        decompress_string(bb, val._pload);
    };
    
    inline void unmarshall(::dsn::binary_reader& reader,  decise_resp& val)
    {
      unmarshall(reader, val._status);
      unmarshall(reader, val._tid);
      unmarshall(reader, val._eid);
      unmarshall(reader, val._etype);
      unmarshall(reader, val._app);
      unmarshall(reader, val._res);
    };
    
    inline void marshall(::dsn::binary_writer& writer, const decise_resp& val)
    {
      marshall(writer, val._status);
      marshall(writer, val._tid);
      marshall(writer, val._eid);
      marshall(writer, val._etype);
      marshall(writer, val._app);
      blob && bb = compress_string(val._res);
      marshall(writer, bb);
    };

  }
}

