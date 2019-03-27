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
		return nullptr;
	}


	void SerializeManger::FromByteArray(ISerializable * pSerializable, ByteArray * bytes)
	{

	}

}