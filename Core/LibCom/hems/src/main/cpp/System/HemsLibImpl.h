//
// Created by A16102 on 2023-02-04.
// CHemsLib实现类
//

#ifndef HEMS_CHEMSLIMPL_H
#define HEMS_CHEMSLIMPL_H


class CHemsLibImpl {
public:
    CHemsLibImpl();
    ~CHemsLibImpl();
public:
    //启动系统
    int Start();
    //停止系统
    int Stop();
public:
    //V2X相关接口

    //开始V2x充电
    int StartV2xCharge();
    //停止V2x充电
    int StopV2xCharge();
    //开始V2x放电
    int StartV2xDisCharge();
    //停止V2x放电
    int StopV2xDisCharge();

};


#endif //HEMS_CHEMSLIMPL_H
