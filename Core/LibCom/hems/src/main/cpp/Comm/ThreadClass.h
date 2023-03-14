//
// Created by A16102 on 2023-02-07.
// 线程类基类，需要创建工作线程的类可继承此类
#ifndef HEMS_THREADCLASS_H
#define HEMS_THREADCLASS_H


#include "autel_thread/run.h"
#include "autel_thread/thread.h"

class CThreadClass : public IRun{

public:
    CThreadClass();
    ~CThreadClass(void);

public:
    //启动检测
    int Start();
    void Stop();
protected:
    //Imolement IRun
    virtual void Wait(struct timespec* timeout) {};

private:
    Thread  m_workThread;
};


#endif //HEMS_THREADCLASS_H
