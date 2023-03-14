//
// Created by A16102 on 2023-02-04.
// HEMS native层主类，APP通过jni调用
//

#ifndef HEMS_CHEMSLIB_H
#define HEMS_CHEMSLIB_H

class CHemsLibImpl;
class CHemsLib {
protected:
    CHemsLib();
public:
    //获取CHemsLib全局实列
    static CHemsLib& GetInst();
    ~CHemsLib();
    //释放全局实例
    static void ReleaseInst();
public:
    //启动系统
    bool Start();
    //停止系统
    bool Stop();
public:
    //V2X相关接口

    //开始V2x充电
    bool StartV2xCharge();
    //停止V2x充电
    bool StopV2xCharge();
    //开始V2x放电
    bool StartV2xDisCharge();
    //停止V2x放电
    bool StopV2xDisCharge();
private:
    CHemsLibImpl* m_pImpl;
};


#endif //HEMS_CHEMSLIB_H
