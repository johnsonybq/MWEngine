/************************************************************************/
/*
文件名: ByteArray.h
描  述: 二进制数组
日  期: 16/04/2018
作  者: MibuWolf
版	本: 1.0
备  注:
*/
/************************************************************************/
#pragma once

#include <vector>
#include <string>
#include <WTypes.h>
#include "AMF3TypeCode.h"
#include "ByteStream.h"

namespace Core
{
	static const std::string BIG_ENDIAN = "BIG";
	static const std::string LITTLE_ENDIAN = "LITTLE";

	class ByteArray
	{
	public:

		ByteArray(const std::string& strEndian = BIG_ENDIAN);
		ByteArray(const BYTE* pByte, int iLength, const std::string& strEndian = BIG_ENDIAN);
		virtual ~ByteArray(){}

	public:
		
		static std::string MBtoUTF8(const std::string& strMB);

		void Initialize();

	public:
		void write(const BYTE* pBytes, int iLength);
		void writeByte(int __byte);
		unsigned int readUnsignedByte();
		void writeUnsingnedByte(BYTE __ubyte);
		bool readBoolean();
		void writeBoolean(bool __boolean);
		int readInt();
		void writeInt(int __int);
		unsigned int readUnsignedInt();
		void writeUnsignedInt(unsigned int __uint);
		double readDouble();
		void writeDouble(double __double);
		float readFloat();
		void writeFloat(float __float);
		short readShort();
		void writeShort(short __short);
		unsigned short readUnsignedShort();
		void writeUnsignedShort(unsigned short __ushort);
		
	public:
		int readPos() {return _memoryStream.readPos();}
		int length()const { return _memoryStream.getLength(); }
		const ByteVec& getByteVec()const { return _memoryStream.getByteVec(); }
		const unsigned char* getBuffPtr()const { return _memoryStream.getBytePtr(); }
		ByteStream& getByteStream() { return _memoryStream; }

	public:
		void writeUTF( std::string& str );
		void _writeStreamBytesEndian(const ByteStream& byteBuff);
		void _writeStreamBytesLittleEndian(const ByteStream& byteBuff);
		void _writeStreamBytesBigEndian(const ByteStream& byteBuff);
		void writeDoubleStreamBigEngian(double dValue);
		void writeU29Int(int iValue);
		void writeAMF3Null();
		int readU29Int();
		double readDoubleStreamLittleEndian();
		void _readStreamBytesEndian(int length, ByteVec& byteVec);
		void _readStreamBytesBigEndian(int length, ByteVec& byteVec);
		void _readStreamBytesLittleEndian(int length, ByteVec& byteVec);
		void readUTF( std::string& str);
		int readIntStreamBytesBigEndian();
		void _readStreamBytes(int length,  ByteVec& byteVec);

	private:
		ByteStream _memoryStream;
		std::string m_sEndian;
		
	};
}