//
// Created by A16102 on 2023-02-04.
//

#include "HemsLibImpl.h"
#include "DevMgr.h"

CHemsLibImpl::CHemsLibImpl() {

}

CHemsLibImpl::~CHemsLibImpl() {

}


//启动系统
int CHemsLibImpl::Start(){
    //启动设备检查
    CDevMgr::GetInst().Start();
    //启动心跳发送和检测

    //启动实时数据读取

    //启动数据监测和资源调度

    return 0;
}

//停止系统
int CHemsLibImpl::Stop(){
    return 0;
}

//开始V2x充电
int CHemsLibImpl::StartV2xCharge(){

}

//停止V2x充电
int CHemsLibImpl::StopV2xCharge(){

}

//开始V2x放电
int CHemsLibImpl::StartV2xDisCharge(){

}

//停止V2x放电
int CHemsLibImpl::StopV2xDisCharge(){

}