#include"lock.h"
#include <stdio.h>


#ifndef _WIN32


// Mutex

Mutex::Mutex() {

	Init();
}

int Mutex::Lock() {

	return pthread_mutex_lock(&m_mutex);
}

int Mutex::TryLock() {

	return pthread_mutex_trylock(&m_mutex);
}

int Mutex::UnLock() {

	return pthread_mutex_unlock(&m_mutex);
}

void Mutex::Init() {

	pthread_mutex_init(&m_mutex, NULL);
}


void Mutex::Destroy() {

	pthread_mutex_destroy(&m_mutex);
}

Mutex::~Mutex() {

	Destroy();
}


Event::Event(bool isSingled, bool isAutoReset)
{
	m_isAutoReset = isAutoReset;
	m_isSingled = isSingled;
	pthread_cond_init(&m_condition, NULL);
}

Event::~Event()
{
	pthread_cond_destroy(&m_condition);
}

void Event::Reset()
{
	m_mutex.Lock();
	m_isSingled = false;
	m_mutex.UnLock();
}

void Event::Set()
{
	m_mutex.Lock();
	m_isSingled = true;
	pthread_cond_signal(&m_condition);
	m_mutex.UnLock();
}

unsigned long Event::Wait(unsigned long timeout)
{
	int ret = 0;
	m_mutex.Lock();
	if (!m_isSingled)
	{
		if (INFINITE == timeout)
		{
			while (!m_isSingled && ret == 0)
			{
				ret = pthread_cond_wait(&m_condition, m_mutex.GetMutexPtr());
			}

		}
		else
		{
			struct timeval tv;
			gettimeofday(&tv, NULL);
			struct timespec ts;
			ts.tv_sec = tv.tv_sec + timeout / 1000;
			ts.tv_nsec = tv.tv_usec * 1000 + (timeout % 1000) * 1000*1000;
			if (ts.tv_nsec >= 1 * 1000 * 1000 * 1000)
			{
				ts.tv_sec++;
				ts.tv_nsec -= 1 * 1000 * 1000 * 1000;
			}
			while (!m_isSingled && ret == 0)
			{
				ret = pthread_cond_timedwait(&m_condition, m_mutex.GetMutexPtr(), &ts);
			}
		}
	}
	
	if (ret==0 && m_isAutoReset)
	{
		m_isSingled = false;
	}
	m_mutex.UnLock();
	
	return ret;
}

// Condition
Condition::Condition() {

	Init();
}

int Condition::Wait(struct timespec* timeout /*= NULL*/) {

	if (NULL == timeout) {

		m_mutex.Lock();
		int ret = pthread_cond_wait(&m_condition, &m_mutex.m_mutex);
		m_mutex.UnLock();

		return ret;
	} else {

		m_mutex.Lock();
		int ret = pthread_cond_timedwait(&m_condition, &m_mutex.m_mutex, timeout);
		m_mutex.UnLock();

		return ret;
	}
}

int Condition::Signal() {

	m_mutex.Lock();
	int ret = pthread_cond_signal(&m_condition);
	m_mutex.UnLock();

	return ret;
}

int Condition::Broadcast() {

	return 0;
}

void Condition::Init() {

	pthread_cond_init(&m_condition, NULL);
}

void Condition::Destroy() {

	pthread_cond_destroy(&m_condition);
}

Condition::~Condition() {

	Destroy();
}


#endif // __TARGET_PLAT_LINUX__