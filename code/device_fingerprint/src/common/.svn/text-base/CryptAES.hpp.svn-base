#ifndef CRYPTAES_HPP
#define CRYPTAES_HPP

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <string>
#include <sys/types.h>
#include "common/Logger.h"

using std::string;

class CryptAES{
public:
  CryptAES();
  ~CryptAES();
  
  string* aesDecrypt(const std::string& ciphertext, const std::string& key);
  void aesDecrypt(u_char *ciphertext, size_t encsiz, const std::string& key, u_char *result, size_t &resLen);
private:
  DECL_LOGGER(logger);

};

#endif  //  CRYPTRSA_HPP
