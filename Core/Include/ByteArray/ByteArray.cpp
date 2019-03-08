#include "ByteArray.h"
#include "IVector.h"

namespace Framework
{
	ByteArray::ByteArray( const BYTE* pByte, int iLength, const std::string& strEndian /*= LITTLE_ENDIAN*/ )
		: m_sEndian(strEndian)
	{
		_memoryStream.write(pByte, iLength);
	}

	ByteArray::ByteArray( const std::string& strEndian /*= LITTLE_ENDIAN*/ )
		:m_sEndian(strEndian)
	{

	}

	void ByteArray::writeU29Int( int iValue )
	{
		//Sign contraction - the high order bit of the resulting value must match every bit removed from the number
		//Clear 3 bits 
		iValue &= 0x1fffffff;
		if (iValue < 0x80)
		{
			_memoryStream.write<BYTE>((BYTE)iValue);
		}
		else if (iValue < 0x4000)
		{
			_memoryStream.write<BYTE>((BYTE)(iValue >> 7 & 0x7f | 0x80));
			_memoryStream.write<BYTE>((BYTE)(iValue & 0x7f));
		}
		else
		{
			if (iValue < 0x200000)
			{
				_memoryStream.write<BYTE>((BYTE)(iValue >> 14 & 0x7f | 0x80));
				_memoryStream.write<BYTE>((BYTE)(iValue >> 7 & 0x7f | 0x80));
				_memoryStream.write<BYTE>((BYTE)(iValue & 0x7f));
			}
			else
			{
				_memoryStream.write<BYTE>((BYTE)(iValue >> 22 & 0x7f | 0x80));
				_memoryStream.write<BYTE>((BYTE)(iValue >> 15 & 0x7f | 0x80));
				_memoryStream.write<BYTE>((BYTE)(iValue >> 8 & 0x7f | 0x80));
				_memoryStream.write<BYTE>((BYTE)(iValue & 0xff));
			}
		}
	}

	void ByteArray::writeByte( int __byte )
	{
		if (__byte < 0)
		{
			__byte += 256;
		}
		BYTE byteValue = (BYTE)__byte;
		_memoryStream.write<BYTE>(byteValue);
	}

	double ByteArray::readDouble()
	{
		ByteVec bytes;
		// Read the next 4 bytes, shift and add
		_readStreamBytesEndian(sizeof(double), bytes);
		ByteStream bStream;
		bStream.write(&bytes[0], sizeof(double));
		return bStream.read<double>();
	}


	void ByteArray::writeDouble( double __double )
	{
		ByteStream byteStream;
		byteStream.write<double>(__double);
		_writeStreamBytesEndian(byteStream);
	}

	void ByteArray::_writeStreamBytesLittleEndian(const ByteStream& byteBuff )
	{
		if (byteBuff.getBytePtr() != NULL)
		{
			_memoryStream.write(byteBuff.getBytePtr(), byteBuff.getLength());
		}
	}

	void ByteArray::_writeStreamBytesBigEndian( const ByteStream& byteBuff )
	{
		const ByteVec& btVec = byteBuff.getByteVec();

		for (int i = ((int)btVec.size() - 1); i >= 0; i--)
		{
			_memoryStream.write(btVec[i]);
		}
	}

	void ByteArray::writeDoubleStreamBigEngian( double dValue )
	{
		ByteStream byteStream;
		byteStream.write<double>(dValue);
		_writeStreamBytesBigEndian(byteStream);
	}

	void ByteArray::_writeStreamBytesEndian( const ByteStream& byteBuff )
	{
		if (m_sEndian == LITTLE_ENDIAN)
		{
			_writeStreamBytesLittleEndian(byteBuff);
		}
		else
		{
			_writeStreamBytesBigEndian(byteBuff);
		}
	}
	
