#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include "Logger.h"
#include "Counter.h"

class Thread
{
	const static int STACK_SIZE = (256 * 1024);

public:
	Thread(int stack_size = 0);
	virtual ~Thread();

	void set_detachable(bool detachable) { m_detachable = detachable; }

	bool start(bool force_restart = false);
	void wait_terminate();

	void request_stop() { m_should_stop = true; }

	void set_activethread_counter(Counter<int>* counter_p)
	{
		m_thread_counter = counter_p;
	}

	bool is_running() { return m_is_started; }
	pthread_t get_thread_id() { return m_thread_id; }

protected:
	virtual void run() = 0;
	bool should_stop() const { return m_should_stop; }

	virtual void set_active()
	{
		if(m_thread_counter != NULL)
			m_thread_counter->increase();
	}
	virtual void set_inactive()
	{
		if(m_thread_counter != NULL)
			m_thread_counter->decrease();
	}


private:
	DECL_LOGGER(logger);

	static void* threadProc(void* para);

	pthread_t m_thread_id;
	bool m_should_stop;
	bool m_detachable;
	int m_stack_size;
	bool m_is_started;

	Counter<int>* m_thread_counter;
};

#endif
