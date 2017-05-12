#ifndef CRYPT_TASK_HPP
#define CRYPT_TASK_HPP
#include <sys/types.h>
#include <string>
#include "common/Logger.h"
#include "common/Json.hpp"

using std::string;
#define MEM_BUFF_SIZE 20480
typedef unsigned char BYTE;         
class CryptTask
{

public:
  static int getHeadLen(char* cryptData, int dataLen);
  static bool Crypt(string &src, string &des);
  static uint16_t crc16_ccitt(BYTE *ucbuf, int iLen);
private:
  DECL_LOGGER(logger);
};

#endif // CRYPT_TASK_HPP
