#include "CryptAES.hpp"
#include "common/Logger.h"

IMPL_LOGGER(CryptAES, logger);
CryptAES::CryptAES(){
}

CryptAES::~CryptAES(){
}

string* CryptAES::aesDecrypt(const std::string& ciphertext, const std::string& key)
{
  EVP_CIPHER_CTX ctx;
  EVP_CIPHER_CTX_init(&ctx);
  int ret = EVP_DecryptInit_ex(&ctx, EVP_aes_128_ecb(), NULL, (const unsigned char*)key.data(), NULL);
  //  assert(ret == 1);
  if(ret != 1){
      LOG4CPLUS_ERROR(logger, "EVP_DecryptInit_ex err");
  }
  unsigned char* result = new unsigned char[ciphertext.length() + 64]; // 弄个足够大的空间
  LOG4CPLUS_DEBUG(logger,"lenData" << ciphertext.length() + 64);
  
  int len1 = 0;
  ret = EVP_DecryptUpdate(&ctx, result, &len1, (const unsigned char*)ciphertext.data(), ciphertext.length());
  //  assert(ret == 1);
  if(ret != 1){
      LOG4CPLUS_ERROR(logger,"EVP_DecryptUpdate err");
  }
  int len2 = 0;
  ret = EVP_DecryptFinal_ex(&ctx, result+len1, &len2);
  
  if(ret != 1){
      LOG4CPLUS_ERROR(logger,"EVP_DecryptFinal_ex err");
  }
    LOG4CPLUS_DEBUG(logger,"len1" << len1);
    LOG4CPLUS_DEBUG(logger,"len2" << len2);

  ret = EVP_CIPHER_CTX_cleanup(&ctx);
  
  if(ret != 1){
      LOG4CPLUS_ERROR(logger,"EVP_CIPHER_CTX_cleanup err");
  }

  std::string *res = new string((char*)result, len1+len2);
  delete[] result;
  return res;
}


void CryptAES::aesDecrypt(u_char *ciphertext, size_t encsiz, const std::string& key, u_char *result, size_t &resLen)
{
  EVP_CIPHER_CTX ctx;
  EVP_CIPHER_CTX_init(&ctx);
  int ret = EVP_DecryptInit_ex(&ctx, EVP_aes_128_ecb(), NULL, (const unsigned char*)key.data(), NULL);
  if(ret != 1){
      LOG4CPLUS_ERROR(logger,"EVP_DecryptInit_ex err");
  }
  int len1 = 0;
  ret = EVP_DecryptUpdate(&ctx, result, &len1, (const unsigned char*)ciphertext, encsiz);
  if(ret != 1){
      LOG4CPLUS_ERROR(logger,"EVP_DecryptUpdate err");
  }
  int len2 = 0;
  ret = EVP_DecryptFinal_ex(&ctx, result+len1, &len2);
  
  if(ret != 1){
      LOG4CPLUS_ERROR(logger,"EVP_DecryptFinal_ex err");
  }

  ret = EVP_CIPHER_CTX_cleanup(&ctx);
  
  if(ret != 1){
      LOG4CPLUS_ERROR(logger,"EVP_CIPHER_CTX_cleanup err");
  }

  resLen = len1 + len2;
}

