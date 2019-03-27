#include "SerializeManager.h"

namespace Core
{

	SerializeManger::SerializeManger()
	{

	}


	SerializeManger::~SerializeManger()
	{

	}

	bool SerializeManger::Initialize()
	{
		return true;
	}


	ByteArray * SerializeManger::ToByteArray(ISerializable * pSerializable, ByteArray * bytes)
	{
		if (pSerializable == nullptr)
			return bytes;

		const char* pClassName = pSerializable->GetSerializeClassName();

		if (pClassName == nullptr)
			return bytes;

		SerializeClassMap::iterator itor = m_allClass.find(pClassName);

		if (itor == m_allClass.end() || itor->second == nullptr)
			return bytes;

		SerializeClass* pClassInfo = itor->second;

		if (bytes == nullptr)
			bytes = MW_New ByteArray;

		if (pClassInfo->GetName() == nullptr)
			pClassInfo->SetName(pClassName);

		// 写入类名
		std::string name = pClassName;
		bytes->writeUTF(name);

		// 写入属性数据



		return nullptr;
	}


	void SerializeManger::FromByteArray(ISerializable * pSerializable, ByteArray * bytes)
	{

	}

}