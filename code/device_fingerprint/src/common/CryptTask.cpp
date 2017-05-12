#include "CryptTask.hpp"
#include "CryptRSA.hpp"
#include "CryptAES.hpp"
#include "common/ConfigReader.h"
#include "Logger.h"
#include "base64.h"
#include <arpa/inet.h>
#include <string>
#include <algorithm>
#include "Utility.h"


extern ConfigReader *g_config_reader;
CryptRSA* safe_rsa = NULL;

IMPL_LOGGER(CryptTask, logger);
uint16_t CryptTask::crc16_ccitt(BYTE *ucbuf, int iLen)
{
    uint16_t crc = 0xFFFF;          // initial value
    uint16_t polynomial = 0x1021;   // 0001 0000 0010 0001  (0, 5, 12)
    int i,j;
    for (j = 0; j < iLen; ++j) {
        for (i = 0; i < 8; i++) {
            char bit = ((ucbuf[j]   >> (7-i) & 1) == 1);
            char c15 = ((crc >> 15    & 1) == 1);
            crc <<= 1;
            if (c15 ^ bit) crc ^= polynomial;
        }
    }
    
    crc &= 0xffff;
    
    return crc;
}

//data=(len:4 + crc:2 + keylen:4 + key + payload)
int CryptTask::getHeadLen(char* cryptData, int dataLen)
{
    if(dataLen < 10)
    {
        LOG4CPLUS_ERROR(logger, "data lenght too short:" << dataLen);
        return -1;
    }
    int32_t mesglen =0, headerlen = 0;
    int *i, *j;
    i = (int*) cryptData;
    mesglen = ntohl(*i);
    uint16_t* k = (uint16_t*)(++i);
    
    uint16_t ocrc = ntohs(*k);
    uint16_t icrc = crc16_ccitt((uint8_t *)(cryptData + 6), dataLen - 6);
    i = (int*) (cryptData + 6);
    headerlen = ntohl(*i);
    
    if(ocrc != icrc)
    {
        LOG4CPLUS_ERROR(logger, "crc error");
        return -1;
    }
    
    return headerlen;
}

//data=(len:4 + crc:2 + keylen:4 + key + payload)
bool CryptTask::Crypt(string &src, string &des)
{
    if(safe_rsa == NULL)
    {
        string filename = g_config_reader->get_string("account_service.privatekey", "private.key");
        safe_rsa = new CryptRSA(filename);
    }
    size_t result_len = 0;
    std::string output;
    unsigned char bufen[256] = {0};
    unsigned char bufkey[32] = {0};
    char memorySrc[MEM_BUFF_SIZE];
    char memoryDst[MEM_BUFF_SIZE];
    memset(memorySrc, 0, MEM_BUFF_SIZE);
    memset(memoryDst, 0, MEM_BUFF_SIZE);
    char *result = memoryDst;
    int b64len = src.length();
    char* befor64 = (char*)malloc(b64len+1);
    int reallen = Utility::base64Pre(src, befor64);
    befor64[reallen]='\0';
    string afterPre = string(befor64);
    free(befor64);
    bool rret = Base64Decode(afterPre, &output);
    //bool rret = Base64Decode(src, &output);
    if(rret = false)
    {
        return false;
        LOG4CPLUS_ERROR(logger, "base 64 decode error:" << afterPre);
    }
    int m_len = output.length();
    char *m_pData = memorySrc;
    memcpy(m_pData, output.data(), output.length());
    
    if(m_len < 10)
    {
        LOG4CPLUS_ERROR(logger, "crc error:" << src << " len:" << b64len);
        LOG4CPLUS_ERROR(logger, "crc error:" << afterPre << " len:" << reallen);
        return false;
    }
    else
    {
        CryptRSA *cryptRSA = (CryptRSA *)safe_rsa;
        //CryptRSA *cryptRSA = CryptRSA::getInstance();
        int len = getHeadLen(m_pData, m_len);
        if(len == -1 )
        {
            LOG4CPLUS_ERROR(logger, "get headlen -1:" << src << " len:" << b64len);
            LOG4CPLUS_ERROR(logger, "get headlen -1:" << afterPre << " len:" << reallen);
            LOG4CPLUS_ERROR(logger, "get headlen -1");
            return false;
        }
        else
        {
            memcpy(bufen, m_pData + 10 , len);
            int ret = cryptRSA->privKeyDecrypt(bufen, len, bufkey);
            string key((char *)bufkey);
            if(key.size() < 1)
            {
                LOG4CPLUS_ERROR(logger, "rsa key failture -1:" << src << " len:" << b64len);
                LOG4CPLUS_ERROR(logger, "rsa key failture -1:" << afterPre << " len:" << reallen);
                LOG4CPLUS_ERROR(logger,"Rsa key failture!");
                return false;
            }
            else
            {
                CryptAES cryptAES;  
                u_char *ciphertext = (u_char *)m_pData + len + 10;
                size_t cip_len = m_len - len - 10;
                
                cryptAES.aesDecrypt(ciphertext,cip_len, key, (u_char*)result, result_len);
                des = string(result, result_len);
                return true;
            }
        }
    }
    return false;
}
