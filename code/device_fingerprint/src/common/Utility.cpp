#include "Utility.h"

#include <time.h>
#include <sys/time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <sstream>

#include <locale>
#include <iconv.h>
#include <cmath>
#include "base64.h"

using namespace std;


const char Utility::HEX_DATA_MAP[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

string Utility::str2hex(const char * buf,int size)
{
	string ret_str;

	char tmpbuf[10] = {0};
	const char * buffer = buf;
	int buffer_size = size;
	for (int i = 0 ;i < buffer_size; i++) {
		sprintf(tmpbuf,"%02X",(unsigned char)buffer[i]);
		ret_str += tmpbuf;
	}

	return ret_str;
}


unsigned int Utility::hash(const char* str)
{
    unsigned int h = 0;
    unsigned char *p;

    for (p = (unsigned char*)str; *p != '\0'; ++p)
    {
        h = 31 * h + *p;
    }
    return h;
}
string Utility::format_time(time_t unix_time)
{
	//  struct timeval tv;
	struct timezone tz;

	gettimeofday(NULL, &tz);

	time_t local_time = (time_t)(unix_time - tz.tz_minuteswest * 60);

	struct tm lt;
	gmtime_r(&local_time, &lt);

	char timebuf[64] = {0};
	sprintf(timebuf, "%4d-%02d-%02d %02d:%02d:%02d", (1900+lt.tm_year), lt.tm_mon+1, lt.tm_mday, lt.tm_hour, lt.tm_min, lt.tm_sec);

	return (string)timebuf;
}


time_t Utility::parse_time(std::string &time_mdy)
{
	struct tm lt;
	memset(&lt, 0, sizeof(struct tm));
	strptime(time_mdy.c_str(), "%m/%d/%Y", &lt);
	return mktime(&lt);
}


string Utility::format(int n)
{
	char buf[10];
	sprintf(buf, "%d", n);

	return (string)buf;
}

string Utility::format(uint32_t n)
{
	char buf[10];
	sprintf(buf, "%u", n);

	return (string)buf;
}

string Utility::format(long n)
{
	char buf[32];
	sprintf(buf, "%ld", n);

	return (string)buf;
}

string Utility::format(string &binary_data)
{
	//long tmp = 0;
	//memcpy(&tmp,binary_data.c_str(),sizeof(binary_data));
	//return format(tmp);
	return binary_data;
}

std::string Utility::format_suffix(int n)
{
	char buf[32];
	sprintf(buf, "%02d", n);

	return (string)buf;
}


int Utility::strnicmp(const char *s1, const char *s2, size_t len)
{
	unsigned char c1, c2;

	c1 = 0; c2 = 0;
	if (len) {
		do {
		c1 = *s1; c2 = *s2;
		s1++; s2++;
		//ÊÇ·ñÒÑµœ×Ö·ûŽ®µÄÄ©Î²»òÁœ×Ö·ûŽ®ÊÇ·ñÓÐ¿ÕŽ®,Èç¹ûµœÁËÄ©Î²»òÓÐ¿ÕŽ®,Ôò±ÈœÏÍê±Ï
		if (!c1)
			break;
		if (!c2)
			break;

		//Èç¹ûÃ»ÓÐ,ÇÒ×Ö·ûŽ®ÏàµÈ,ÔòŒÌÐø±ÈœÏÏÂžö×Ö·û
		if (c1 == c2)
			continue;

		//Èç¹û²»ÏàÍ¬,ÔòÍ¬Ê±×ª»»ÎªÐ¡ÐŽ×Ö·ûÔÙœøÐÐ±ÈœÏ
		c1 = tolower(c1);
		c2 = tolower(c2);

		//Èç¹û²»ÏàÍ¬,Ôò±ÈœÏÍê±Ï,·ñÔòŒÌÐø
		if (c1 != c2)
			break;
		}while (--len);
	}

	return (int)c1 - (int)c2;
}


uint32_t Utility::atouint32(char* ptr, int32_t len)
{
	uint32_t value = 0;
	while((len >= 0) && isdigit(*ptr )){
		value = 10 * value + (uint32_t)(*ptr - '0');
		ptr ++;
		len --;
	}
	return value;
}

uint32_t Utility::atouint64(char* ptr, int32_t len)
{
	uint64_t value = 0;
	while((len >= 0) && isdigit(*ptr )){
		value = 10 * value + (uint32_t)(*ptr - '0');
		ptr ++;
		len --;
	}
	return value;
}


string Utility::ip_ntoa(uint32_t ip)
{
	struct in_addr in;
	in.s_addr = in_addr_t(ip);
	return string(inet_ntoa(in));
}

uint32_t Utility::ip_aton(const  string & ip)
{
	struct in_addr in;
	in.s_addr = 0;
	inet_aton(ip.c_str(), &in);
	return uint32_t(in.s_addr);
}

string Utility::get_local_datestring()
{
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);

	time_t local_time = (time_t)(tv.tv_sec - tz.tz_minuteswest * 60);
	struct tm lt;
	gmtime_r(&local_time, &lt);

	char timebuf[64];
        sprintf(timebuf, "%4d-%02d-%02d %02d:%02d:%02d.%06d", (1900+lt.tm_year), lt.tm_mon+1, lt.tm_mday, lt.tm_hour, lt.tm_min, lt.tm_sec,tv.tv_usec);

	return (string)timebuf;
}

