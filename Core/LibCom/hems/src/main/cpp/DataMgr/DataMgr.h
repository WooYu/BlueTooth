//
// Created by A16102 on 2023-02-04.
// 数据管理类，用于管理各类数据以及数据读取

#ifndef HEMS_CDATAMGR_H
#define HEMS_CDATAMGR_H
#include "SysData.h"
#include "ConfigData.h"
#include "V2XData.h"

class CDataMgr {
protected:
    CDataMgr();
public:
    //获取CDataMgr全局实列
    static CDataMgr& GetInst();
    static void ReleaseInst();
    ~CDataMgr();

public:
    CSysData& GetSysData() {return m_sysData;}
    CV2XData& GetV2xData() {return m_v2xData;}
    CConfigData& GetConfigData() {return m_configData;}
private:
    CSysData m_sysData;
    CV2XData m_v2xData;
    CConfigData m_configData;
};

#endif //HEMS_CDATAMGR_H
