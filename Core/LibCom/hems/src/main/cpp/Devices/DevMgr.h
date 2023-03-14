//
// Created by A16102 on 2023-02-04.
// 设备管理类，负责设备检测，提供设备操作对象

#ifndef HEMS_DEVMGR_H
#define HEMS_DEVMGR_H


#include "DevDetect.h"
#include "ATS/AtsOperator.h"

class CDevMgr : public IDetectNotify{
protected:
    CDevMgr();
public:
    //获取CDataMgr全局实列
    static CDevMgr& GetInst();
    static void ReleaseInst();
    ~CDevMgr();

    //启动设备管理模块
    int Start();
    //停止
    int Stop();

    //获取ats操作对象
    CAtsOperator& GetDevAts() {return m_devAts;}

protected:
    //implement IDetectNotify
    virtual int NotifyDevStatus(const int devType,const int nStatus,const std::string& sPath);
protected:
    void OnAtsStatus(const int nStatus,const std::string& sPath);
private:
    CDevDetect m_devDetect;
    CAtsOperator m_devAts;
};


#endif //HEMS_DEVMGR_H
