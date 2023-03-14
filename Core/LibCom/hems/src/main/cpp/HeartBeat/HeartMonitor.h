//
// Created by A16102 on 2023-02-06.
// 心跳监测

#ifndef HEMS_HEARTMONITOR_H
#define HEMS_HEARTMONITOR_H


#include "../Comm/ThreadClass.h"

class CHeartMonitor : public CThreadClass
{
public:
    CHeartMonitor();
    ~CHeartMonitor(void);

protected:
    //Imolement IRun
    virtual int Run(void* ptrData, unsigned int uParam, int iParam);
    virtual bool IsLoop(int& nWaitTime);
protected:
    //检测心跳
    int Monitor();


};


#endif //HEMS_HEARTMONITOR_H