vector<string> Utility::resolve(string hostname)
{
	vector<string> addresses;
	if(hostname.empty())
	{
	}
	else if(inet_addr(hostname.c_str()) != INADDR_NONE)
	{
		addresses.push_back(hostname);
	}
	else
	{
		struct hostent* ent = gethostbyname(hostname.c_str());
		if(ent && ent->h_addrtype == AF_INET)
		{
			in_addr addr;
			for(int i = 0; ent->h_addr_list[i]; ++i)
			{
				addr.s_addr = *((long*)ent->h_addr_list[i]);
				addresses.push_back(inet_ntoa(addr));
			}
		}
	}

	return addresses;
}



string Utility::gbk2utf8(const char* text)
{
	if(text == NULL)
	{
		return "";
	}

    size_t inlen = strlen(text);
    if(inlen == 0)
    {
        return "";
    }

	iconv_t ic = iconv_open("utf-8", "gbk");
	if(ic == (iconv_t)-1)
	{
		return "";
	}

	size_t outlen = inlen * 2;
	std::vector<char> result(outlen + 1);
	char* inbuf = const_cast<char*>(text);
	char* outbuf = &result[0];
	if(iconv(ic, &inbuf, &inlen, &outbuf, &outlen) == (size_t)-1)
	{
		iconv_close(ic);
		return "";
	}
	iconv_close(ic);
	return &result[0];
}


string Utility::utf82gbk(const char* text)
{
	if(text == NULL)
	{
		return "";
	}

    size_t inlen = strlen(text);
    if(inlen == 0)
    {
        return "";
    }

	iconv_t ic = iconv_open("gbk", "utf-8");
	if(ic == (iconv_t)-1)
	{
		return "";
	}

	size_t outlen = inlen * 2;
	std::vector<char> result(outlen + 1);
	char* inbuf = const_cast<char*>(text);
	char* outbuf = &result[0];
	if(iconv(ic, &inbuf, &inlen, &outbuf, &outlen) == (size_t)-1)
	{
		iconv_close(ic);
		return "";
	}
	iconv_close(ic);
	return &result[0];


}


int Utility::split(const std::string& source, const char* delimitor, std::vector<std::string>& result_array)
{
    if(delimitor == NULL)
        return 0;

    result_array.clear();

    string::size_type startPos = 0;
    bool reachEnd = false;
    while(!reachEnd)
    {
        string::size_type curPos = source.find(delimitor, startPos);
        if(curPos != string::npos)
        {
            result_array.push_back(source.substr(startPos, curPos - startPos));
            startPos = curPos + 1;
        }
        else
        {
            // add the last part
            if(startPos < source.length())
                result_array.push_back(source.substr(startPos));
            
            reachEnd = true;
        }
    }

    return result_array.size();
}

