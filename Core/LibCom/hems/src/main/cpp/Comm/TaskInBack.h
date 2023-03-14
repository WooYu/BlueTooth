#ifndef AUTEL_E8A765DB_4675_4CFC_875D_D7045457DD4A__WORKTHREAD__INCLUDED_
#define AUTEL_E8A765DB_4675_4CFC_875D_D7045457DD4A__WORKTHREAD__INCLUDED_

#include "autel_thread/run.h"
#include <string>
#include <list>
#include <memory>
#ifdef WIN32
#include "win_lock.inl.hpp"
#include <thread>
#else
#include "autel_thread/lock.h"
#include "autel_thread/thread.h"
#endif
using namespace std;

typedef struct STR_TASKINFO
{
	int nTaskId;//task
	int nTaskType;
	std::string strParam;//参数
	void*   ptrParam;//参数，用于复杂参数

	STR_TASKINFO()
	{
		nTaskId = -1;
		ptrParam = NULL;
	}
}stTaskInfo;

class ITaskProcess
{
public:
	ITaskProcess() { }
	~ITaskProcess() {}
	virtual int ProcessTask(const stTaskInfo& task) {return 0;};
public:
	//volatile bool m_bReqNet;//
};

class CTaskInBack : public IRun
{

public:
	CTaskInBack();
	virtual ~CTaskInBack();

	void Init(ITaskProcess* pTaskProcess);
	void AddTask(const stTaskInfo& task);
protected:
	int PopTask(stTaskInfo& task);
	void DoInBackground();

	void ProcessTask(const stTaskInfo& task);
protected:
	//Imolement IRun
	virtual int Run(void* ptrData, unsigned int uParam, int iParam);
	virtual void Wait(struct timespec* timeout) {};
private:
	Mutex             m_mtxWorkTask;
	Event             m_evtWorkTask;
	std::list<stTaskInfo>  m_lsWorkTask;


#ifdef _WIN32
	std::shared_ptr<std::thread>     m_workThread;
#else
	Thread  m_workThread;
#endif
	ITaskProcess* m_pProcess;
	
	volatile bool m_bIsRun;
};
#endif // !defined(AUTEL_E8A765DB_4675_4CFC_875D_D7045457DD4A__WORKTHREAD__INCLUDED_)
