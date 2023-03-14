//
// Created by A16102 on 2023-02-04.
//

#include "DataMgr.h"
using namespace std;

CDataMgr* pDataMgr = NULL;

CDataMgr &CDataMgr::GetInst() {
    if(pDataMgr == NULL){
        pDataMgr = new CDataMgr;
    }
    return *pDataMgr;
}

void CDataMgr::ReleaseInst() {
    if(pDataMgr)
    {
        delete pDataMgr;
        pDataMgr = NULL;
    }
}

CDataMgr::CDataMgr()
{

}

CDataMgr::~CDataMgr()
{

}