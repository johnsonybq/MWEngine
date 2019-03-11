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


		// ���ص���ģ��
		virtual	bool	LoadModule(const char* path);


		// ͨ�����ü���ģ���б�
		virtual	bool	LoadAllModules(const char* path);


		// �ж�ģ���Ƿ񱻼���
		virtual	bool	IsLoadModule(const char* path);


		// �Ƴ�����ģ��
		virtual	bool	RemoveModule(const char* path);


		// �Ƴ�����ģ��
		virtual	bool	RemoveAllModules();



	private:

		using  ModuleMap = std::map<std::string, ModuleData*>;
		ModuleMap			m_moduleMap;

	};
}