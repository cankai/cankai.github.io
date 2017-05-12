#ifndef MUTEX_LOCK_H
#define MUTEX_LOCK_H

#include <pthread.h>

class Lock
{
public:
	Lock()
	{
		pthread_mutex_init(&m_lock, NULL);
	}
	~Lock()
	{
		pthread_mutex_destroy(&m_lock);
	}
	int lock()
	{
		return pthread_mutex_lock(&m_lock);
	}
	int try_lock()
	{
		return pthread_mutex_trylock(&m_lock);
	}
	int unlock()
	{
		return pthread_mutex_unlock(&m_lock);
	}
	pthread_mutex_t raw_lock() const
	{
		return m_lock;
	}

	pthread_mutex_t* raw_lock_ptr()
	{
		return &m_lock;
	}

private:
	pthread_mutex_t m_lock;

	friend class AutoLock;
};

class AutoLock
{
public:	
	AutoLock(pthread_mutex_t& lock) : m_lock(&lock)
	{
		pthread_mutex_lock(m_lock);
	}
	AutoLock(pthread_mutex_t* lock) : m_lock(lock)
	{
		pthread_mutex_lock(m_lock);
	}
	AutoLock(Lock& lock) : m_lock(&(lock.m_lock))
	{
		pthread_mutex_lock(m_lock);
	}
	~AutoLock()
	{
		pthread_mutex_unlock(m_lock);
	}

private:
	pthread_mutex_t* m_lock;
};
#endif