	void ByteArray::writeUTF( std::string& str )
	{
		int len = MultiByteToWideChar( CP_ACP, 0, str.c_str(), -1, 0, 0 );
		wchar_t* pWideChar = new wchar_t[len];
		MultiByteToWideChar( CP_ACP, 0, str.c_str(), -1, pWideChar, len );
		len = WideCharToMultiByte( CP_UTF8, 0, pWideChar, -1, 0, 0, NULL, NULL );
		char* pUTF8 = new char[len];
		WideCharToMultiByte( CP_UTF8, 0, pWideChar, -1, pUTF8, len, NULL, NULL );
		writeU29Int(len - 1);
		_memoryStream.write( (BYTE*)pUTF8, len - 1 );
		delete []pWideChar;
		delete []pUTF8;
	}



	void ByteArray::readUTF( std::string& str)
	{
		int len = readU29Int();
		_memoryStream.read(str, len);
	}


	void ByteArray::writeAMF3Null()
	{
		//Write the null code (0x1) to the output stream.
		writeByte(ATC_Null);
	}


	int ByteArray::readU29Int()
	{
		int acc = _memoryStream.read<BYTE>();
		int tmp;
		if (acc < 128)
		{
			return acc;
		}
		else
		{
			acc = (acc & 0x7f) << 7;
			tmp = _memoryStream.read<BYTE>();
			if (tmp < 128)
			{
				acc = acc | tmp;
			}
			else
			{
				acc = (acc | tmp & 0x7f) << 7;
				tmp = _memoryStream.read<BYTE>();
				if (tmp < 128)
				{
					acc = acc | tmp;
				}
				else
				{
					acc = (acc | tmp & 0x7f) << 8;
					tmp = _memoryStream.read<BYTE>();
					acc = acc | tmp;
				}
			}
		}
		//To sign extend a value from some number of bits to a greater number of bits just copy the sign bit into all the additional bits in the new format.
		//convert/sign extend the 29bit two's complement number to 32 bit
		int mask = 1 << 28; // mask
		int r = -(acc & mask) | acc;
		return r;

		//The following variation is not portable, but on architectures that employ an 
		//arithmetic right-shift, maintaining the sign, it should be fast. 
		//s = 32 - 29;
		//r = (x << s) >> s;
	}
	

	double ByteArray::readDoubleStreamLittleEndian()
	{
		ByteVec tmpVec;
		_readStreamBytesBigEndian(sizeof(double), tmpVec);
		ByteStream tmpStream;
		tmpStream.write(&tmpVec[0], sizeof(double));
		return tmpStream.read<double>();
	}

	void ByteArray::_readStreamBytesBigEndian( int ilength, ByteVec& byteVec )
	{
		ByteVec tmpVec;
		_readStreamBytesLittleEndian(ilength, tmpVec);
	
		for (int i = ilength - 1; i >= 0; i--)
		{
			byteVec.push_back(tmpVec[i]);
		}
	}

	void ByteArray::_readStreamBytesLittleEndian( int ilength, ByteVec& byteVec )
	{
		for (int i = 0; i < ilength; i++)
		{
			 byteVec.push_back(_memoryStream.read<BYTE>());
		}
	}


	int ByteArray::readIntStreamBytesBigEndian()
	{
		ByteVec byteVec;
		_readStreamBytesBigEndian(sizeof(int), byteVec);
		int iValue = (int)((byteVec[3] << 24) | (byteVec[2] << 16) | (byteVec[1] << 8) | byteVec[0]);
		return iValue;
	}

	void ByteArray::write( const BYTE* pBytes, int iLength )
	{
		_memoryStream.write(pBytes, iLength);
	}

	unsigned int ByteArray::readUnsignedByte()
	{
		return (unsigned int)_memoryStream.read<BYTE>();
	}

	void ByteArray::writeUnsingnedByte( BYTE __ubyte )
	{
		_memoryStream.write<BYTE>(__ubyte);
	}

	bool ByteArray::readBoolean()
	{
		return _memoryStream.read<BYTE>() == 1;
	}

	void ByteArray::writeBoolean( bool __boolean )
	{
		_memoryStream.write<BYTE>(__boolean ? ((BYTE)1) : ((BYTE)0));
	}


	void ByteArray::writeInt( int __int )
	{
		ByteStream byteStream;
		byteStream.write<int>(__int);
		_writeStreamBytesEndian(byteStream);
	}

	int ByteArray::readInt()
	{
		ByteVec bytes;
		// Read the next 4 bytes, shift and add
		_readStreamBytesEndian(sizeof(int), bytes);
		int iValue = (int)((bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0]);
		return iValue;
	}

