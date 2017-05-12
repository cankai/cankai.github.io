/*
** Copyright (C) 2014 Wang Yaofu
** All rights reserved.
**
**Author:Wang Yaofu voipman@qq.com
**Description: The header file of base64.
*/
#ifndef _BASE64UTILS_H_
#define _BASE64UTILS_H_
#include <string>
#define B0(a) (a & 0xFF) 
#define B1(a) (a >> 8 & 0xFF) 
#define B2(a) (a >> 16 & 0xFF) 
#define B3(a) (a >> 24 & 0xFF) 

bool Base64Encode(const std::string& input, std::string* output);
bool Base64Encode(const std::string& input, char* output, size_t* len);

inline char GetB64Char(int index);
inline int GetB64Index(char ch);
bool Base64Decode(const std::string& input, std::string* output);
bool Base64Decode(const std::string& input, char* output, size_t* len);
int Base64Decode(char * buf, const char * base64code, int src_len);

#endif // #define _BASE64UTILS_H_
