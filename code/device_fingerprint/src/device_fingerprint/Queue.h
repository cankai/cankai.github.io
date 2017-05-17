#ifndef _QUEUE_H
#define _QUEUE_H
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>
#include <exception>
#include "common/MutexLock.h"
#include <set>
#include <vector>

using set;
using vector;
template <class T> 
class Pool{
    T*  m_buffer;

    int m_capacity;
    int m_used;
    int m_free;
    pthread_mutex_t m_lock;
    pthread_cond_t    m_cond_not_full;
    pthread_cond_t    m_cond_not_empty;

public:
    Pool(int capacity)
    {
        m_buffer = NULL;
        m_capacity = capacity;
        m_used = 0;
        m_free = capacity;

        pthread_mutex_init(&m_lock, NULL);
        pthread_cond_init(&m_cond_not_full, NULL);
        pthread_cond_init(&m_cond_not_empty, NULL);
    }
    virtual ~Pool()
    {
        freeBuffer(m_buffer);
        pthread_mutex_destroy(&m_lock);
        pthread_cond_destroy(&m_cond_not_full);
        pthread_cond_destroy(&m_cond_not_empty);
    }
    int getCapacity()
    {
        return m_capacity;
    }

    int getUsed()
    {
        return m_used;
    }

    int getFree()
    {
        return m_free;
    }
protected:
    virtual T* allocBuffer(int capacity)
    {
        return new T[capacity];
    }
    virtual void freeBuffer(T* pBuffer)
    {    
        if(pBuffer)
            delete []pBuffer;
    }

private:
    bool checkBuffer()
    {
        if(m_buffer == NULL)
        {
            m_buffer = allocBuffer(m_capacity);
        }

        return m_buffer != NULL;
    }
};
#endif