	unsigned int ByteArray::readUnsignedInt()
	{
		ByteVec bytes;
		// Read the next 4 bytes, shift and add
		_readStreamBytesEndian(sizeof(unsigned int), bytes);
		ByteStream bStream;
		bStream.write(&bytes[0], sizeof(unsigned int));
		return bStream.read<unsigned int>();
	}

	void ByteArray::_readStreamBytesEndian( int length, ByteVec& byteVec )
	{
		if (m_sEndian == LITTLE_ENDIAN)
		{
			_readStreamBytesLittleEndian(length, byteVec); ;
		}
		else
		{
			_readStreamBytesBigEndian(length, byteVec);
		}
	}

	void ByteArray::writeUnsignedInt( unsigned int __uint )
	{
		ByteVec bVec(4,0);
		bVec[3] = (BYTE)(0xFF & (__uint >> 24));
		bVec[2] = (BYTE)(0xFF & (__uint >> 16));
		bVec[1] = (BYTE)(0xFF & (__uint >> 8));
		bVec[0] = (BYTE)(0xFF & (__uint >> 0));
		ByteStream bStream;
		bStream.write(&bVec[0], 4);
		_writeStreamBytesEndian(bStream);
		//this._memoryStream.Write(bytes, 0, bytes.Length);
	}

	void ByteArray::_readStreamBytes( int length, ByteVec& byteVec )
	{
		byteVec.clear();
		byteVec.resize(length, 0);
		_memoryStream.read(&byteVec[0], length);
	}

	float ByteArray::readFloat()
	{
		ByteVec bytes;
		// Read the next 4 bytes, shift and add
		_readStreamBytesEndian(sizeof(float), bytes);
		ByteStream bStream;
		bStream.write(&bytes[0], sizeof(float));
		return bStream.read<float>();
	}

	void ByteArray::writeFloat( float __float )
	{
		ByteStream byteStream;
		byteStream.write<float>(__float);
		_writeStreamBytesEndian(byteStream);
	}

	short ByteArray::readShort()
	{
		ByteVec bytes;
		// Read the next 4 bytes, shift and add
		_readStreamBytesEndian(sizeof(short), bytes);
		return (short)((bytes[1] << 8) | bytes[0]);
	}

	void ByteArray::writeShort( short __short )
	{
		ByteStream byteStream;
		byteStream.write<short>(__short);
		_writeStreamBytesEndian(byteStream);
	}

	unsigned short ByteArray::readUnsignedShort()
	{
		ByteVec bytes;
		// Read the next 4 bytes, shift and add
		_readStreamBytesEndian(sizeof(unsigned short), bytes);
		//byte[] bytes = this._readStreamBytes(2);
		return (unsigned short)(((bytes[1] & 0xff) << 8) | (bytes[0] & 0xff));
	}

	void ByteArray::writeUnsignedShort( unsigned short __ushort )
	{
		ByteStream byteStream;
		byteStream.write<unsigned short>(__ushort);
		_writeStreamBytesEndian(byteStream);
	}

	std::string ByteArray::MBtoUTF8( const std::string& strMB )
	{
		int iLen=::MultiByteToWideChar(CP_ACP,0, strMB.c_str(),-1,NULL,0);

		//To Unicode
		if(0 == iLen)
		{
			return "";
		}

		std::vector<wchar_t> unicodeBuf(iLen);
		::MultiByteToWideChar(CP_ACP,0, strMB.c_str(),-1,&unicodeBuf[0],iLen);

		//To Utf8
		int iUtfLen = ::WideCharToMultiByte(CP_UTF8, 0, &unicodeBuf[0], -1, NULL, 0, NULL, NULL);

		if (iUtfLen == 0) 
		{
			return "";
		}

		std::vector<char> utf8Vec(iUtfLen);
		::WideCharToMultiByte(CP_UTF8, 0, &unicodeBuf[0], -1, &utf8Vec[0], iUtfLen, NULL, NULL);
		return &utf8Vec[0];

	}
	void ByteArray::Initialize()
	{
		_memoryStream.Initialize();
	}
}