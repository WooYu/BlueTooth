#pragma once
#include <vector>
#include <string>
#include <wchar.h>
#include <math.h>
using namespace std;

namespace PlatPublic
{
	template<class T> void ToLowerCase(T& src)
	{
		for (unsigned int i = 0; i < src.length(); i++)
		{
			if (src[i] >= 65 && src[i] <= 90)
			{
				src[i] = src[i] + 32;
			}
		}
	}

	template<class T> void ToUpperCase(T& src)
	{
		for (unsigned int i = 0; i < src.length(); i++)
		{
			if (src[i] >= 97 && src[i] <= 122)
			{
				src[i] = src[i] - 32;
			}
		}
	}

	template<class T> void TrimLeft(T& src, const int& ch = 0x00)
	{
		int iLen = src.length();
		for (int i = 0; i < iLen; ++i)
		{
			if (src.at(i) != 0x20 && src.at(i) != 0x09 && src.at(i) != ch)  //空格和TAB字符及指定字符
			{
				src = src.substr(i, iLen - i);
				break;
			}
		}
	}

	template<class T> void TrimRight(T& src, const int& ch = 0x00)
	{
		int iLen = src.length();
		for (int i = iLen - 1; i >= 0; --i)
		{
			if (src.at(i) != 0x20 && src.at(i) != 0x09 && src.at(i) != ch) //空格和TAB字符及指定字符
			{
				src = src.substr(0, i + 1);
				break;
			}
			else
			{
				src = src.substr(0, i);
			}
		}
	}

	template<class T> void Trim(T& src, const int& ch = 0x00)
	{
		TrimLeft(src, ch);
		TrimRight(src, ch);
	}

	template<class T, class T1> void SplitString(const T& sSrc, const T1& sDelimiter, vector<T>& vecDes)
	{
		int pos = 0;
		unsigned int nFindStart = 0;
		bool bSameFlage = true;
		T strContent;
		T strDelimiter = sDelimiter;

		while (pos != -1)
		{
			strContent.clear();
			pos = sSrc.find(strDelimiter, nFindStart);
			if (-1 == pos)
			{
				if (nFindStart < sSrc.length())
				{
					strContent = sSrc.substr(nFindStart);
				}
				else
				{
					break;
				}
			}
			else
			{
				strContent = sSrc.substr(nFindStart, pos - nFindStart);
			}
			nFindStart = pos + strDelimiter.size();
			vecDes.push_back(strContent);
		}
	}

	template<class T, class T1, class T2> T ReplaceString(const T& src, const T1& oldstr, const T2& newstr)
	{
		T  old = oldstr;
		if (old.empty() || src.empty())
		{
			return src;
		}
		T			strTemp = src;
		T           strnew = newstr;
		int			len = old.size();
		int			pos = 0;
		while (strTemp.find(old, pos) != T::npos)
		{
			pos = strTemp.find(old, pos);
			strTemp.replace(pos, len, strnew);
			pos += strnew.size();
		}

		return strTemp;
	}

	template<class T> T TrimString(const T &srcText, const T& sTrimString)
	{
		if (srcText.empty())
		{
			return srcText;
		}
		T		newString = srcText;
		T		strTemp;
		int		pos = 0;
		bool	bFind = true;

		while (bFind)
		{
			strTemp = newString;
			pos = strTemp.find(sTrimString, 0);
			if (0 == pos)
			{
				bFind = true;
				newString = strTemp.substr(sTrimString.length(), strTemp.length() - sTrimString.length());
			}
			else if (0 < pos && pos == strTemp.length() - sTrimString.length())
			{
				bFind = true;
				newString = strTemp.substr(0, strTemp.length() - sTrimString.length());
			}
			else
			{
				bFind = false;
			}
		}
		return newString;
	}

	enum DigitType
	{
		eUint,
		eInt,
		eFloat,
	};

	template<class T> bool IsHexHead(const T& strVal)
	{
		bool bRet = false;
		if (strVal.size() > 2)
		{
			//判断前两个字节是否是0x或0X
			if (strVal[0] == 48 &&
				(strVal[1] == 88 || strVal[1] == 120))
			{
				bRet = true;
			}
		}
		return bRet;
	}

	template<class T> bool IsDigit(const T& ch, const bool bHex)
	{
		if (bHex)
		{
			return (ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 70) || (ch >= 97 && ch <= 102);
		}
		else
		{
			return ch >= 48 && ch <= 57;
		}
	}

	template<class T> bool IsDigitStr(const T& strVal, int iType = eUint)
	{
		bool bIsDigit = true;
		bool bFirstChar = true;
		bool bExistNumber = false;
		bool bExistDot = false;
		T str(strVal);
		Trim(str);
		bool bHexStr = false;
		if (iType == eUint)
		{
			bHexStr = IsHexHead(str);
			if (bHexStr)
			{
				str = str.substr(2);
			}
		}
		for (auto ch : str)
		{
			if (!IsDigit(ch, bHexStr))
			{
				if (ch == 45 && bFirstChar && (iType != eUint))
				{//首位可以是符号位

				}
				else if (ch == 46 && iType == eFloat && bExistNumber && (!bExistDot))
				{//浮点型已前面已存在数字时，可以是小数点
					bExistDot = true;
				}
				else
				{
					bIsDigit = false;
					break;
				}
			}
			else
			{
				bExistNumber = true;
			}
			bFirstChar = false;
		}
		return bIsDigit && bExistNumber;
	}

	template<typename... Args> std::string FormatStr(const char* pFomatStr, Args... args)
	{
		std::string strRet;
		int lenStr = snprintf(nullptr, 0, pFomatStr, args...);
		if (lenStr > 0)
		{
			char* pStr = new char[lenStr+1];
			if (pStr)
			{
				snprintf(pStr, lenStr+1, pFomatStr, args...);
				strRet = pStr;

				delete[] pStr;
				pStr = nullptr;
			}	
		}
		return strRet;
	}
};
