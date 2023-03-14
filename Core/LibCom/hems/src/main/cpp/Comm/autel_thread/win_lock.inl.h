/**********************************************************************\
 * lock.inl.hpp
 *
 *  Created on: 2013/05/10 8:54
 *      Author: WANG YAN SHUN
 *   Copyright: Autel
 * Description: �߳�ͬ��������
 *
 ***********************************************************************/


#ifndef __LOCK_INL_HPP__
#define __LOCK_INL_HPP__

#ifdef _WIN32

#include <Windows.h>
#define __AUTEL_IN const
/**
 *\class  Event
 *\brief  �¼�����
 */
class Event{
public:

	/**
	 *\brief  ���캯����ÿ�ε��ûᴴ��һ���µ��¼�
	 *\param[in] isSingled      ����ָ���¼������������ĳ�ʼ״̬�� true Ϊ����̬��false �Ǽ���̬
	 *\param[in] isAuteReset    ����֪���¼��Ƿ���Ҫ�Զ����ã�Ĭ���Զ�����
	 *\param[in] eventName      �¼�������
	 */
	inline Event( bool isSingled = false, bool isAutoReset = true, char* eventName = NULL ){

		m_handle = CreateEvent( NULL, !isAutoReset, isSingled, NULL );
	}

	inline ~Event(){

		CloseHandle( m_handle );
	}

public:

	/**
	 *\brief  �ȴ��¼����� �� ��ʱ�˳�
	 *\param[in] timeout ��ʱʱ�� �Ժ���Ϊ��λ Ĭ��������ʱ
	 *\return     == AUTEL_WAIT_TIMEOUT �ȴ���ʱ
	 *\              ���ش����¼�������
	 */
	inline unsigned long Wait( __AUTEL_IN unsigned long timeout = INFINITE ){

		return WaitForSingleObject( m_handle, timeout );
	}

	/**
	 *\brief  �����¼����������Ǽ���״̬
	 */
	inline void Reset(){

		ResetEvent( m_handle );
	}

	/**
	 *\brief �����¼���������뼤��״̬
	 */
	inline void Set(){

		SetEvent( m_handle );
	}
    
	/**
	 *\brief ��ȡ�¼����
	 */
	inline HANDLE FetchHandle(){

		return m_handle;
	}

private:
	HANDLE  m_handle;
};

/**
 *\class  LockEvent
 *\brief  �¼���
 */
class LockEvent{
public:
	inline LockEvent( Event* event ):m_ptrEvent(event){}
	inline ~LockEvent(){}

public:
	inline void Lock(){

		m_ptrEvent->Wait();
	}

	inline void UnLock(){

		m_ptrEvent->Set();
	}

private:
	Event*       m_ptrEvent;
};

/**
 *\class Mutex
 *\brief �������
 */
class Mutex{
public:
	inline Mutex(char* mutexName = NULL){

		m_handle = CreateMutex( NULL, FALSE, NULL );
	}
	inline ~Mutex(){

		CloseHandle( m_handle );
	}

public:

	/**
	 *\brief  �ȴ����������� �� ��ʱ�˳�
	 *\param[in] timeout ��ʱʱ�� �Ժ���Ϊ��λ Ĭ��������ʱ
	 *\return     == AUTEL_WAIT_TIMEOUT �ȴ���ʱ
	 *\              ���ش����¼�������
	 */
	inline unsigned long Wait( __AUTEL_IN unsigned long timeout = INFINITE ){

		return WaitForSingleObject( m_handle, timeout );
	}

	/**
	 *\brief �ͷŻ�����
	 */
	inline void Release(){

		ReleaseMutex( m_handle );
	}

private:
	HANDLE     m_handle;
};



/**
 *\class LockMutex
 *\brief ������
 */
class LockMutex{

public:
	inline LockMutex(Mutex* mutex):m_ptrMutex(mutex){}
   inline ~LockMutex(){}

public:
	
	inline void Lock(){

		m_ptrMutex->Wait();
	}

	inline bool TryLock()
	{
		return m_ptrMutex->Wait(0) == WAIT_OBJECT_0;
	}

	inline void UnLock(){

		m_ptrMutex->Release();
	}

private:
    Mutex*      m_ptrMutex;
};

/**
 *\class  Semaphore
 *\brief  �ź�����
 */
class Semaphore{
public:
	/**
	 *\brief  ���캯����ÿ�ε��ö��ᴴ��һ���ź�������
	 *\param[in] initCount     ��ʼ���Է��ʹ�����Դ�ķ���������
	 *\param[in] maxCount      ����ͬʱ���ʹ�����Դ�ķ���������
	 *\param[in] semaphoreName �ź�������
	 */
	inline Semaphore(unsigned long initCount = 1, unsigned long maxCount = 1, char* semaphoreName = NULL){

		m_handle = CreateSemaphoreA( NULL, initCount, maxCount, NULL );
	}

