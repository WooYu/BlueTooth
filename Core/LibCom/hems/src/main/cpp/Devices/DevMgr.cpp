//
// Created by A16102 on 2023-02-04.
//

#include "DevMgr.h"
#include "DataMgr/DataMgr.h"

CDevMgr* pDevMgr = nullptr;

CDevMgr &CDevMgr::GetInst() {
    if(pDevMgr == nullptr){
        pDevMgr = new CDevMgr;
    }
    return *pDevMgr;
}

void CDevMgr::ReleaseInst() {
    if(pDevMgr)
    {
        delete pDevMgr;
        pDevMgr = nullptr;
    }
}

CDevMgr::CDevMgr()
{

}

CDevMgr::~CDevMgr()
{

}

int CDevMgr::Start()
{
    return m_devDetect.Start();
}

int CDevMgr::Stop()
{
    m_devDetect.Stop();
    return 0;
}

int CDevMgr::NotifyDevStatus(const int devType,const int nStatus,const std::string& sPath){
    switch(devType)
    {
        case IDetectNotify::eDev_ATS:
            OnAtsStatus(nStatus,sPath);
            break;
        default:
            break;
    }
    return 0;
}

void CDevMgr::OnAtsStatus(const int nStatus,const std::string& sPath){
    bool bAtsConnect = nStatus == 1;
    if(CDataMgr::GetInst().GetSysData().bAtsConnect != bAtsConnect)
    {
        CDataMgr::GetInst().GetSysData().bAtsConnect = bAtsConnect;
        if(bAtsConnect)
        {//打开设备
            m_devAts.Open(sPath);
        }
        else
        {//关闭设备
            m_devAts.Close();
        }
    }
}
