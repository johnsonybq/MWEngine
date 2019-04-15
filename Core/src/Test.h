#pragma once
#include <string>
#include "Reflect\IReflectFactory.h"
#include "Serialize\ISerializable.h"
#include "Module\Module.h"

namespace Core
{
	

	class Test : public ISerializable, public Module
	{
		SERIALIZE_DEFAULTREFLECT_CLASS(Core::Test)

	public:
		Test()
		{
			st = "mmmmmmm";
		}
		~Test()
		{

		}

	public:

		int  a;
		std::string st;
		float b;


	};
	INITIALIZATION_MODULE_CLASS(Test);

	class MyClass : public ISerializable
	{
		SERIALIZE_DEFAULTREFLECT_CLASS(Core::MyClass)

	public:
		MyClass();
		~MyClass();

	public:

		int  x;
		std::string str;
		Test test;
		float y;
		bool b;

	};

	MyClass::MyClass()
	{
		x = 100;
		y = 200.0f;
		str = "123456";
		b = true;
	}

	MyClass::~MyClass()
	{
	}



}


