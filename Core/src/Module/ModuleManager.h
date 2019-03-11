#pragma once
#include <map>
#include <string>
#include "IMiscellaneous.h"
#include "Module\ModuleData.h"
#include "Module\IModuleManager.h"


namespace Core
{
	class ModuleManager : public IModuleManager
	{
	public:

		SINGLETON_IMPLEMENT(ModuleManager);

	public:

		~ModuleManager();

	public:


		// 加载单个模块
		virtual	bool	LoadModule(const char* path);


		// 通过配置加载模块列表
		virtual	bool	LoadAllModules(const char* path);


		// 判断模块是否被加载
		virtual	bool	IsLoadModule(const char* path);


		// 移除单个模块
		virtual	bool	RemoveModule(const char* path);


		// 移除所有模块
		virtual	bool	RemoveAllModules();



	private:

		using  ModuleMap = std::map<std::string, ModuleData*>;
		ModuleMap			m_moduleMap;

	};
}