#include "MWCoreAPI.h"
#include "Log\LogManager.h"
#include "Module\ModuleManager.h"


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

		LogManager::GetInstance()->Log("Test  Log %s","asd");
		LogManager::GetInstance()->Warning("Test  Log %s", "hhhh");
		LogManager::GetInstance()->Error("Test  Log %s", "xcxcx");
		LogManager::GetInstance()->Log("Test  Log %s", "iiii");
		return ModuleManager::GetInstance()->Initialize();
	}
}