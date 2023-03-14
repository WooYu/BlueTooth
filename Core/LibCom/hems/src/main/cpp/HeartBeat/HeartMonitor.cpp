//
// Created by A16102 on 2023-02-06.
//

#include "HeartMonitor.h"
#include "../DataMgr/DataMgr.h"
#include "../Devices/DevMgr.h"

CHeartMonitor::CHeartMonitor(){

}

CHeartMonitor::~CHeartMonitor(){

}

bool CHeartMonitor::IsLoop(int& nWaitTime){
    //1s执行一次Run
    nWaitTime = 1000;
    return true;
}

int CHeartMonitor::Run(void* ptrData, unsigned int uParam, int iParam){
   return Monitor();
}

int CHeartMonitor::Monitor(){

    if(!CDevMgr::GetInst().GetDevAts().IsOpen())
    {//ats未打开
        return 0;
    }
    CDevMgr::GetInst().GetDevAts().Connect();
}