	inline ~Semaphore(){

		CloseHandle( m_handle );
	}

public:
	
	/**
	 *\brief  �ȴ����������� �� ��ʱ�˳�
	 *\param[in] timeout ��ʱʱ�� �Ժ���Ϊ��λ Ĭ��������ʱ
	 *\return     == AUTEL_WAIT_TIMEOUT �ȴ���ʱ
	 *\              ���ش����¼�������
	 */
	inline unsigned long Wait( __AUTEL_IN unsigned long timeout = INFINITE ){

		return WaitForSingleObject( m_handle, timeout );
	}

	/**
	 *\brief �ͷ��ź���
	 */
	inline void Release(){

		ReleaseSemaphore( m_handle, 1, NULL );
	}

private:
	HANDLE    m_handle;
};

/**
 *\class LockSemaphore
 *\brief �ź�����
 */
class LockSemaphore{
public:
	inline LockSemaphore(Semaphore* semaphore):m_ptrSemaphore(semaphore){}
	inline ~LockSemaphore(){}

public:
	
	inline void Lock(){

		m_ptrSemaphore->Wait();
	}

	inline void UnLock(){

		m_ptrSemaphore->Release();
	}

private:
	Semaphore*     m_ptrSemaphore;
};

/**
 *\class  KernelObjectManager ���ڶ��ں˶��� Event��Mutex��Semaphore����������
 *\brief  ���ڶԶ���¼����й���
 */
template<class KERNEL_OBJECT>
class KernelObjectManager{
public:
	inline KernelObjectManager( KERNEL_OBJECT* ptrKernelObjectArray, unsigned long count){

		assert( count > 0 && ptrKernelObjectArray != NULL );
		m_arraySize = count;
		m_ptrKernelHandleArray = new HANDLE[count];

		for ( int index = 0; index < count; ++index){

			m_ptrKernelHandleArray[index] = ptrKernelObjectArray[index]->FetchHandle();
		}

	}
	inline ~KernelObjectManager(){

		m_arraySize = 0;
		delete[] m_ptrKernelHandleArray;
	}

public:

	/**
	 *\brief  �ȴ��ں˶��󷵻�
	 *\param[in]  needWaitAll true ��Ҫ�ȴ������¼�, false �в����¼���������ʱ��Ĭ�ϵȴ����ַ���
	 *\param[in]  timeout     �ȴ���ʱʱ�䣬Ĭ��������ʱ
	 *\return     == AUTEL_WAIT_TIMEOUT �ȴ���ʱ
	 *\              ���ش����¼�������
	 */
	inline unsigned long Wait( __AUTEL_IN bool needWaitAll = false, __AUTEL_IN unsigned long timeout = 0 ){

		return WaitForMultipleObjects( m_arraySize, m_ptrKernelHandleArray, needWaitAll, timeout);
	}

private:
     HANDLE*              m_ptrKernelHandleArray;
	 unsigned long              m_arraySize;
};

/**
 *\class  CriticalSection
 *\brief  �ٽ�������
 */
class CriticalSection{
public:
	inline CriticalSection(){

		InitializeCriticalSection( &m_criticalSection );
	}
	inline ~CriticalSection(){

		DeleteCriticalSection( &m_criticalSection );
	}

public:

   /**
	 *\brief �����ٽ���
	 */
	inline void Enter(){

		EnterCriticalSection( &m_criticalSection );
	}

	/**
	 *\brief �뿪�ٽ���
	 */
	inline void Leave(){

		LeaveCriticalSection( &m_criticalSection );
	}

private:
	CRITICAL_SECTION       m_criticalSection;
};

/**
 *\class LockCriticalSection
 *\brief �ٽ�����
 */
class LockCriticalSection{

public:
	inline LockCriticalSection(CriticalSection* critical):m_ptrCriticalSection(critical){}
	inline ~LockCriticalSection(){}

public:
	inline void Lock(){

		m_ptrCriticalSection->Enter();
	}

	inline void UnLock(){

		m_ptrCriticalSection->Leave();
	}

private:
	CriticalSection*   m_ptrCriticalSection;
};



/**
 *\class Lock
 *\brief ��ģ����
 */
template<class OBJECT, class LOCKER>
class Lock{
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

	inline ~Lock(){

		if (m_bOwnsLock)
		{
			LOCKER(m_ptrObject).UnLock();
		}
	}

private:
	OBJECT*          m_ptrObject;
	bool             m_bOwnsLock;
};

#endif // __TARGET_PLAT_WIN__

#endif