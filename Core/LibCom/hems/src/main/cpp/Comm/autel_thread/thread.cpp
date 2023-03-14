#include "thread.h"

#ifndef _WIN32

#include<memory.h>
#include <pthread.h>
#include <stdio.h>

Thread::Thread(): m_isNeedStop(false),m_threadState(THREAD_IS_STOPPED),m_ptrRun(NULL){

	memset(&m_threadParams,0,sizeof(ThreadParams));
}

Thread::Thread( IRun* ptrRun ): m_isNeedStop(false),m_threadState(THREAD_IS_STOPPED),m_ptrRun(ptrRun){

	memset(&m_threadParams, 0, sizeof(ThreadParams));
}

Thread::Thread( IRun* ptrRun, const ThreadParams& threadParams ): m_isNeedStop(false),m_threadState(THREAD_IS_STOPPED),m_ptrRun(ptrRun){

	memcpy(&m_threadParams, &threadParams, sizeof(ThreadParams));
}

void* Thread::Execute(void* ptrData){


	Thread* ptrTarget = reinterpret_cast<Thread*>( ptrData );

	ptrTarget->m_threadState = THREAD_IS_CREATED;

    while (!ptrTarget->m_isNeedStop) {

		int nTime = 0;
		bool bLoop = false;
		if (ptrTarget->m_ptrRun) {

            ptrTarget->m_threadState = THREAD_IS_RUNNING;
            ptrTarget->m_ptrRun->Run(ptrTarget->m_threadParams.ptrData, ptrTarget->m_threadParams.uParam, ptrTarget->m_threadParams.iParam);
			bLoop = ptrTarget->m_ptrRun->IsLoop(nTime);
		}

		ptrTarget->m_threadState = THREAD_IS_WAITING;

		if(!bLoop)
		{
			break;
		}
		else
		{
			struct timespec spec;
			spec.tv_sec = nTime/1000;
			spec.tv_nsec = nTime % 1000 * 1000 * 1000;
			ptrTarget->m_condtionWaitNewTask.Wait(&spec);
		}

	}

    return (void*)(0);
}

pthread_t Thread::GetId(){

	return m_threadId;
}

int Thread::Start(IRun* ptrRun){

	m_ptrRun = ptrRun;
	return pthread_create( &m_threadId, NULL, &Thread::Execute, this );
}

IRun* Thread::Stop(struct timespec* timeout){

	m_isNeedStop  = true;
    m_threadState = THREAD_IS_STOPPING;

	if( m_ptrRun ){

		m_ptrRun->Wait( timeout );
		m_condtionWaitNewTask.Signal();
		//pthread_cancel(m_threadId);
		pthread_join( m_threadId, NULL );
	}

	m_threadState = THREAD_IS_STOPPED;
	return m_ptrRun;
}
Thread::~Thread(){}

#endif //__TARGET_PLAT_LINUX__