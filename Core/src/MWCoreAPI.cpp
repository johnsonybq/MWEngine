#include "MWCoreAPI.h"
#include "System\System.h"
#include "Log\LogManager.h"
#include "Module\ModuleManager.h"
#include "Reflect\ReflectManager.h"
#include "Serialize\SerializeManager.h"
#include "Test.h"
namespace Core
{
	MWCoreAPI::MWCoreAPI()
	{

	}


	MWCoreAPI::~MWCoreAPI()
	{

	}


	bool	MWCoreAPI::Initialize()
	{
		System::GetInstance()->Initialize();
		LogManager::GetInstance()->Initialize();
		ReflectManager::GetInstance()->Initialize();
		SerializeManger::GetInstance()->Initialize();


		Test::RegisterReflect();
		SerializeClass* pTestClassInfo = SerializeManger::GetInstance()->Class<Test>();
		pTestClassInfo->Member(EAMT_INT, "a", &Test::a);
		pTestClassInfo->Member(EAMT_STRING, "st", &Test::st);
		pTestClassInfo->Member(EAMT_FLOAT, "b", &Test::b);


		MyClass::RegisterReflect();
		SerializeClass* pClassInfo = SerializeManger::GetInstance()->Class<MyClass>();
		pClassInfo->Member(EAMT_INT, "x", &MyClass::x);
		pClassInfo->Member(EAMT_STRING, "str", &MyClass::str);
		pClassInfo->Member(EAMT_BYTEARRAY, "test", &MyClass::test);
		pClassInfo->Member(EAMT_FLOAT, "y", &MyClass::y);
		pClassInfo->Member(EAMT_BOOL, "b", &MyClass::b);




		MyClass*pClass = new MyClass();
		pClass->x = 9999;
		pClass->y = 0.1234f;
		pClass->str = "test001456456546546";
		pClass->test.a = 888;
		pClass->test.b = 9.8765f;
		pClass->test.st = "OK45654654654645654656ughnjcfvbhsdfgsdfdsfasdasdqweqw";

		ByteArray* pBytes = SerializeManger::GetInstance()->ToByteArray(pClass);
		MyClass*pClass1 = (MyClass*)SerializeManger::GetInstance()->FromByteArray(pBytes);
		
		LogManager::GetInstance()->LogToFile("sssssssssssssssssssss");


		return ModuleManager::GetInstance()->Initialize();
	}
}