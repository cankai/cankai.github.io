#ifndef CRYPTRSA_HPP
#define CRYPTRSA_HPP

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <string>
#include "common/Logger.h"

using std::string;

class CryptRSA {
public:
  CryptRSA(string &prifile, int padding=RSA_PKCS1_PADDING);
  ~CryptRSA();
  
  int publicEncrypt(unsigned char * data,int data_len, unsigned char *encrypted);
  int privKeyDecrypt(unsigned char * enc_data,int data_len, unsigned char *decrypted);

  static void createInstance(string &prifile);
  //         void createInstance(string &prifile)
  static CryptRSA* getInstance();
  static void destroy();

  void createRSA();
  bool readFile();
  
  static CryptRSA* m_instance;  
private:

  void printLastError();
  
  string m_prifile;
  int m_padding;
  RSA *m_rsa;
  string *m_pemkey;
  DECL_LOGGER(logger);
};

#endif  //  CRYPTRSA_HPP