unsigned int Utility::utf8_decode( char *s, unsigned int *pi )
{
    unsigned int c;
    int i = *pi;
    /* one digit utf-8 */
    if ((s[i] & 128)== 0 ) {
        c = (unsigned int) s[i];
        i += 1;
    } else if ((s[i] & 224)== 192 ) { /* 110xxxxx & 111xxxxx == 110xxxxx */
        c = (( (unsigned int) s[i] & 31 ) << 6) +
            ( (unsigned int) s[i+1] & 63 );
        i += 2;
    } else if ((s[i] & 240)== 224 ) { /* 1110xxxx & 1111xxxx == 1110xxxx */
        c = ( ( (unsigned int) s[i] & 15 ) << 12 ) +
            ( ( (unsigned int) s[i+1] & 63 ) << 6 ) +
            ( (unsigned int) s[i+2] & 63 );
        i += 3;
    } else if ((s[i] & 248)== 240 ) { /* 11110xxx & 11111xxx == 11110xxx */
        c =  ( ( (unsigned int) s[i] & 7 ) << 18 ) +
            ( ( (unsigned int) s[i+1] & 63 ) << 12 ) +
            ( ( (unsigned int) s[i+2] & 63 ) << 6 ) +
            ( (unsigned int) s[i+3] & 63 );
        i+= 4;
    } else if ((s[i] & 252)== 248 ) { /* 111110xx & 111111xx == 111110xx */
        c = ( ( (unsigned int) s[i] & 3 ) << 24 ) +
            ( ( (unsigned int) s[i+1] & 63 ) << 18 ) +
            ( ( (unsigned int) s[i+2] & 63 ) << 12 ) +
            ( ( (unsigned int) s[i+3] & 63 ) << 6 ) +
            ( (unsigned int) s[i+4] & 63 );
        i += 5;
    } else if ((s[i] & 254)== 252 ) { /* 1111110x & 1111111x == 1111110x */
        c = ( ( (unsigned int) s[i] & 1 ) << 30 ) +
            ( ( (unsigned int) s[i+1] & 63 ) << 24 ) +
            ( ( (unsigned int) s[i+2] & 63 ) << 18 ) +
            ( ( (unsigned int) s[i+3] & 63 ) << 12 ) +
            ( ( (unsigned int) s[i+4] & 63 ) << 6 ) +
            ( (unsigned int) s[i+5] & 63 );
        i += 6;
    } else {
        c = '?';
        i++;
    }
    *pi = i;
    return c;
}


string Utility::UrlEncode(const string& src)
{
    static    char hex[] = "0123456789ABCDEF";
    std::string dst;

    for (size_t i = 0; i < src.size(); i++)
    {
        unsigned char ch = src[i];
        if (isalnum(ch))
        {
            dst += ch;
        }
        else
            if (src[i] == ' ')
            {
                dst += '+';
            }
            else
            {
                unsigned char c = static_cast<unsigned char>(src[i]);
                dst += '%';
                dst += hex[c / 16];
                dst += hex[c % 16];
            }
    }
    return dst;
}

string Utility::UrlDecode(const std::string& src)
{
    std::string dst, dsturl;

    int srclen = src.size();

    for (size_t i = 0; i < srclen; i++)
    {
        if (src[i] == '%')
        {
            if(isxdigit(src[i + 1]) && isxdigit(src[i + 2]))
            {
                char c1 = src[++i];
                char c2 = src[++i];
                c1 = c1 - 48 - ((c1 >= 'A') ? 7 : 0) - ((c1 >= 'a') ? 32 : 0);
                c2 = c2 - 48 - ((c2 >= 'A') ? 7 : 0) - ((c2 >= 'a') ? 32 : 0);
                dst += (unsigned char)(c1 * 16 + c2);
            }
        }
        else
            if (src[i] == '+')
            {
                dst += ' ';
            }
            else
            {
                dst += src[i];
            }
    }

    int len = dst.size();

    for(unsigned int pos = 0; pos < len;)
    {
        unsigned int nvalue = utf8_decode((char *)dst.c_str(), &pos);
        dsturl += (unsigned char)nvalue;
    }

    return dsturl;
}


