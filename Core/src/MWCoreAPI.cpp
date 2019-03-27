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

		MyClass*pClass = new MyClass();

		MyClass::RegisterReflect();
		const char* pName = pClass->GetSerializeClassName();

		SerializeClass* pClassInfo = SerializeManger::GetInstance()->Class<MyClass>();
		
		LogManager::GetInstance()->LogToFile("sssssssssssssssssssss");


		return ModuleManager::GetInstance()->Initialize();
	}
}