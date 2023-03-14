#include "TaskInBack.h"
//#include <functional>
//#include "public.h"
#include "../JniInterface/LogPrint.h"

//CTaskInBack* CTaskInBack::m_pIns = NULL;
CTaskInBack::CTaskInBack()
{
	m_pProcess = NULL;
	//m_bReqNet = false;
	m_bIsRun = false;
}


CTaskInBack::~CTaskInBack()
{
	m_bIsRun = false;
	m_evtWorkTask.Set();
	{
		Lock<Mutex, LockMutex> lock(&m_mtxWorkTask);
		m_lsWorkTask.clear();
	}
#ifdef _WIN32
	//m_workThread.reset(new std::thread(std::bind(&CTaskInBack::DoInBackground, this)));
#else
	m_workThread.Stop();
#endif
}

void CTaskInBack::Init(ITaskProcess* pTaskProcess)
{
	m_pProcess = pTaskProcess;
	LOGI("CTaskInBack::Init %d", m_bIsRun);
	if (!m_bIsRun)
	{
		m_bIsRun = true;

#ifdef _WIN32
		m_workThread.reset(new std::thread(std::bind(&CTaskInBack::DoInBackground, this)));
#else
		m_workThread.Start(this);
#endif
	}

}


void CTaskInBack::DoInBackground()
{
	while (m_bIsRun)
	{
		stTaskInfo taskInfo;
		int nRet = PopTask(taskInfo);
		if (nRet == 0)
		{
			ProcessTask(taskInfo);
		}
		else if (nRet == 1)
		{
//			Sleep(1000);
		}
		else
		{
			m_evtWorkTask.Wait();
		}
	}
}

int CTaskInBack::Run(void* ptrData, unsigned int uParam, int iParam)
{
	DoInBackground();
	return 0;
}

void CTaskInBack::AddTask(const stTaskInfo& task)
{
	LOGI("add AddTask %d", m_bIsRun);
	bool bAdd = true;
	Lock<Mutex, LockMutex> lock(&m_mtxWorkTask);
	m_lsWorkTask.push_back(task);
	m_evtWorkTask.Set();
}

int CTaskInBack::PopTask(stTaskInfo& task)
{
	int nRet = -1;
	{
		Lock<Mutex, LockMutex> lock(&m_mtxWorkTask);
		
		if (!m_lsWorkTask.empty())
		{
			task = m_lsWorkTask.front();
			nRet = 0;
			m_lsWorkTask.pop_front();
		}
		LOGI("poptask %d  %d", nRet, task.nTaskType);
	}
	return nRet;
}

void CTaskInBack::ProcessTask(const stTaskInfo& task)
{
	if (m_pProcess)
	{
		m_pProcess->ProcessTask(task);
	}
}