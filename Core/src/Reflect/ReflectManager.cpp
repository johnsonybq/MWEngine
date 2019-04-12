#include "Log\ILog.h"
#include "ReflectManager.h"
#include "BaseDataReflectFactory.h"

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
		BaseDataReflectFactory* pBaseFactory = MW_New BaseDataReflectFactory();

		Register("string", pBaseFactory);		Register("std::string", pBaseFactory);
		Register("int16", pBaseFactory);		Register("Core::int16", pBaseFactory);
		Register("vec1", pBaseFactory);			Register("Core::vec1", pBaseFactory);
		Register("vec2", pBaseFactory);			Register("Core::vec2", pBaseFactory);
		Register("vec3", pBaseFactory);			Register("Core::vec3", pBaseFactory);
		Register("vec4", pBaseFactory);			Register("Core::vec4", pBaseFactory);
		Register("mat4", pBaseFactory);			Register("Core::mat4", pBaseFactory);
		Register("mat3", pBaseFactory);			Register("Core::mat3", pBaseFactory);
		Register("mat2", pBaseFactory);			Register("Core::mat2", pBaseFactory);

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