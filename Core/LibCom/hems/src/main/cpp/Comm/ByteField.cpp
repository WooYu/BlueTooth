#include "ByteField.h"
#include <assert.h>
#include "StrHelper.h"
#include "CrossPlatDef.h"
#define INIT_BUFFSIZE 1024

CByteFild::CByteFild()
{
	m_pBuffer = NULL;
	m_nBufferSize = 0;
	m_nUsedSize = 0;
}

CByteFild::~CByteFild()
{
	Clear();
}

CByteFild::CByteFild(int nInitSize)
{
	AllocBuffer(nInitSize);
	m_nUsedSize = nInitSize;
	memset(m_pBuffer, 0, m_nUsedSize);
}

void CByteFild::Clear()
{
	if (m_pBuffer)
	{
		delete[]m_pBuffer;
		m_pBuffer = NULL;
	}
	m_nBufferSize = 0;
	m_nUsedSize = 0;
}

CByteFild::CByteFild(const BYTE* pBuff, int nBuffLen)
{
	AllocBuffer(nBuffLen);
	memcpy(m_pBuffer, pBuff, nBuffLen);
	m_nUsedSize = nBuffLen;
}

CByteFild::CByteFild(const CByteFild& byteFiled)
{
	AllocBuffer(byteFiled.m_nUsedSize);
	memcpy(m_pBuffer, byteFiled.m_pBuffer, byteFiled.m_nUsedSize);
	m_nUsedSize = byteFiled.m_nUsedSize;
}

void CByteFild::AllocBuffer(const int nSize)
{
	int nBufferSize = (nSize / INIT_BUFFSIZE + 1)*INIT_BUFFSIZE;
	m_pBuffer = new BYTE[nBufferSize];
	m_nBufferSize = nBufferSize;
	m_nUsedSize = 0;
}


CByteFild& CByteFild::operator=(const CByteFild& byteFiled)
{
	if (this == &byteFiled)
	{
		return *this;
	}
	else
	{
		m_nUsedSize = 0;
		Append(byteFiled);
	}
	return *this;
}

CByteFild& CByteFild::operator+=(const CByteFild& byteFiled)
{
	return Append(byteFiled.m_pBuffer, byteFiled.m_nUsedSize);
}

BYTE& CByteFild::operator[](int nPos)
{
	assert(nPos >= 0);
	assert(nPos < m_nUsedSize);
	return m_pBuffer[nPos];
}

BYTE CByteFild::GetAt(int nPos) const
{
	assert(nPos >= 0);
	assert(nPos < m_nUsedSize);
	return m_pBuffer[nPos];
}

CByteFild::operator  BYTE*()
{
	return m_pBuffer;
}

CByteFild& CByteFild::Append(const CByteFild& byteFiled)
{
	return Append(byteFiled.m_pBuffer, byteFiled.m_nUsedSize);
}

CByteFild& CByteFild::Append(const BYTE* pBuff, int nBuffLen)
{
	int nAddSize = nBuffLen;
	if (m_nUsedSize + nAddSize <= m_nBufferSize)
	{
		memcpy(m_pBuffer + m_nUsedSize, pBuff, nAddSize);
		m_nUsedSize += nAddSize;
	}
	else
	{
		BYTE* pOld = m_pBuffer;
		int nLen = m_nUsedSize;
		AllocBuffer(m_nUsedSize + nAddSize);
		if (pOld)
		{
			memcpy(m_pBuffer, pOld, nLen);
			delete[]pOld;
		}
		memcpy(m_pBuffer + nLen, pBuff, nAddSize);
		m_nUsedSize = nLen + nAddSize;
	}
	return *this;
}

int CByteFild::Copy(const BYTE* pBuff, const int nBuffLen,const int nFromIdx)
{
	if(nFromIdx < 0 || nFromIdx + nBuffLen > m_nUsedSize)
	{
		return -1;
	}
	memcpy(m_pBuffer + nFromIdx, pBuff, nBuffLen);
	return 0;
}

CByteFild  StrToBanary(const std::string& strData)
{

	std::vector<std::string> vecData;
	PlatPublic::SplitString(strData, ",", vecData);
	const size_t nSize = vecData.size();
	CByteFild binary(nSize);
	int nIndex = 0;
	for (auto& sData : vecData)
	{
		std::string strTemp(sData);
		PlatPublic::Trim(strTemp);
		unsigned int nVal = 0;
		//unsigned char chTemp = 0;
		if (_strnicmp(strTemp.c_str(), "0x", 2) == 0)
		{
#if _WIN32
			sscanf_s(strTemp.substr(2).c_str(), "%x", &nVal);;

#else
			sscanf(strTemp.substr(2).c_str(), "%x", &nVal);
#endif

		}
		else
		{
#if _WIN32
			sscanf_s(strTemp.c_str(), "%x", &nVal);;
#else
			sscanf(strTemp.c_str(), "%x", &nVal);
#endif
			//nVal = atoi(strTemp.c_str());
		}
		binary[nIndex++] = nVal & 0xFF;
	}
	return binary;
}