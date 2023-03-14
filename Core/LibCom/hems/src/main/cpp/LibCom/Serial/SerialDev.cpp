//
// Created by A16102 on 2023-02-06.
//

#include <unistd.h>
#include "SerialPortCore.h"
#include "SerialDev.h"
#include "../../Comm/CrossPlatDef.h"
#include "../../Comm/PublicFunc.h"


#define HEAD_LEN  5
#define CMD_HEAD  0xA5
#define CMD_CONNECT 0x0101
#define CMD_DISCONNECT 0x0102

CSerialDev::CSerialDev(){
    m_pSerial = nullptr;
    m_bOpen = false;
}

CSerialDev::~CSerialDev(){
    if(m_pSerial)
    {
        delete m_pSerial;
        m_pSerial = nullptr;
    }
}


bool CSerialDev::Open(const std::string& sPath){
    if(m_pSerial == nullptr)
    {
        m_pSerial = new SerialPortCore(sPath.c_str());
    }
    else
    {
        m_pSerial->closePort();
    }
    SerialPortConfig config;
    config.baudrate = 38400;
    config.databits = 8;   // one of 7,8
    config.stopbits = 1;   // one of 1,2
    config.parity = 'n';    // one of N,E,O,S
    m_bOpen = m_pSerial->openSerialPort(config) == 1;
    return m_bOpen;
}

void CSerialDev::Close(){
    if(m_pSerial){
        m_pSerial->closePort();
    }
    m_bOpen = false;
}

int CSerialDev::PackCmd(CByteFild& byteCmd,const int nCmdId,const int nDataLen)
{
    byteCmd[0] = CMD_HEAD;
    IntToBuffer(nCmdId, byteCmd + 1, 2);
    IntToBuffer(nDataLen, byteCmd + 3, 2);
    int checkSum = 0;
    int nCheckPos = nDataLen+5;
    for(int nIdx = 1; nIdx < nCheckPos; nIdx++)
    {
        checkSum += byteCmd[nIdx];
    }
    IntToBuffer(checkSum, byteCmd + nCheckPos, 1);
    byteCmd[nCheckPos + 1] = 0x0D;
    return 0;
}

int CSerialDev::ReceiveData( BYTE* buffer,int cmdType,int iTimeout/* = 1000*/ )
{
    if( !m_pSerial )
    {
        return -1;
    }
    int iRevLength = 0;
    int iHadRevLen = 0;
    bool bHeadChecked = false;
    int nPackLen = REV_DATA_LEN;

    int nBeginTime = GetTickCount();
    while( 1 )
    {

        if( GetTickCount()-nBeginTime > iTimeout )		// 超时
        {
            return -1;
        }
        // 读取数据
        iRevLength = m_pSerial->readData((BYTE*)(buffer+iHadRevLen), nPackLen-iHadRevLen,iTimeout);

        iHadRevLen+=iRevLength;

        if(!bHeadChecked && iHadRevLen >= HEAD_LEN)
        {
            // MY_LOG(0)<<"ReceiveBytes  iCount="<<iCount;
            if(!CheckHead(buffer,cmdType))
            {
                return -1;
            }
            bHeadChecked = true;
            int iLen = GetPackLen(buffer);
            nPackLen = iLen + HEAD_LEN +2;
        }

        if(iHadRevLen >= nPackLen)
        {
            iHadRevLen = nPackLen;
            break;
        }
        usleep(10*1000);

    }
    return iHadRevLen;
}

bool CSerialDev::CheckHead(BYTE* buffer,int cmdType)
{
    bool bCheck = buffer[0] == 0x5A;
    if(bCheck)
    {
        int nType = buffer[1]*256+buffer[2];
        bCheck = nType == cmdType;
    }
    return bCheck;
}

int CSerialDev::GetPackLen(BYTE* buffer)
{
    return buffer[3]*256+buffer[4];
}


int CSerialDev::SendData(const BYTE* buffer, int iLength,int iTimeout)
{
    if( !m_pSerial )
    {
        return -1;
    }
    int iSendLength = 0;

    int nBeginTime = GetTickCount();
    int iNeedSend = iLength;
    BYTE* pData = (BYTE*)buffer;
    while( iNeedSend > 0 )
    {

        if( GetTickCount() - nBeginTime > iTimeout )		// 2秒超时
        {
            //SendMessage( MSG_SERIAL_OUTPUT_DEBUG, (WPARAM)_T( "Send over time." ), 0 );
            return -1;
        }
        // 发送数据
        iSendLength = m_pSerial->writeData( ( BYTE* )pData, iNeedSend );

        pData+=iSendLength;
        iNeedSend -= iSendLength;
        if( iNeedSend == 0 )
        {
            break;
        }
        else
        {
            usleep(50*1000);
        }
    }
    return 1;
}