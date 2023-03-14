/**********************************************************************\
 * run.h
 *
 *  Created on: 2013-7-17
 *      Author: WANG YAN SHUN
 *   Copyright: Autel
 * Description: 声明线程的任务对象
 *
 ***********************************************************************/

#ifndef __RUN_H__
#define __RUN_H__

#include <time.h>
#include"lock.h"


/**
 * @class IRun
 * @brief 任务对象接口
 */
class IRun{
public:
	IRun(){};
	virtual ~IRun(){};

public:
	// 接口声明

	/**
	 * @brief 线程对象执行任务的入口
	 */
    virtual int Run( void* ptrData, unsigned int uParam, int iParam ) = 0;

    /**
     * @brief 用于等待任务结束退出
     */
    virtual void Wait( struct timespec* timeout ) = 0;

	/**
    * @brief 是否循环调用Run
    * 参数： nWaitTime 循环调用的间隔时间，返回值为true时有效
    * 返回值: true 循环调用Run false 执行一次run后线程推出
    */
	virtual bool IsLoop(int& nWaitTime) {return false;};
};

#endif /* __RUN_H__ */
