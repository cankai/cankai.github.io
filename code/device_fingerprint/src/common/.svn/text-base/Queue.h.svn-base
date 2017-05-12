#ifndef _QUEUE_H
#define _QUEUE_H
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>
#include <exception>
#include "common/MutexLock.h"
#include <set>
#include <vector>

using std::set;
using std::vector;
template <class T> 
class Queue{
	T*  m_buffer;

	int m_capacity;
	int m_start;
	int m_size;
	int m_max_size;

	pthread_mutex_t m_lock;
	pthread_cond_t	m_cond_not_full;
	pthread_cond_t	m_cond_not_empty;

public:
	Queue(int capacity)
	{
		m_buffer = NULL;
		m_start = 0;
		m_size = 0;
		m_max_size = 0;
		m_capacity = capacity;

		pthread_mutex_init(&m_lock, NULL);
		pthread_cond_init(&m_cond_not_full, NULL);
		pthread_cond_init(&m_cond_not_empty, NULL);
		
	}
	virtual ~Queue()
	{
		freeBuffer(m_buffer);
		pthread_mutex_destroy(&m_lock);
		pthread_cond_destroy(&m_cond_not_full);
		pthread_cond_destroy(&m_cond_not_empty);
	}
	bool pop(T& retVal, int waitMs)
	{
		bool ret_val = false;

		AutoLock lock(m_lock);
//		pthread_mutex_lock(&m_lock);
		if(!checkBuffer())
			return false;
		try
		{
			if(m_size == 0)
			{//empty
				if(waitMs == 0)
				{//wait infinitely
					while(m_size == 0)
						pthread_cond_wait(&m_cond_not_empty, &m_lock);
				}
				else
				{//wait for a given timeout
					struct timespec timespot;

					if(waitMs > 0)
					{
						getAbsTimeout(waitMs, timespot);
					}
					else
					{//need not call gettimeofday
						timespot.tv_sec = 0;
						timespot.tv_nsec = 0;
					}
					pthread_cond_timedwait(&m_cond_not_empty, &m_lock, &timespot);
				}
			}
			if(m_size > 0)
			{
				retVal = m_buffer[m_start];
				ret_val = true;
				if(++m_start >= m_capacity)
					m_start -= m_capacity;
				m_size --;
				pthread_cond_signal(&m_cond_not_full);
			}
		}
		catch (std::exception& ) {
			//exception
			ret_val = false;
		}
		return ret_val;
	}
	bool push(const T& element, int waitMs)
	{
		bool retVal = false;
		AutoLock lock(m_lock);
//		pthread_mutex_lock(&m_lock);
		if(!checkBuffer())
			return false;
		try	
		{
			if(m_size >= m_capacity)
			{//full
				if(waitMs == 0)
				{//wait infinitely
					while(m_size >= m_capacity)
						pthread_cond_wait(&m_cond_not_full, &m_lock);
				}
				else
				{//wait for a given timeout
					struct timespec timespot;

					if(waitMs > 0)
					{
						getAbsTimeout(waitMs, timespot);
					}
					else
					{//need not call gettimeofday
						timespot.tv_sec = 0;
						timespot.tv_nsec = 0;
					}
					pthread_cond_timedwait(&m_cond_not_full, &m_lock, &timespot);
				}
			}

			if(m_size < m_capacity)
			{
				int newpos = m_start + m_size;
				if(newpos >= m_capacity)
					newpos -= m_capacity;

				m_buffer[newpos] = element;
				m_size ++;
				if(m_max_size < m_size)
					m_max_size = m_size;
				pthread_cond_signal(&m_cond_not_empty);
				retVal = true;
			}
		}
		catch (std::exception&) {
			//exception
			retVal = false;
		}

		return retVal;
	}

	bool pop(T& retVal)
	{
		return pop(retVal, -1);
	}

	bool push(T element)
	{
		return push(element, -1);
	}

	int getCapacity()
	{
		return m_capacity;
	}

	int getSize()
	{
		return m_size;
	}

	int getMaxSize(bool resetMax = true)
	{
		int maxSize = m_max_size;

		if(resetMax)
		{
			pthread_mutex_lock(&m_lock);	
			m_max_size = m_size;
			pthread_mutex_unlock(&m_lock);		
		}

		return maxSize;		
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
		
	void getAbsTimeout(int timeout, struct timespec& abstimeout)
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		timeout += (now.tv_usec / 1000);

		abstimeout.tv_sec = now.tv_sec + timeout / 1000;
		abstimeout.tv_nsec = (timeout % 1000) * 1000 * 1000;
	}

};

#endif
