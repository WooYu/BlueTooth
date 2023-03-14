/**********************************************************************\
* lock.h
*
*  Created on: 2013-7-18
*      Author: WANG YAN SHUN
*   Copyright: Autel
* Description: 实现对线程同步锁的封装
*
***********************************************************************/

#ifndef __LOCK_H__
#define __LOCK_H__

#ifndef _WIN32

#include <pthread.h>
#include <stdlib.h>

#define InterlockedIncrement(ptr) __sync_add_and_fetch(ptr,1)
#define InterlockedDecrement(ptr) __sync_sub_and_fetch(ptr,1) 
#define InterlockedExchange(ptr,val) __sync_val_compare_and_swap(ptr,*ptr,val)

class Condition;
/**
* @class Mutex
* @brief 对互斥量的面向对象封装
*/
class Mutex {
public:
	Mutex();
	~Mutex();
public:
	friend class Condition;

public:

	/**
	* @brief  加锁
	* @return 若成功则返回0 否则返回错误编码
	*/
	int Lock();

	/**
	* @brief  尝试加锁
	* @return 若成功则返回0 否则为错误编码
	*/
	int TryLock();

	/**
	* @brief  解锁
	* @return 若成功则返回0 否则返回错误编码
	*/
	int UnLock();

	pthread_mutex_t* GetMutexPtr()
	{
		return &m_mutex;
	}

private:

	/**
	* @brief 执行内部初始化
	*/
	void Init();

	/**
	* @brief 执行内部资源销毁操作
	*/
	void Destroy();

private:
	pthread_mutex_t   m_mutex;
};

/**
* @class LockMutex
* @brief 锁对象
*/
class LockMutex {
public:
	inline LockMutex(Mutex* ptrMutex) :m_ptrMutex(ptrMutex) {}
	inline ~LockMutex() {};

public:
	inline void Lock() {

		m_ptrMutex->Lock();
	};

	inline bool TryLock()
	{
		return m_ptrMutex->TryLock() == 0;
	}

	inline void UnLock() {

		m_ptrMutex->UnLock();
	};

private:
	Mutex * m_ptrMutex;

};

#define  INFINITE  (-1)
#define  WAIT_TIMEOUT ETIMEDOUT
/**
*\class  Event
*\brief  事件对象
*/
class Event
{
public:

	/**
	*\brief  构造函数，每次调用会创建一个新的事件
	*\param[in] isSingled      用于指明事件创建后所处的初始状态， true 为激发态，false 非激发态
	*\param[in] isAuteReset    用于知名事件是否需要自动重置，默认自动重置
	*/
	Event(bool isSingled = false, bool isAutoReset = true);

	~Event();

public:

	/**
	*\brief  等待事件触发 或 超时退出
	*\param[in] timeout 超时时间 以毫秒为单位 默认永不超时
	*\return     == AUTEL_WAIT_TIMEOUT 等待超时
	*\              返回触发事件的索引
	*/
	unsigned long Wait(unsigned long timeout = INFINITE);

	/**
	*\brief  重置事件，让其进入非激发状态
	*/
	void Reset();

	/**
	*\brief 设置事件，让其进入激发状态
	*/
	void Set();

private:
	pthread_cond_t    m_condition;
	Mutex  m_mutex;
	bool   m_isAutoReset;
	bool   m_isSingled;
};

/**
* @class Condition
* @brief 对条件变量进行面向对象封装
*/
class Condition {
public:
	Condition();
	~Condition();
public:
	/**
	* @brief 执行等待操作
	* @param[in] timeout  设置等待超时时间 如果一直等待则将参数保持为 NULL
	* @return 成功返回0 否则返回错误编码
	*/
	int Wait(struct timespec* timeout = NULL);

	/**
	* @brief 唤醒等待该条件的某个线程
	* @return 成功返回0 否则返回错误编码
	*/
	int Signal();

	/**
	* @brief 唤醒等待该条件的所有线程
	* @return 成功返回0 否则返回错误编码
	*/
	int Broadcast();

private:

	/**
	* @brief 初始化内部资源
	*/
	void Init();

	/**
	* @brief 回收内部资源
	*/
	void Destroy();

private:
	Mutex  m_mutex;

private:
	pthread_cond_t    m_condition;
};

/**
* @class Lock
* @brief 锁模板
*/
template<typename OBJECT, typename LOCKER>
class Lock {
public:

	inline Lock(OBJECT* object, bool bTryLock = false) : m_ptrObject(object) {

		if (bTryLock)
		{
			m_bOwnsLock = LOCKER(m_ptrObject).TryLock();
		}
		else
		{
			LOCKER(m_ptrObject).Lock();
			m_bOwnsLock = true;
		}
	};

	inline bool Owns_Lock()
	{
		return m_bOwnsLock;
	}

	inline ~Lock() {

		if (m_bOwnsLock)
		{
			LOCKER(m_ptrObject).UnLock();
		}
	}

private:
	OBJECT * m_ptrObject;
	bool             m_bOwnsLock;
};

#endif //! __TARGET_PLAT_LINUX__

#endif /* __LOCK_H__ */
