//
// Created by A16543 on 2023/2/7.
//

#ifndef HEMS_APPSERIALOPERATOR_H
#define HEMS_APPSERIALOPERATOR_H

#include "../../Comm/ByteField.h"

class SerialPortCore;

class CAppSerialOperator{

public:
    CAppSerialOperator();
    ~CAppSerialOperator();
    bool openDevice();
    void closeDevice();
    bool isOpenDevice();

//    int sendData(const BYTE* pData = NULL,const int nLen = 0);
//    int sendData(const CByteFild& byteCmd);
//    int readData(BYTE *data, int size,long timeout);
private:
    SerialPortCore* m_pSerial;

};

#endif //HEMS_APPSERIALOPERATOR_H
