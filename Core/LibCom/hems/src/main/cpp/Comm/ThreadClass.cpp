//
// Created by A16102 on 2023-02-07.
//

#include "ThreadClass.h"

CThreadClass::CThreadClass()
{

}

CThreadClass::~CThreadClass(void)
{
}

int CThreadClass::Start()
{
    return m_workThread.Start(this);
}

void CThreadClass::Stop() {
    m_workThread.Stop();
}
