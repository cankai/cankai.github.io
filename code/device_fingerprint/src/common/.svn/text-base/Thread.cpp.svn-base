#include <exception>
#include "Thread.h"

using namespace std;

IMPL_LOGGER(Thread, logger)

Thread::Thread(int stack_size)
{
	m_thread_id = 0;
	m_stack_size = stack_size;
	m_should_stop = false;
	m_is_started = false;

	m_detachable = false;

	m_thread_counter = NULL;
}

Thread::~Thread()
{

}

bool Thread::start(bool force_restart)
{
	if(m_is_started && !force_restart)
		return false;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	// set stack size
	if(m_stack_size > 0)
		pthread_attr_setstacksize(&attr, m_stack_size);
	if(m_detachable)
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); 

	if(0 != pthread_create(&m_thread_id, &attr, threadProc, (void*)this))
		return false;

	m_is_started = true;

	pthread_attr_destroy(&attr);

	return true;
}

void Thread::wait_terminate()
{
	if(m_detachable)
		return;
	else
		pthread_join(m_thread_id, NULL);
}

void* Thread::threadProc(void* param)
{
	Thread* me = (Thread*) param;
	me->run();
	me->m_is_started = false;
	
	return NULL;
}
