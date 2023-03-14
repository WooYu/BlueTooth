//
// Created by A16102 on 2023-02-06.
//

#include "AtsOperator.h"
#include "../../Comm/ByteField.h"
#include "../../Comm/PublicFunc.h"


#define CMD_CONNECT    0x0101
#define CMD_DISCONNECT 0x0102
#define CMD_READNAME   0x0201
#define CMD_READSN     0x0301
#define CMD_READVER     0x0501
#define CMD_READVHV     0x0503
#define CMD_V2XSTART     0x0801
#define CMD_V2XSTOP     0x0802
#define CMD_SETCYCTIME     0x0900

CAtsOperator::CAtsOperator(){

}

CAtsOperator::~CAtsOperator(){

}


bool CAtsOperator::Open(const std::string& sPath){
    m_serialDev.Open(sPath);
}

void CAtsOperator::Close(){
    m_sDevName.clear();
    m_sDevSn.clear();
    m_sVer.clear();
    m_serialDev.Close();
}

int CAtsOperator::PackAndSend(const int nCmdType,CByteFild* pRev,const BYTE* pData,const int nLen)
{
    int nDataLen = nLen;
    int nCmdLen = nDataLen + 7;
    CByteFild byteFild(nCmdLen);
    if(pData)
    {
        byteFild.Copy(pData,nLen,5);
    }
    m_serialDev.PackCmd(byteFild,nCmdType,nDataLen);
    return SendCmd(byteFild, pRev);
}

int CAtsOperator::Connect()
{
    return PackAndSend(CMD_CONNECT);
}

int CAtsOperator::DisConnect()
{
    return PackAndSend(CMD_DISCONNECT);
}

std::string CAtsOperator::GetName()
{
    if(m_sDevName.empty())
    {
        CByteFild byteRev;
        int nRet = PackAndSend(CMD_READNAME,&byteRev);
        if(nRet == 0)
        {
            char chName[100];
            memcpy(chName,byteRev.GetBuffer(),byteRev.GetLength());
            chName[byteRev.GetLength()-1] = '\0';
            m_sDevName = chName;
        }
    }
    return m_sDevName;
}


std::string CAtsOperator::GetSn()
{
    if(m_sDevSn.empty())
    {
        CByteFild byteRev;
        int nRet = PackAndSend(CMD_READSN,&byteRev);
        if(nRet == 0)
        {
            char chName[100];
            memcpy(chName,byteRev.GetBuffer(),byteRev.GetLength());
            chName[byteRev.GetLength()-1] = '\0';
            m_sDevSn = chName;
        }
    }
    return m_sDevName;
}

std::string CAtsOperator::GetVer()
{
    if(m_sVer.empty())
    {
        CByteFild byteRev;
        int nRet = PackAndSend(CMD_READVER,&byteRev);
        if(nRet == 0)
        {
            char chName[100];
            memcpy(chName,byteRev.GetBuffer(),byteRev.GetLength());
            chName[byteRev.GetLength()-1] = '\0';
            m_sVer = chName;
        }
    }
    return m_sVer;
}

int CAtsOperator::SetCycleTime(int nTime)
{
    const int nDataLen = 2;
    BYTE byteData[nDataLen];
    IntToBuffer(nTime,byteData,2);
    return PackAndSend(CMD_SETCYCTIME,NULL,byteData,nDataLen);
}

int CAtsOperator::StartCharge(int nPower)
{
    const int nDataLen = 3;
    BYTE byteData[nDataLen] = {0x01, 0x00};
    IntToBuffer(nPower,byteData + 1,2);
    return PackAndSend(CMD_V2XSTART,NULL,byteData,nDataLen);
}

int CAtsOperator::StartDischarge(int nPower)
{
    const int nDataLen = 3;
    BYTE byteData[nDataLen] = {0x02, 0x00};
    IntToBuffer(nPower,byteData + 1,2);
    return PackAndSend(CMD_V2XSTART,NULL,byteData,nDataLen);
}

int CAtsOperator::StartDischargeOff(int nPower)
{
    const int nDataLen = 3;
    BYTE byteData[nDataLen] = {0x03, 0x00};
    IntToBuffer(nPower,byteData + 1,2);
    return PackAndSend(CMD_V2XSTART,NULL,byteData,nDataLen);
}

int CAtsOperator::Stop()
{
    return PackAndSend(CMD_V2XSTOP);
}

int CAtsOperator::SendCmd(const CByteFild& byteCmd,CByteFild* pRev)
{
    int nRet = m_serialDev.SendData(byteCmd.GetBuffer(),byteCmd.GetLength());
    if(nRet > 0)
    {
        int nCmd = byteCmd.GetAt(1) * 256 + byteCmd.GetAt(2);
        BYTE rev[REV_DATA_LEN];
        nRet = m_serialDev.ReceiveData(rev, nCmd);
        if(nRet > 0)
        {
            //结果值
            if(pRev)
            {
                pRev->Append(rev+5,nRet - 5 -2);
            }
            nRet = rev[nRet-3];
        }
        else
        {
            nRet = -1;
        }
    }
    return nRet;
}
