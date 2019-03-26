#include "Log\ILog.h"
#include "ReflectManager.h"


namespace Core
{


	ReflectManager::ReflectManager()
	{

	}


	ReflectManager::~ReflectManager()
	{

	}

	bool ReflectManager::Initialize()
	{
		ReflectionEBus::BusConnect(this);
		return true;
	}

	bool ReflectManager::Register(const char * className, IReflectFactory * factory)
	{
		if(className == nullptr || factory == nullptr)
			return false;

		ReflectMap::iterator itor = m_reflectMap.find(className);

		if (itor != m_reflectMap.end())
		{
			if (itor->second != factory)
			{
				LogEBus::Broadcast(&Core::ILog::Error, "ReflectManager Register Error className Repat Register! className is  ", className);
				return false;
			}

			return true;
		}

		m_reflectMap.insert(std::pair<std::string, IReflectFactory*>(className, factory));

		return true;
	}

	IReflectFactory * ReflectManager::GetReflectFactory(const char * className)
	{
		if (className == nullptr)
			return nullptr;

		ReflectMap::iterator itor = m_reflectMap.find(className);

		if (itor == m_reflectMap.end())
			return nullptr;

		return itor->second;
	}

	bool ReflectManager::UnRegister(const char * className)
	{
		if (className == nullptr)
			return false;

		ReflectMap::iterator itor = m_reflectMap.find(className);

		if (itor == m_reflectMap.end())
			return false;

		if (itor->second != nullptr)
			MW_Delete(itor->second);

		m_reflectMap.erase(itor);
		return false;
	}

}