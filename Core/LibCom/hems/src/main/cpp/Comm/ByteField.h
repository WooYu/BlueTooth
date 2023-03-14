#ifndef AUTEL_89873B06_C04E_4417_BF76_48E05399A9D4_BYTEFIELD_INCLUDE_
#define AUTEL_89873B06_C04E_4417_BF76_48E05399A9D4_BYTEFIELD_INCLUDE_
/*!
 * \file ByteField.h
 * \date 2021/11/23 16:19
 *
 * \author A16102
 * Contact: user@company.com
 *
 * \brief BYTE数组处理类
 *
 * TODO: long description
 *
 * \note
*/
#include <string>
typedef unsigned char BYTE;

class CByteFild
{
public:
	CByteFild();
	CByteFild(int nInitSize);
	CByteFild(const BYTE* pBuff, int nBuffLen);
	CByteFild(const CByteFild& byteFiled);
	~CByteFild();
public:
	CByteFild & operator += (const CByteFild& byteFiled);
	CByteFild& operator = (const CByteFild& byteFiled);
	BYTE& operator[](int nPos);
	operator  BYTE*();
	BYTE GetAt(int nPos) const;
	CByteFild& Append(const CByteFild& byteFiled);
	CByteFild& Append(const BYTE* pBuff, int nBuffLen);
	void Clear();
	int GetLength() const{
		return m_nUsedSize;
	}
	const BYTE* GetBuffer() const { return m_pBuffer; }

    int Copy(const BYTE* pBuff,const int nBuffLen,const int nFromIdx);
protected:
	void AllocBuffer(const int nSize);
protected:
	BYTE * m_pBuffer;//buff指针
	int  m_nBufferSize;//buff大小
	int  m_nUsedSize;//buff实际已使用的大小
};

extern CByteFild  StrToBanary(const std::string& strData);
#endif // AUTEL_89873B06_C04E_4417_BF76_48E05399A9D4_BYTEFIELD_INCLUDE_
