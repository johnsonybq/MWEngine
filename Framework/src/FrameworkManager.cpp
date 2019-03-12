#include "FrameworkManager.h"
#include "Entity\EntitySystem.h"
//#include "Asset\AssetSystem.h"

namespace Framework
{
	FrameworkManager::FrameworkManager()
	{

	}

	FrameworkManager::~FrameworkManager()
	{
		
	}


	void FrameworkManager::Initialization()
	{
		//AssetSystem::GetInstance()->Initialization();
		EntitySystem::GetInstance()->Initialization();
	}


	/*IAssetSystem * FrameworkManager::GetAssetSystem()
	{
		return AssetSystem::GetInstance();
	}*/


	IEntitySystem * FrameworkManager::GetEntitySystem()
	{
		return EntitySystem::GetInstance();
	}


	void FrameworkManager::Destory()
	{

	}
}