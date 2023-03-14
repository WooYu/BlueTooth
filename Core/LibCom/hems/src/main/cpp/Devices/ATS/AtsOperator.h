//
// Created by A16102 on 2023-02-06.
// ATS设备操作封装类

#ifndef HEMS_ATSOPERATOR_H
#define HEMS_ATSOPERATOR_H


#include "../../Comm/ByteField.h"
#include "../../libcom/serial/SerialDev.h"

class SerialPortCore;

class CAtsOperator {
public:
    CAtsOperator();
    ~CAtsOperator();
    //打开设备
    bool Open(const std::string& sPath);
    //关闭设备
    void Close();

    //设备是否已打开
    bool IsOpen() {return m_serialDev.IsOpen();}
public:
    //连接
    int Connect();
    //断开连接
    int DisConnect();
    //获取设备名称
    std::string GetName();
    //获取设备序列号
    std::string GetSn();
    //获取固件版本号
    std::string GetVer();

    //设置周期数据间隔时间
    int SetCycleTime(int nTime);
public://通过ATS控制V2X
    //充电，nPower 功率
    int StartCharge(int nPower);
    //放电，nPower 功率
    int StartDischarge(int nPower);
    //李旺放电，nPower 功率
    int StartDischargeOff(int nPower);
    //停止充放电
    int Stop();
protected:
    int PackAndSend(const int nCmdType,CByteFild* pRev = NULL,const BYTE* pData = NULL,const int nLen = 0);
    //发东命令并获取返回值 0成功 其他失败
    int SendCmd(const CByteFild& byteCmd,CByteFild* pRev = NULL);
private:
    CSerialDev m_serialDev;
    std::string m_sDevName;
    std::string m_sDevSn;
    std::string m_sVer;//固件版本号
};


#endif //HEMS_ATSOPERATOR_H
