#ifndef AUTEL_8B70C478_8FE9_404A_82F5_8EA3B215B4EC_GLOBALOUBLIC_INCLUDE_
#define AUTEL_8B70C478_8FE9_404A_82F5_8EA3B215B4EC_GLOBALOUBLIC_INCLUDE_
/*!
 * \file GlobalFunc.h
 * \date 2021/11/22 17:34
 *
 * \author A16102
 * Contact: user@company.com
 *
 * \brief 全局函数定义
 *
 * TODO: long description
 *
 * \note
*/
#include <string>
#include <list>
//字符串转int，0x开头按16进制转换
extern int StrToInt(const std::string& strData);
//Int转Buff
extern void IntToBuffer(const unsigned int nValue, unsigned char* pBuffer,const int nSize = 4);

//将版本号转为int
// v1.00转换为100
// v1.00.01转换为10001
extern unsigned int ConvertVerToInt(const std::string& strVer);

//比较版本大小
// 返回值>0  strV1>strV2
//  返回值=0 strV1=strV2
// 返回值<0  strV1<strV2
extern int  CompareVer(const std::string& strV1, const std::string& strV2);

//是否是版本号字符串
extern bool IsVerStr(const std::string& strVer);

//获取指定目录下的指定扩展名的文件列表,不对文件夹展开
extern int GetAllFiles(const std::string& strPath, std::list<std::string>& lsFiles, const std::string& strExt);

//通过路径获取文件名
extern std::string GetFileName(const std::string& sFilePath);

#ifndef _WIN32
unsigned long GetTickCount();
#endif
#endif // AUTEL_8B70C478_8FE9_404A_82F5_8EA3B215B4EC_GLOBALOUBLIC_INCLUDE_
