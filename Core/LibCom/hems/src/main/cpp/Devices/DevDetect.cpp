
#include "DevDetect.h"
#include "libusb.h"
#include "Comm/CrossPlatDef.h"
#include "DataMgr/DataMgr.h"
#include "../Ext/includes/libusb.h"
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <iostream>
#include <dirent.h>
#include <unistd.h>

//DEVID定义 PID_VID
#define DEVID_ATS "5740_048E"

libusb_context *context = NULL;

CDevDetect::CDevDetect()
{
    m_pNotify = NULL;
    libusb_init(&context);
}

CDevDetect::~CDevDetect(void)
{
}

void Init(IDetectNotify*  m_pNotify){
    m_pNotify = m_pNotify;
}

bool CDevDetect::IsLoop(int& nWaitTime){
    nWaitTime = 1000;
    return true;
}

int CDevDetect::Run(void* ptrData, unsigned int uParam, int iParam)
{
    std::map<std::string,int> mapDev;
    ScanDev(mapDev);
    DetectDev(mapDev);
   // usleep(100*1000);
}

int CDevDetect::ScanDev(std::map<std::string,int>& mapDev)
{

    libusb_device **list = NULL;
    int rc = 0;
    ssize_t count = 0;
    count = libusb_get_device_list(context, &list);
    if(count > 0){
        for (size_t idx = 0; idx < count; ++idx) {
            libusb_device *device = list[idx];
            libusb_device_descriptor desc = {0};
            int nPortNumber = (int)libusb_get_port_number(device);

            rc = libusb_get_device_descriptor(device, &desc);
            char chTemp[20];
            sprintf_s(chTemp,20,"%04X_%04X",desc.idProduct,desc.idVendor);
            mapDev[std::string(chTemp)] = nPortNumber;
        }
        libusb_free_device_list(list,1);
    }
    return 0;
}

bool CDevDetect::DetectDev(const std::map<std::string,int>& mapDev)
{

    if(!m_pNotify)
    {
        return false;
    }
    auto iteFind = mapDev.find(DEVID_ATS);
    int nStatus = 0;
    std::string strPath;
    if(iteFind != mapDev.end())
    {
        nStatus = 1;
        char chTemp[20];
        sprintf_s(chTemp,20,"/dev/tty_USB%d",iteFind->second);
        strPath = chTemp;
    }
    m_pNotify->NotifyDevStatus(IDetectNotify::eDev_ATS,nStatus,strPath);
    return true;
}



