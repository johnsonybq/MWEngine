#include "MWCoreAPI.h"
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
		return ModuleManager::GetInstance()->Initialize();
	}
}