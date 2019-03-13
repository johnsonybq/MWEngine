#include "ModuleManager.h"
#include "Memory\MemoryDefine.h"

namespace Core
{

	ModuleManager::ModuleManager()
	{

	}

	ModuleManager::~ModuleManager()
	{

	}

	bool ModuleManager::Initialize()
	{
		ModuleManagerEBus::BusConnect(this);
		return true;
	}

	bool ModuleManager::LoadModule(const char * path)
	{
		if(path == nullptr)
			return false;

		ModuleMap::iterator itor = m_moduleMap.begin();
		itor = m_moduleMap.find(path);

		if (itor != m_moduleMap.end())
			return false;

		ModuleData* pModuleData = MW_New ModuleData();
		m_moduleMap.insert(std::make_pair(path, pModuleData));
		
		return pModuleData->LoadModule(path);
	}


	bool ModuleManager::LoadAllModules(const char * path)
	{
		return false;
	}


	bool ModuleManager::IsLoadModule(const char * path)
	{
		return false;
	}


	bool ModuleManager::RemoveModule(const char * path)
	{
		return false;
	}


	bool ModuleManager::RemoveAllModules()
	{
		return false;
	}
}