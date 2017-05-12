/*
** Copyright (C) 2014 Wang Yaofu
** All rights reserved.
**
**Author:Wang Yaofu voipman@qq.com
**Description: The source file of base64.
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include "base64.h"
namespace {

static const unsigned char EncodeTable[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const unsigned char* DecodeTable = NULL;

void FillDecodeTable() {
    // double buffer is used here for thread safe.
    static unsigned char DecodeTableBuff[256];
    unsigned char buff[256];
    if (DecodeTable != NULL) {
        return;
    }
    ::memset(buff, 0x80, sizeof(buff));

    for (size_t k = 0; k < sizeof(EncodeTable); ++k) {
        buff[(size_t)EncodeTable[k]] = k;
    }
    // to mark those valid characters in encoded string, but not in these
    // 64 bases list.
    buff[(size_t)'\r'] = buff[(size_t)'\n'] = 0x4F;
    buff[(size_t)'='] = 0x40;

    ::memcpy(DecodeTableBuff, buff, sizeof(DecodeTableBuff));
    DecodeTable = DecodeTableBuff;
}

// Get the next 4 characters from input string, '\r\n' will be trimmed off.
// The input string starts from 'p', and ends before 'q'. 'buff' is for
// storing the return characters.
// The return value, -1: error, there aren't 4 characters available, or get
// invalid character. 0-4 mean the number of valid characters, '=' is excluded.
int GetNext4EncodedCharacters(const unsigned char*& p,
                              const unsigned char* q,
                              unsigned char* buff) {
    int k = 0;
    unsigned char c = 0;
    while (k < 4 && p < q) {
        c = DecodeTable[*p];
        if ((c & 0xC0) == 0) {      // normal valid characters
            *buff++ = c;
            ++p;
            ++k;
        } else if (c & 0x80) {      // not ('\r' or '\n' or '=')
            return -1;
        } else if (*p == '=') {
            break;
        } else {                    // ('\r' or '\n')
            ++p;
        }
    }
    // success. this should be most of the cases, return as soon as possible
    if (k == 4) {
        return 4;
    }
    // get a '='
    if (p < q && *p == '=') {
        ++p;
        // there should be 4 characters in the last encode group
        int tail = 4 - k - 1;
        // there should not be more than 2 '=' in the end
        if (tail > 1) {
            return -1;
        }
        while (tail > 0 && p < q && ((DecodeTable[*p] & 0x40) == 0x40)) {
            if (*p == '=') {
                --tail;
            }
            ++p;
        }
        // any character not ('\r' or '\n' or '=') appears after '='
        if (tail != 0) {
            return -1;
        }
        // only ('\r' || '\n') is allowed at the end
        while (p < q) {
            if ((DecodeTable[*p] & 0x4F) == 0x4F) {
                ++p;
            } else {
                return -1;
            }
        }

        return k;
    }
    // for ('\r' or '\n') at very end
    while (p < q && (DecodeTable[*p] & 0x4F) == 0x4F) {
        ++p;
    }
    if (k == 0 && p == q) {
        return 0;
    }

    return -1;
}

size_t ExpectedEncodeLength(size_t len)
{
    size_t encodedLen = ((len * 4 / 3 + 3) / 4) * 4;
    return encodedLen;
}

size_t ExpectedDecodeLength(size_t len)
{
    return (size_t)((len + 3) / 4 * 3);
}

} // anonymous namespace

bool Base64Encode(const std::string& input, std::string* output)
{
    assert(output);
    output->resize(ExpectedEncodeLength(input.size()));

    char* buff = const_cast<char*>(output->data());
    size_t len = output->size();

    if (!Base64Encode(input, buff, &len)) {
        output->clear();
        return false;
    }
    output->resize(len);
    return true;
}

bool Base64Encode(const std::string& input, char* output, size_t* len)
{
    assert(output);

    char* buff = output;
    if (__builtin_expect(*len < ExpectedEncodeLength(input.size()), 0)) {
        return false;
    }

    unsigned char *p = (unsigned char*)input.data();
    unsigned char *q = p + input.size();
    unsigned char c1, c2, c3;

    // process 3 char every loop
    for (; p + 3 <= q; p += 3) {
        c1 = *p;
        c2 = *(p + 1);
        c3 = *(p + 2);

        *buff++ = EncodeTable[c1 >> 2];
        *buff++ = EncodeTable[((c1 << 4) | (c2 >> 4)) & 0x3f];
        *buff++ = EncodeTable[((c2 << 2) | (c3 >> 6)) & 0x3f];
        *buff++ = EncodeTable[c3 & 0x3f];
    }

    // the reminders
    if (q - p == 1) {
        c1 = *p;
        *buff++ = EncodeTable[(c1 & 0xfc) >> 2];
        *buff++ = EncodeTable[(c1 & 0x03) << 4];
        *buff++ = '=';
        *buff++ = '=';
    } else if (q - p == 2) {
        c1 = *p;
        c2 = *(p + 1);
        *buff++ = EncodeTable[(c1 & 0xfc) >> 2];
        *buff++ = EncodeTable[((c1 & 0x03) << 4) | ((c2 & 0xf0) >> 4)];
        *buff++ = EncodeTable[((c2 & 0x0f) << 2)];
        *buff++ = '=';
    }

    *len = buff - output;
    return true;
}

bool Base64Decode(const std::string& input, std::string* output)
{
    assert(output);
    output->resize(ExpectedDecodeLength(input.size()));

    char* buff = const_cast<char*>(output->data());
    size_t len = output->size();

    if (!Base64Decode(input, buff, &len)) {
        output->clear();
        return false;
    }
    output->resize(len);
    return true;
}

bool Base64Decode(const std::string& input, char* output, size_t* len)
{
    assert(output && len);

    char* buff = output;
    if (__builtin_expect(*len < ExpectedDecodeLength(input.size()), 0)) {
        return false;
    }
    if (__builtin_expect(!DecodeTable, 0)) {
        FillDecodeTable();
    }
    if (input.empty()) {
        *len = buff - output;
        return true;
    }

    const unsigned char* p = (unsigned char*)input.data();
    const unsigned char* q = (unsigned char*)input.data() + input.size();

    // handle 4 bytes in every loop
    while (true) {
        char ch = 0;
        unsigned char encoded[4];
        int len = GetNext4EncodedCharacters(p, q, encoded);
        if (__builtin_expect(len == 4, 1)) {
            ch =  encoded[0] << 2; // all 6 bits
            ch |= encoded[1] >> 4; // 2 high bits
            *buff++ = ch;
            ch =  encoded[1] << 4; // 4 low bits
            ch |= encoded[2] >> 2; // 4 high bits
            *buff++ = ch;
            ch =  encoded[2] << 6; // 2 low bits
            ch |= encoded[3];
            *buff++ = ch;
        } else if (len >= 2) {
            ch =  encoded[0] << 2; // all 6 bits
            ch |= encoded[1] >> 4; // 2 high bits
            *buff++ = ch;
            if (len == 3) {
                ch =  encoded[1] << 4; // 4 low bits
                ch |= encoded[2] >> 2; // 4 high bits
                *buff++ = ch;
            }
        } else if (len == 0) {
            break;
        } else {
            return false;
        }
    }

    *len = buff - output;
    return true;
}


void *read_file( char *fn, int *_sz)
{
  char *data;

  data = 0;
  FILE * pFile;
  long size, result= 0;

  pFile = fopen (fn,"r");
  if (pFile==NULL) perror ("Error opening file");
  else
  {
    fseek (pFile, 0, SEEK_END);   // non-portable
    size = ftell (pFile);
    rewind (pFile);
    data = (char *) malloc(sizeof(char) *size+2);
    if(data == NULL)
      {
        printf("get memory error");
        return NULL;
      }
    printf("size is %d", size);
    result = fread (data,1,size,pFile);
    if(result != size)
      {
        printf("read data error %d", result);
        return data;
      }
    data[size] ='\0';

    fclose (pFile);
    *_sz = result;
  }
  return data;
}

inline char GetB64Char(int index) 
{ 
	const char szBase64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 
	if (index >= 0 && index < 64) 
		return szBase64Table[index]; 
	 
	return '='; 
} 
inline int Base64Encode(char * base64code, const char * src, int src_len)  
{    
	if (src_len == 0) 
		src_len = strlen(src); 
	 
	int len = 0; 
	unsigned char* psrc = (unsigned char*)src; 
	char * p64 = base64code; 
	int i=0;
	for (i = 0; i < src_len - 3; i += 3) 
	{ 
		unsigned long ulTmp = *(unsigned long*)psrc; 
		register int b0 = GetB64Char((B0(ulTmp) >> 2) & 0x3F);  
		register int b1 = GetB64Char((B0(ulTmp) << 6 >> 2 | B1(ulTmp) >> 4) & 0x3F);  
		register int b2 = GetB64Char((B1(ulTmp) << 4 >> 2 | B2(ulTmp) >> 6) & 0x3F);  
		register int b3 = GetB64Char((B2(ulTmp) << 2 >> 2) & 0x3F);  
		*((unsigned long*)p64) = b0 | b1 << 8 | b2 << 16 | b3 << 24; 
		len += 4; 
		p64  += 4;  
		psrc += 3; 
	} 
	 
	if (i < src_len) 
	{ 
		int rest = src_len - i; 
		unsigned long ulTmp = 0; 
		for (int j = 0; j < rest; ++j) 
		{ 
			*(((unsigned char*)&ulTmp) + j) = *psrc++; 
		} 
		 
		p64[0] = GetB64Char((B0(ulTmp) >> 2) & 0x3F);  
		p64[1] = GetB64Char((B0(ulTmp) << 6 >> 2 | B1(ulTmp) >> 4) & 0x3F);  
		p64[2] = rest > 1 ? GetB64Char((B1(ulTmp) << 4 >> 2 | B2(ulTmp) >> 6) & 0x3F) : '=';  
		p64[3] = rest > 2 ? GetB64Char((B2(ulTmp) << 2 >> 2) & 0x3F) : '=';  
		p64 += 4;  
		len += 4; 
	} 
	 
	*p64 = '\0';  
	 
	return len; 
} 

int Base64Decode(char * buf, const char * base64code, int src_len)
{
        if (src_len == 0)
                src_len = strlen(base64code);

        int len = 0;
        unsigned char* psrc = (unsigned char*)base64code;
        char * pbuf = buf;
        int i=0;
        for (i = 0; i < src_len - 4; i += 4)
        {
                unsigned long ulTmp = *(unsigned long*)psrc;

                register int b0 = (GetB64Index((char)B0(ulTmp)) << 2 | GetB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF;
                register int b1 = (GetB64Index((char)B1(ulTmp)) << 4 | GetB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF;
                register int b2 = (GetB64Index((char)B2(ulTmp)) << 6 | GetB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF;

                *((unsigned long*)pbuf) = b0 | b1 << 8 | b2 << 16;
                psrc  += 4;
                pbuf += 3;
                len += 3;
        }

        if (i < src_len)
        {
                int rest = src_len - i;
                unsigned long ulTmp = 0;
                for (int j = 0; j < rest; ++j)
                {
                        *(((unsigned char*)&ulTmp) + j) = *psrc++;
                }

                register int b0 = (GetB64Index((char)B0(ulTmp)) << 2 | GetB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF;
                *pbuf++ = b0;
                len  ++;

                if ('=' != B1(ulTmp) && '=' != B2(ulTmp))
                {
                        register int b1 = (GetB64Index((char)B1(ulTmp)) << 4 | GetB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF;
                        *pbuf++ = b1;
                        len  ++;
                }
                if ('=' != B2(ulTmp) && '=' != B3(ulTmp))
                {
                        register int b2 = (GetB64Index((char)B2(ulTmp)) << 6 | GetB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF;
                        *pbuf++ = b2;
                        len  ++;
                }

        }

        *pbuf = '\0';
        return len;
}
 
#if 0
inline int Base64Decode(char * buf, const char * base64code, int src_len)  
{    
	if (src_len == 0) 
		src_len = strlen(base64code); 
 
	int len = 0; 
	unsigned char* psrc = (unsigned char*)base64code; 
	char * pbuf = buf; 
	int i=0;
	for (i = 0; i < src_len - 4; i += 4) 
	{ 
		unsigned long ulTmp = *(unsigned long*)psrc; 
		 
		register int b0 = (GetB64Index((char)B0(ulTmp)) << 2 | GetB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF; 
		register int b1 = (GetB64Index((char)B1(ulTmp)) << 4 | GetB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF; 
		register int b2 = (GetB64Index((char)B2(ulTmp)) << 6 | GetB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF; 
		 
		*((unsigned long*)pbuf) = b0 | b1 << 8 | b2 << 16; 
		psrc  += 4;  
		pbuf += 3; 
		len += 3; 
	} 
 
	if (i < src_len) 
	{ 
		int rest = src_len - i; 
		unsigned long ulTmp = 0; 
		for (int j = 0; j < rest; ++j) 
		{ 
			*(((unsigned char*)&ulTmp) + j) = *psrc++; 
		} 
		 
		register int b0 = (GetB64Index((char)B0(ulTmp)) << 2 | GetB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF; 
		*pbuf++ = b0; 
		len  ++; 
 
		if ('=' != B1(ulTmp) && '=' != B2(ulTmp)) 
		{ 
			register int b1 = (GetB64Index((char)B1(ulTmp)) << 4 | GetB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF; 
			*pbuf++ = b1; 
			len  ++; 
		} 
		 
		if ('=' != B2(ulTmp) && '=' != B3(ulTmp)) 
		{ 
			register int b2 = (GetB64Index((char)B2(ulTmp)) << 6 | GetB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF; 
			*pbuf++ = b2; 
			len  ++; 
		} 
 
	} 
		 
	*pbuf = '\0';  
	 
	return len; 
}  
#endif

inline int GetB64Index(char ch) 
{ 
	int index = -1; 
	if (ch >= 'A' && ch <= 'Z') 
	{ 
		index = ch - 'A'; 
	} 
	else if (ch >= 'a' && ch <= 'z') 
	{ 
		index = ch - 'a' + 26; 
	} 
	else if (ch >= '0' && ch <= '9') 
	{ 
		index = ch - '0' + 52; 
	} 
	else if (ch == '+') 
	{ 
		index = 62; 
	} 
	else if (ch == '/') 
	{ 
		index = 63; 
	} 
 
	return index; 
} 

int my_main(int argc, char *argv[])
{
  int size;
  char plain[4086];
  std::string in= "AAACtPW9AAAAgA5g7GQTuRI9rYgsFtxCoJSD0AR6nDCg90iB3y1Hu0tEcfR5IM5nVXPCcUW7jjzwG4lsWap7L1nJU32dDGmQ0tg9gJmGeew15k1xjsycCZ0M7xdPiQttnCO9vU6lWPfTKHLP+O+W/2GT9NPmfOqmh+Vzvd7ypXTiPNrNCOvu0xgibmz1FgdSLJ0MHLotBD4MxXV7CvkwKstho5UnxRZoMFGgVBh2xDMPqs7N/AtODP+vEsOqlAejmLTLTL+PkOCuQarQXobtP/UvUSH7oVFEqNL+ZNEOAjWHcixRUMmc3J4+A4S9pAZNOzeRgaHQAH28UmNtjaiFCq+4HfOQUrur9me6LuZe5VXm3ttbQy3NffeN3hEUjs4S3RUmg256KN0R9lJ2AVmD+hI5t16m9zqwO1Lky+aKdTqstA1LYSIOf8r+XsfjRz/QCty5CiH+Obxc0O+6w+eDB1Eg38S2kQSK3gEhoITqqz6cWUlEW3dXktHaaxi0tauZJk0+fXnVOyZNrxXMeS0K/pv3S3sJ7576TCDVp7kkaLmw/bZEwsaoT2OBQPw1aEU2y9RRFQcj80OOs+3rKVvd6EYe2yoGkRyvg9XCQFHW54In8lXWvR00LxQbaGCNl83y9AD64Two2HlKSjuUPGrV3f8FKOW39OE53AuPadct3lr7WO6K7HXhPqLioygpbzDnjoW4MXZWsM6K7lmUTK8DFDo47S5kvvWJOvp3r1XbhvmII0/TsUQrwqBc2iO7Cu5PStqRgaqiyHJguHq3DgIcS9kfo3zABzwquLsQubwI03np7xFRFvpY2UcA6eQq7hT9W7Nlb2h9AW92T364aCCP33DaModp3wu8gEvEAS81q6TIfHHgCp2WgKOOlbJAivDcK2hzadAe/KoRmiLBfeWfgzeuLAxNI4MDPTU=";
  in = "AAAENIKdAAAAgJnd3ZHMSQQeyw9erRyPW4T2CrAC5D4Di7spCNQiCDzf0jIZmspr0sUo0x4ThsZsuhXU5T+ztozIgC6xrmGnK8DM1d3qafVAgAmP43Fl+zjs0zhikzvgCphWuke3QN/+bRU/kpiEOXcuIrhPQUHqri+osRDM0lEksvUhSA0wXHw0GUFDkvGScctzXZXUsDTrPDLNir4WEfSE0SYyq4P0T9i3RlGABvJGMw0dVbsBhRSxthrBwDslIxQZUGWf7LiSweeU5o+aZMS+eTzkl6sM9dynEms5HJNZ44zu48IFMZk+YdNES6iK0KaKCWXbuXnQMyZ+yVbxzsQq/yvb1eFaaKW675yzf7FcwSa4ijWq7l2UspOoq+wPjYBqY+4hFm0+zaxDpK790wWJ4KY6gLbi/rdKg2hjanw5PPgMmbkKVK/F4B+2brCjDNEfOHmyBca/0h3BEpXJiO1qspUYE9kkT+rXmAgludn5UnfCX3fEZG1RiOncDD2fqT1E+CMycvrgZiKdfo88M6+NnGnm85MKJCC7wY/9xGizsf6Y7k+Cvy1dPljD9Lb8rbwanOdGEA9su8a+ICsAs1bim/Pn/CAsY24vqBNfBBFebjNiePO7ji24E16+BnJXQrSae7p3zeZXnVPcGP73Xo7xjN5D+0RB7j5sACTRpDKvh7lwIzWsaCsWT4gXSz1IxUXxhd9BFmw+Lhp1Lg2O7+aOH3mQgaLFXR27OZL966ho/3n8qt/bKCq40C8lljMjSCX3QU4sxwJyJYMbwEEXhAklDR7J7Bc/2bUZpGiE2paQ9uJ6a6x9FLRcZSXN7Z+xaetd23r6f4pQiz4e+Qhiq3ExC4HpKjAz8qT4RE+72HF0EyFHCLWLirAbRufycwlmiByaeQEj/3PIzMDtzE7uQQPy8DtT6BkXovtbGU7GX/WXnt5XLHXtSVsUmlh2AgD2XQqq8CXYU4n+oHJBpsoRsnyDXn+Rd8sdF5pvzUD6iKQ2mvNjSIlKO6RnuEwXF4uiUCg6fbxSrzjqE+WMKdIsSli2RWn+u+KThUI88BfII7QKubCa6bqInIuo6gCQ/tDTsP4dgXytLB99uYHchjc6P+I+EGGcIUuio0pK6CPuSZ3xwHP8Zkp3qvps7y4xQVnkXKlbd/NqRHOfEDFRj4jFyFO9C/pK9U5OmmfDJb/fjxsbH9H0c6Ob9s74TYd0rLguvCuDSNrRd/s0ne4dPyCjaceZLw5wo1hsDdBRq1/yS/08ix0Uqb1b8Msg0Hqpl8XausOwTND/6w1bxX4hIl92voAYkmHMhAVrwLf/xnnW4s6fvIpxF74lV6lLrXgeb1ze56qJQqMPDK4bnxB6Pc8PQrSKcybJQufgiktDn2tBNtUrNTJg5erbZ5tRah+zPe5dd15USi48ry9rC/Mq6c1msiem8gSFQMikcis";
  std::string result1, result2;
  bool re = Base64Decode(in,&result2);
  std::cout<<"len"<<result2.length()<<std::endl;
  return 0;
}
