//
// Created by A16102 on 2023-02-06.
// brief: 带锁的数据类基类

#ifndef HEMS_LOCKER_H
#define HEMS_LOCKER_H


#include "../Comm/autel_thread/lock.h"

class CLocker {
public:
    int Lock() {return mtx.Lock();}
    int Unlock() {return mtx.UnLock();}
protected:
    Mutex mtx;
};


#endif //HEMS_LOCKER_H
