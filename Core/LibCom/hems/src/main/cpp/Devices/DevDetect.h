#ifndef AUTEL_0ED1B19E_54A9_4241_8F35_1800F55D75ED__DEVICESCAN__INCLUDED_
#define AUTEL_0ED1B19E_54A9_4241_8F35_1800F55D75ED__DEVICESCAN__INCLUDED_

//设备检测类，检测系统中各个设备是否有接入
#include <map>
#include <string>
#include "Comm/ThreadClass.h"

using namespace std;

class IDetectNotify
{
public:
    enum DevType{
        eDev_ATS,//Ats
    };
public:
    IDetectNotify() {};
    virtual ~ IDetectNotify() {};

    //通知设备信息
    //参数： devType 设备类型，见DevType定义
    //      nStatus 设备状态 1已连接 0未连接
    //      sPath   设备路径
    virtual int NotifyDevStatus(const int devType,const int nStatus,const std::string& sPath) = 0;

};

class CDevDetect : public CThreadClass{
public:
    CDevDetect();
     ~CDevDetect(void);

     void Init(IDetectNotify*  m_pNotify);
protected:
    //Imolement IRun
    virtual int Run(void* ptrData, unsigned int uParam, int iParam);
    virtual bool IsLoop(int& nWaitTime);
protected:
    //扫描设备
    int ScanDev(std::map<std::string,int>& mapDevs);
    //检测设备
    bool DetectDev(const std::map<std::string,int>& mapDevs);
private:
    IDetectNotify* m_pNotify;
};


#endif // !defined(ODX_0ED1B19E_54A9_4241_8F35_1800F55D75ED__DEVICESCAN__INCLUDED_)

