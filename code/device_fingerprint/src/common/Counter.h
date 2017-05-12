#ifndef COUNTER_H
#define  COUNTER_H

#include "common/MutexLock.h"

template <class T> 
class Counter
{
public:
	Counter() : m_count(0), m_max_count(0) { }
	virtual ~Counter() { }
	
	virtual T increase()
	{
	        T new_count = ++m_count;
	        if(new_count > m_max_count)
	            m_max_count = new_count;

	        return new_count;		
	}
	virtual T decrease()
	{
	        return --m_count;		
	}

	virtual T count() const { return m_count; }
	
	virtual T max_count() { return m_max_count; }
	virtual T reset_max() 
	{
	        int pre_max = m_max_count;
	        m_max_count = m_count;

	        return pre_max;
	}
	virtual void reset()
	{
		m_count = 0;
		m_max_count = 0;
	}

private:
	T m_count;
	T m_max_count;
};

template <class T> 
class MutexCounter : public Counter<T>
{
public:
	MutexCounter() {}
	virtual ~MutexCounter() {}

	virtual T increase()
	{
		AutoLock auto_lock(m_lock.raw_lock_ptr());
		return Counter<T>::increase();
	}
	
	virtual T decrease()
	{
		AutoLock auto_lock(m_lock.raw_lock_ptr());
		return Counter<T>::decrease();		
	}
	
	virtual T reset_max() 
	{
		AutoLock auto_lock(m_lock.raw_lock_ptr());
		return Counter<T>::reset_max();
	}

	virtual void reset() 
	{
		AutoLock auto_lock(m_lock.raw_lock_ptr());
		return Counter<T>::reset();
	}	

private:
	Lock m_lock;
};

#endif


