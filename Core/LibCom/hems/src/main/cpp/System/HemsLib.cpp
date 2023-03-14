//
// Created by A16102 on 2023-02-04.
//

#include "HemsLib.h"
#include "HemsLibImpl.h"

CHemsLib* pCHemsLib = nullptr;
CHemsLib &CHemsLib::GetInst() {
    if(pCHemsLib == nullptr){
        pCHemsLib = new CHemsLib;
    }
    return *pCHemsLib;
}

void CHemsLib::ReleaseInst() {
   if(pCHemsLib)
   {
       delete pCHemsLib;
       pCHemsLib = nullptr;
   }
}

CHemsLib::CHemsLib() {
   m_pImpl = new CHemsLibImpl();
}

CHemsLib::~CHemsLib() {
   if(m_pImpl)
   {
       delete m_pImpl;
       m_pImpl = nullptr;
   }
}

//启动系统
bool CHemsLib::Start(){
    return m_pImpl->Start() == 0;
}

//停止系统
bool CHemsLib::Stop(){
    return m_pImpl->Stop() == 0;
}

//开始V2x充电
bool CHemsLib::StartV2xCharge(){
    return m_pImpl->StartV2xCharge() == 0;
}

//停止V2x充电
bool CHemsLib::StopV2xCharge(){
    return m_pImpl->StopV2xCharge() == 0;
}

//开始V2x放电
bool CHemsLib::StartV2xDisCharge(){
    return m_pImpl->StartV2xDisCharge() == 0;
}

//停止V2x放电
bool CHemsLib::StopV2xDisCharge(){
    return m_pImpl->StopV2xDisCharge() == 0;
}