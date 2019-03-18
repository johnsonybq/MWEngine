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

		LogManager::GetInstance()->Initialize();
		LogManager::GetInstance()->ToFile("sssssssssssssssssssss");
		return ModuleManager::GetInstance()->Initialize();
	}
}