long Utility::time_interval(struct timeval &start_time, struct timeval&end_time)
{
	return (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
}

// in msec
uint64_t Utility::time_stamp()
{
	struct timeval now_time;
	gettimeofday(&now_time, 0);

	return ((now_time.tv_sec) * 1000000 + now_time.tv_usec)/1000;
}


// 需要以\0 结尾
int64_t Utility::HexToDec(char *s)
{
	char *p = s;

	//空串返回0
	if(*s == '\0')
		return 0;

	//忽略开头的'0'字符
	while(*p == '0')
		p++;

	int64_t dec = 0;
	char c;

	//循环直到字符串结束。
	while(c = *p++)
	{
		//dec乘16
		dec <<= 4;

		//数字字符。
		if(c >= '0' && c <= '9')
		{
			dec += c - '0';
			continue;
		}

		//小写abcdef。
		if(c >= 'a' && c <= 'f')
		{
			dec += c - 'a' + 10;
			continue;
		}

		//大写ABCDEF。
		if(c >= 'A' && c <= 'F')
		{
			dec += c - 'A' + 10;
			continue;
		}

		//没有从任何一个if语句中结束，说明遇到了非法字符。
		return -1;
	}

	//正常结束循环，返回10进制整数值。
	return dec;
}


int64_t Utility::MacToDec(std::string &s)
{
	if(s.length() != 12)
	{
		return -1;
	}

	std::string tmp = s + "\0";
	return HexToDec((char*)tmp.c_str());
}


std::string Utility::DecToMac(int64_t d)
{
	char tmpbuf[16] = {0};
	sprintf(tmpbuf,"%012X", d);

	return std::string(tmpbuf);
}

std::string Utility::time_index(uint32_t interval)
{
    time_t unix_time = time(NULL);
    struct timezone tz;
    gettimeofday(NULL, &tz);

    time_t local_time = (time_t)(unix_time - tz.tz_minuteswest * 60);

    struct tm lt;
    gmtime_r(&local_time, &lt);

    uint32_t index = (lt.tm_hour*3600 + lt.tm_min*60 + lt.tm_sec) / interval;
    char timebuf[64] = {0};
    sprintf(timebuf, "%4d%02d%02d_%04d", (1900+lt.tm_year), lt.tm_mon+1, lt.tm_mday, index);

    return (string)timebuf;

}

int Utility::replace_all(std::string& str,  const std::string& pattern,  const std::string& newpat)
{
        int count = 0;
        const size_t nsize = newpat.size();
        const size_t psize = pattern.size();

        for(size_t pos = str.find(pattern, 0);
                        pos != std::string::npos;
            pos = str.find(pattern,pos + nsize))
        {
            str.replace(pos, psize, newpat);
            count++; 
        }   
 
        return count; 
}

//caodan
//if the string has blank and has nothing '+',then replace blank with '+'
//if the string has blank and has '+',then delete blank 
int Utility::base64Pre(const std::string & str64, char* des)
{
    int i = 0;
    if(str64.find("+") == std::string::npos)
    {
        for(std::string::const_iterator it = str64.begin(); it != str64.end(); ++it)
        {   
            if((*it >= 'A' && *it <= 'Z') || (*it >= 'a' && *it <= 'z') || (*it >= '0' && *it <= '9') || *it == '=' || *it == '/' || *it == '+')
            {   
                *(des + i++) = *it;
            }   
            if(*it == ' ')
            {
                *(des + i++) = '+';
            }
        }   
    }
    else
    {
        for(std::string::const_iterator it = str64.begin(); it != str64.end(); ++it)
        {   
            if((*it >= 'A' && *it <= 'Z') || (*it >= 'a' && *it <= 'z') || (*it >= '0' && *it <= '9') || *it == '=' || *it == '/' || *it == '+')
            {   
                *(des + i++) = *it;
            }   
        }   
    }
    return i;
}


std::string Utility::decompress(const std::string & str64)
{
    try{
        int b64len = str64.length();
        char* befor64 = (char*)malloc(b64len);
        char* after64 = (char*)malloc(b64len);
    
        size_t reallen = Utility::base64Pre(str64, befor64);
    
        int b64dlen =  Base64Decode(after64, befor64, reallen);
        if(b64dlen <= 47)    return "";
        else
        {
            char* decompr = (char*)malloc(b64dlen*20);
            int rt = Utility::unzip((unsigned char*)after64, b64dlen, (unsigned char*)decompr, b64dlen*20);
            std::string rtDecompr = std::string(decompr);
            free(befor64);
            free(after64);
            free(decompr);
            return rtDecompr;
        }
    }
    catch (std::exception& e)
    {
        return "";
    }
    catch(...)
    {
        return "";
    }

}

int Utility::unzip(unsigned char* src, int srcLen, unsigned char* des, int desLen)
{
    int ret;
    unsigned have;
    z_stream strm;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    unsigned char* in;
    try{
        int count = 0;
        do {
            if(++count >=2) break;
            strm.avail_in = srcLen - 45; 
            in = (unsigned char*)malloc(srcLen - 45);
            memcpy(in + 2, src + 31, srcLen - 47);
            *(in) = 120;
            *(in + 1) = 156;
            strm.next_in = in; 
    
            do {
                strm.avail_out = desLen;
                strm.next_out = des;
                ret = inflate(&strm, Z_NO_FLUSH);
                switch (ret) {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    (void)inflateEnd(&strm);
                    free(in);
                    return ret;
                }
                have = desLen - strm.avail_out;
            } while (strm.avail_out == 0);
        } while (ret != Z_STREAM_END);
    }
   catch (std::exception& e)
   {
       (void)inflateEnd(&strm);
       free(in);
       return -1;
   }
   catch(...)
   {
       (void)inflateEnd(&strm);
       free(in);
       return -1;
   }

    (void)inflateEnd(&strm);
    free(in);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

bool Utility::is_end_with(std::string& fullstr, const char* c_suffix)
{
    std::string suffix(c_suffix);
    return fullstr.size() >= suffix.size() 
        && 0 == fullstr.compare(fullstr.size() - suffix.size(), suffix.size(), suffix);
}

