//
// Created by A16102 on 2023-02-06.
//

#ifndef HEMS_SERIALDEV_H
#define HEMS_SERIALDEV_H

#include <string>
#include "../../Comm/ByteField.h"
#define REV_DATA_LEN 2048
class SerialPortCore;

class CSerialDev {
public:
    CSerialDev();
    ~CSerialDev();
    //打开设备
    bool Open(const std::string& sPath);
    //关闭设备
    void Close();

    bool IsOpen() {return m_bOpen;}
public:
    //接受数据
    int ReceiveData( BYTE* buffer,int cmdType,int iTimeout = 1000 );
    //打包数据
    int PackCmd(CByteFild& byteCmd,const int nCmdId,const int nDataLen);

    //发送数据
    int SendData(const BYTE* buffer, int iLength,int iTimeout = 1000 );

protected:
    //检查头和命令ID
    bool CheckHead(BYTE* buffer,int cmdType);
    //获取包数据长度
    int GetPackLen(BYTE* buffer);

private:
    SerialPortCore* m_pSerial;
    bool m_bOpen;//设备是否已打开
};


#endif //HEMS_SERIALDEV_H
