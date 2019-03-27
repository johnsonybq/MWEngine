#pragma once
#include "Reflect\IReflectFactory.h"
#include "Serialize\ISerializable.h"

namespace Core
{
	class MyClass : public ISerializable
	{
		SERIALIZE_DEFAULTREFLECT_CLASS(Core::MyClass)

	public:
		MyClass();
		~MyClass();

	private:

	};

	MyClass::MyClass()
	{
	}

	MyClass::~MyClass()
	{
	}
}


