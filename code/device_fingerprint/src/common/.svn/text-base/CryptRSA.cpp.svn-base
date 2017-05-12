#include "Logger.h"
#include "CryptRSA.hpp"

#include <fstream>
#include <iterator>

IMPL_LOGGER(CryptRSA, logger);
CryptRSA::CryptRSA(string &prifile, int padding)
  :m_prifile(prifile)
  ,m_rsa(NULL)
  ,m_pemkey(NULL)
  ,m_padding(padding)
{
  readFile();
}

CryptRSA::~CryptRSA(){
  //删除已读取的密钥信息
  if(m_pemkey)
    delete m_pemkey;
  if(m_rsa)
    RSA_free(m_rsa);
}

void CryptRSA::createRSA(){
  BIO *keybio ;
  keybio = BIO_new_mem_buf((void *)m_pemkey->data(), -1);
  if (keybio==NULL)
    {
      printf( "Failed to create key BIO\n");
      return;
    }
  
  m_rsa = PEM_read_bio_RSAPrivateKey(keybio, &m_rsa,NULL, NULL);
  if(m_rsa == NULL)
    {
      printf( "Failed to create RSA\n");
      return;
    }
  BIO_free(keybio);
}

int CryptRSA::privKeyDecrypt(unsigned char * enc_data,int data_len,unsigned char *decrypted){
  if(NULL == m_rsa)
    createRSA();
  
  if(m_rsa == NULL){
    printf("errrrrrrrrr\n");
    return -1;
  }
  int result = RSA_private_decrypt(data_len,enc_data,decrypted,m_rsa,m_padding);
  return result;
}

int CryptRSA::publicEncrypt(unsigned char * data,int data_len, unsigned char *encrypted){
  //TODO
  return 0;
}


void CryptRSA::printLastError()
{
  char err[130] = {0};
  ERR_load_crypto_strings();
  ERR_error_string(ERR_get_error(), err);
  printf("ERROR: %s\n", err);
}

bool CryptRSA::readFile(){
  std::ifstream infile(m_prifile.data()) ;
  if (infile) {
    m_pemkey = new string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    //    cout<<m_pemkey;
    infile.close();
    return true ;
  }
  else {
    //    std::cout << "file not found!\n" ;
    return false ;
  }
}

void CryptRSA::createInstance(string &prifile)
{
  if(not m_instance)
    m_instance = new CryptRSA(prifile);
}
CryptRSA* CryptRSA::getInstance()
{
  return m_instance;
}
void CryptRSA::destroy()
{
  delete m_instance;
}
CryptRSA* CryptRSA::m_instance = NULL;
