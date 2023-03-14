//
// Created by A16102 on 2023-02-04.
// 系统数据类

#ifndef HEMS_CSYSDATA_H
#define HEMS_CSYSDATA_H

#include "LocKer.h"

class CSysData : public CLocker{
public:
    bool bAtsConnect;//下位机连接状态
    bool bV2xConnect;//V2X连接状态

public:
    CSysData(){
        Init();
    }
    void Init(){
        bAtsConnect = false;
        bV2xConnect = false;
    }
};


#endif //HEMS_CSYSDATA_H
