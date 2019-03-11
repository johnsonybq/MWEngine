#include "CoreManager.h"
#include "Module\ModuleManager.h"

namespace Core
{
	CoreManager::CoreManager()
	{

	}

	CoreManager::~CoreManager()
	{
		
	}


	void CoreManager::Initialization()
	{

	}

	IModuleManager * CoreManager::GetModuleManager()
	{
		return ModuleManager::GetInstance();
	}


	void CoreManager::Destory()
	{

	}
}