#pragma once

#include <vector>
#include <string>
#include <WTypes.h>
#include <assert.h>

namespace Core
{
	typedef std::vector<BYTE> ByteVec;
	class ByteArray;

	class ByteStream
	{
	public:
		ByteStream():m_iReadPos(0),m_iWritePos(0){}
		ByteStream(const ByteStream& rStream) { clone(rStream); }
		virtual ~ByteStream(){}

	public:

		void Initialize();

		bool write(const BYTE* pValue, int iLength);
		bool write(const std::string& strValue);
		bool write(const ByteArray& byteArrayValue);
		bool write(const ByteStream& byteStream);

		void read(std::string& strValue, int iLength);
		void read( ByteArray& byteArrayValue, int iLength);
		void read( ByteStream& byteStream, int iLength);
		void read(BYTE* pReadByte, int iLength);
		const BYTE* readPtr();
		//BYTE* writePtr() {return &m_ByteVec[m_iWritePos];}
		void reset();

		const ByteVec& getByteVec()const {return m_ByteVec;}
	
		const BYTE* getBytePtr() const;

		int getLength()const{return (int)m_ByteVec.size();}

		bool isEmpty()const {return m_ByteVec.empty();}
		void clone(const ByteStream& tStream);

	public:

		ByteStream& operator =(const ByteStream& rStream)
		{
			clone(rStream);
			return *this;
		}

	public:
		template<typename T> T read()
		{
			T tValue = read<T>(m_iReadPos);
			m_iReadPos += sizeof(T);
			return tValue;
		}

		template<typename T> T read(size_t iPos)
		{
			if (iPos + sizeof(T) > getLength())
			{
				assert(false);
			}

			T tValue = *((const T*)&m_ByteVec[iPos]);
			return tValue;
		}

		template<typename T> void read(std::vector<T>& tVec)
		{
			int iValueCount = read<int>();
			while (iValueCount--)
			{
				T tValue = read<T>();
				tVec.push_back(tValue);
			}
		}

		template <typename T> void write(const T& value)
		{
			write((const BYTE*)&value, sizeof(value));
		}

		template <typename T> void write(const std::vector<T>& tVec)
		{
			int iValueCount = int(tVec.size());

			write<int>(iValueCount);
			
			for (int index = 0; index < iValueCount; index++)
			{
				write<T>(tVec[index]);
			}
		}

	public:
		int readPos()const {return m_iReadPos;}
		int writePos()const {return m_iWritePos;}
		int readPos(int iPos) { m_iReadPos = iPos; return m_iReadPos;}
		int writePos(int iPos) {m_iWritePos = iPos; return m_iWritePos;}
		
	private:
		int m_iWritePos;
		int m_iReadPos;
		ByteVec m_ByteVec;
	};
}