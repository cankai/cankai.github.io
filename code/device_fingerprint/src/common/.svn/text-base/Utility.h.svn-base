#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <set>
#include <stdint.h>
#include <unistd.h>
#include <zlib.h>


class Utility
{
    const static char HEX_DATA_MAP[];

public:
    static unsigned int hash(const char* str);
    static std::string str2hex(const char* buf, int size);
    static std::string format_time(time_t unix_time);

    static time_t parse_time(std::string &time_mdy);

    static std::string format(int n);
    static std::string format(uint32_t n);
    static std::string format(long n);
    static std::string format(std::string &binary_data);    // 将二进制数据按照10机制输出

    static std::string format_suffix(int n);

    static int strnicmp(const char *s1, const char *s2, size_t len);

    static uint32_t  atouint32(char* ptr, int32_t len);
    static uint32_t  atouint64(char* ptr, int32_t len);

    static std::string ip_ntoa(uint32_t ip);
    static uint32_t ip_aton(const std::string& ip);

    static std::string get_local_datestring();

    static std::vector<std::string> resolve(std::string hostname);

    static std::string data_to_string(char * buf, int nbytes);

    static std::string gbk2utf8(const char* text);

    static std::string utf82gbk(const char* text);

    static int split(const std::string& source, const char* delimitor, std::vector<std::string>& result_array);

    static unsigned int utf8_decode( char *s, unsigned int *pi );
    static std::string UrlEncode(const std::string& src);
    static std::string UrlDecode(const std::string& src);
    static int replace_all(std::string& str,  const std::string& pattern,  const std::string& newpat);

    // in usec
    static long time_interval(struct timeval &start_time, struct timeval&end_time);

    // in msec
    static uint64_t time_stamp();

    static int64_t HexToDec(char *s);

    static int64_t MacToDec(std::string &s);

    static std::string DecToMac(int64_t d);

    // 当天的时间点 YYYYMMDD_INDEX
    static std::string time_index(uint32_t interval);
    static int base64Pre(const std::string & str64, char* des);
    static int unzip(unsigned char* src, int srcLen, unsigned char* des, int desLen);
    static std::string decompress(const std::string & str64);
    static bool is_end_with(std::string& fullstr, const char* suffix);
    //static bool is_end_with(std::string& fullstr, std::string& suffix);
};

#endif

