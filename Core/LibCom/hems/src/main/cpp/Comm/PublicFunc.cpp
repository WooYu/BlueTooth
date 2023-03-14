#include "PublicFunc.h"
#include "StrHelper.h"
#include "CrossPlatDef.h"

#ifdef _WIN32
#define _WIN32_WINNT 0x0400
#include <Windows.h>
#else
#include <time.h>
#endif
#include <math.h>

int StrToInt(const std::string& strData)
{
	int nRet = 0;
	std::string strTemp(strData);
	PlatPublic::Trim(strTemp);
	if (_strnicmp(strTemp.c_str(), "0x", 2) == 0)
	{
		//sscanf_s(strTemp.substr(2).c_str(), "%x", &nRet);
#if _WIN32
		sscanf_s(strTemp.substr(2).c_str(), "%x", &nRet);;
#else
		sscanf(strTemp.substr(2).c_str(), "%x", &nRet);
#endif
	}
	else
	{
		nRet = atoi(strTemp.c_str());
	}
	return nRet;
}

void IntToBuffer(const unsigned int nValue, unsigned char* pBuffer, const int nSize)
{
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		int nOffset = (nSize - nIndex -1) * 8;
		pBuffer[nIndex] = (nValue >> nOffset) & 0xFF;
	}
}

unsigned int ConvertVerToInt(const std::string& strVer)
{
	int nRet = 0;
	if (!strVer.empty())
	{
		string strVerData = strVer.substr(1);
		vector<string> vtVer;
		PlatPublic::SplitString(strVerData, ".", vtVer);
		if (vtVer.size() <= 3)
		{
			for (int nIdx = 0; nIdx < vtVer.size(); nIdx++)
			{
				int nVerNum = atoi(vtVer[nIdx].c_str());
				nRet += (nVerNum*(pow(1000.0f, 2 - nIdx)));
			}
		}

// 		strVerData = PlatPublic::ReplaceString(strVerData, ".", "");
// 		nRet = atoi(strVerData.c_str());
	}

	return nRet;
}

int  CompareVer(const std::string& strV1, const std::string& strV2)
{
	int nVer1 = ConvertVerToInt(strV1);
	int nVer2 = ConvertVerToInt(strV2);
	return nVer1 - nVer2;
}

bool IsVerStr(const std::string& strVer)
{
	bool bRet = false;
	std::string str = strVer;
	PlatPublic::Trim(str);
	if (str.empty())
	{
		return bRet;
	}
	if (str.substr(0, 1) == "v" || str.substr(0, 1) == "V")
	{
		str = str.substr(1);
		std::vector<std::string> vtStr;
		PlatPublic::SplitString(str, ".", vtStr);
		if (vtStr.size() > 1 && vtStr.size() < 4)
		{
			bRet = true;
			for (auto& sItem : vtStr)
			{
				if (!PlatPublic::IsDigitStr(sItem, PlatPublic::eUint))
				{
					bRet = false;
					break;
				}
				unsigned int nVerNum = atoi(sItem.c_str());
				if (nVerNum > 999)
				{
					bRet = false;
					break;
				}
			}
		}
	}
	return bRet;
}

int GetAllFiles(const std::string& strPath, std::list<std::string>& lsFiles, const std::string& strExt)
{
#ifdef _WIN32
	lsFiles.clear();
	WIN32_FIND_DATAA findInfo;
	std::string sDestPath = strPath + "\\*." + strExt;
	HANDLE hFind = FindFirstFileA(sDestPath.c_str(), &findInfo);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return -1;
	}

	do {
		string sFileName = findInfo.cFileName;
		lsFiles.push_back(strPath + sFileName);
	} while (FindNextFileA(hFind, &findInfo));

	FindClose(hFind);
#endif
	return 0;
}




std::string GetFileName(const std::string& sFilePath)
{
	int iPos1 = sFilePath.rfind("/");
	int iPos2 = sFilePath.rfind("\\");
	int iPos = iPos1 > iPos2 ? iPos1 : iPos2;

	string sFileName;
	if (string::npos != iPos)
	{
		sFileName = sFilePath.substr(iPos + 1, sFilePath.size());
	}
	else
	{
		sFileName = sFilePath;
	}

	size_t nExtPos = sFileName.rfind(".");
	if (string::npos != iPos)
	{
		sFileName = sFileName.substr(0, nExtPos);
	}
	return sFileName;
}

#ifndef _WIN32
unsigned long GetTickCount()
{
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC,&ts);
	return ts.tv_nsec*1000 + ts.tv_nsec / 1000000;
}
#endif