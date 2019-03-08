#include "ByteStream.h"
#include "ByteArray.h"

namespace Framework
{
	bool ByteStream::write( const std::string& strValue )
	{
		return write((const BYTE*)strValue.c_str(), (int)strValue.length());
	}

	void ByteStream::Initialize()
	{
		m_iReadPos = m_iWritePos = 0;
		m_ByteVec.clear();
	}

	bool ByteStream::write( const BYTE* pValue, int iLength )
	{
		if (NULL == pValue || iLength <= 0)
		{
			return false;
		}

		int iOldLength = getLength();
		m_ByteVec.resize(iOldLength + iLength, 0);
		memcpy_s(&m_ByteVec[0] + iOldLength, iLength, pValue, iLength);
		m_iWritePos += iLength;
		return true;
	}

	bool ByteStream::write( const ByteArray& byteArrayValue )
	{
		int iLength = byteArrayValue.length(); 
		return write(byteArrayValue.getBuffPtr(), iLength);
	}

	bool ByteStream::write( const ByteStream& byteStream )
	{
		if (byteStream.getBytePtr() == NULL || byteStream.getLength() == 0)
		{
			return false;
		}
		return write(byteStream.getBytePtr(), byteStream.getLength());
	}

	void ByteStream::read( BYTE* pReadByte, int iLength )
	{
		if (m_iReadPos + iLength > getLength())
		{
			assert(false);
		}
		memcpy(pReadByte, &m_ByteVec[m_iReadPos], iLength);
		m_iReadPos += iLength;
	}

	void ByteStream::read( ByteArray& byteArrayValue, int iLength)
	{
		//int iLength = read<int>();
		if (m_iReadPos + iLength > getLength())
		{
			assert(false);
		}

		if (iLength > 0)
		{
			byteArrayValue.getByteStream().write(readPtr(), iLength);
		}
		m_iReadPos += iLength;
	}

	void ByteStream::read( ByteStream& byteStream, int iLength)
	{
		if (m_iReadPos + iLength > getLength())
		{
			assert(false);
		}

		if (iLength > 0)
		{
			byteStream.write(readPtr(), iLength);
		}
		m_iReadPos += iLength;
	}

	void ByteStream::read( std::string& strValue, int iLength )
	{
		strValue.clear();
		for (int i = 0; i < iLength; i++)
		{
			char c = read<char>();
			strValue += c;
		}
	}

	void ByteStream::reset()
	{
		m_iWritePos = 0;
		m_iReadPos = 0;
		ByteVec tmpVec;
		tmpVec.swap(m_ByteVec);//对象析构，内存才被释放
	}

	const BYTE* ByteStream::getBytePtr() const
	{
		if (isEmpty())
		{
			return NULL;
		}

		return &m_ByteVec[0];
	}

	void ByteStream::clone( const ByteStream& tStream )
	{
		write(tStream);
		m_iReadPos = 0;
		m_iWritePos = tStream.m_iWritePos;
	}

	const BYTE* ByteStream::readPtr()
	{
		if (getLength())
		{
			return &m_ByteVec[m_iReadPos];
		}
		return NULL;
	}

}