#ifndef _MUTEXTLOCK_H
#define  _MUTEXTLOCK_H

#include <pthread.h>

class MutexLock
{
public:
	MutexLock()
	{
		pthread_mutex_init(&m_lock, NULL);
	}
	~MutexLock()
	{
		pthread_mutex_destroy(&m_lock);
	}
	void lock()
	{
		pthread_mutex_lock(&m_lock);	
	}
	void unlock()
	{
		pthread_mutex_unlock(&m_lock);		
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
};

class AutoLock
{
public:
	AutoLock(const pthread_mutex_t& lock)
	{
		m_lock_p = const_cast<pthread_mutex_t*>(&lock);
		pthread_mutex_lock(m_lock_p);
	}
	AutoLock(const pthread_mutex_t* lock)
	{
		m_lock_p = const_cast<pthread_mutex_t*>(lock);
		pthread_mutex_lock(m_lock_p);
	}	

	~AutoLock()
	{
		pthread_mutex_unlock(m_lock_p);
	}

	
private:
	pthread_mutex_t* m_lock_p;
};

class AutoRDLock
{
public:
	AutoRDLock(const pthread_rwlock_t& lock)
	{
		m_lock_p = const_cast<pthread_rwlock_t*>(&lock);
		pthread_rwlock_rdlock(m_lock_p);
	}
	AutoRDLock(const pthread_rwlock_t* lock)
	{
		m_lock_p = const_cast<pthread_rwlock_t*>(lock);
		pthread_rwlock_rdlock(m_lock_p);
	}	

	~AutoRDLock()
	{
		pthread_rwlock_unlock(m_lock_p);
	}
	
private:
	pthread_rwlock_t* m_lock_p;
};

class AutoWRLock
{
public:
	AutoWRLock(const pthread_rwlock_t& lock)
	{
		m_lock_p = const_cast<pthread_rwlock_t*>(&lock);
		pthread_rwlock_wrlock(m_lock_p);
	}
	AutoWRLock(const pthread_rwlock_t* lock)
	{
		m_lock_p = const_cast<pthread_rwlock_t*>(lock);
		pthread_rwlock_wrlock(m_lock_p);
	}	

	~AutoWRLock()
	{
		pthread_rwlock_unlock(m_lock_p);
	}
	
private:
	pthread_rwlock_t* m_lock_p;
};

#endif //


