/**********************************************************************\
 * thread.h
 *
 *  Created on: 2013-7-18
 *      Author: WANG YAN SHUN
 *   Copyright: Autel
 * Description: 线程对象
 *
 ***********************************************************************/

#ifndef __THREAD_H__
#define __THREAD_H__

#ifndef _WIN32

#include<pthread.h>

#include"run.h"

/**
 * @class ThreadParams
 * @brief 线程参数
 */
typedef struct _ThradParams{

	void*        ptrData;
	int          iParam;
	unsigned int uParam;

}ThreadParams;

/**
 * @class ThreadState
 * @brief 线程状态
 */
enum ThreadState{

	/**
	 * @brief 线程处于等待状态 此时可以绑定新的线程任务
	 */
	THREAD_IS_WAITING,

	/**
	 * @brief 线程处于运行状态
	 */
	THREAD_IS_RUNNING,

	/**
	 * @brief 线程已经被成功创建
	 */
	THREAD_IS_CREATED,

	/**
	 * @brief 线程正处于即将被关闭状态
	 */
	THREAD_IS_STOPPING,

	/**
	 * @brief 线程已经停止运行 此时需要重新start
	 */
	THREAD_IS_STOPPED
};

/**
 * @class Thread
 * @brief 线程对象 将线程封装成对象 以对象的方式操作线程
 */
class Thread{
public:
	Thread();
	explicit Thread( IRun* ptrRun );
	explicit Thread( IRun* ptrRun, const ThreadParams& threadParams );
	~Thread();

public:

	static void* Execute( void* ptrData );

public:

	pthread_t GetId();

	int   Start( IRun* ptrRun );
	IRun* Stop( struct timespec* timeout = NULL );

private:
     Condition       m_condtionWaitNewTask;
private:
     volatile  bool  m_isNeedStop;
     ThreadState     m_threadState;

private:
	 ThreadParams    m_threadParams;
	 IRun*           m_ptrRun;
	 pthread_t       m_threadId;
};

#endif // __TARGET_PLAT_LINUX__

#endif /* __THREAD_H__ */
