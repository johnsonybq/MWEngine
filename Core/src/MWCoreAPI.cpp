#include "MWCoreAPI.h"
#include "System\System.h"
#include "Log\LogManager.h"
#include "Module\ModuleManager.h"
#include "Reflect\ReflectManager.h"

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

		LogManager::GetInstance()->LogToFile("sssssssssssssssssssss");
		return ModuleManager::GetInstance()->Initialize();
	}
}