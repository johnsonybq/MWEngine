#pragma once
#include <string>
#include <Windows.h>
#include "Module\Module.h"


namespace Core
{
	// ÿ���̳�Module��ģ�鶼���е���������
	using CreateModuleClassFunction = Module * (*)();
	const char CreateModuleClassFunctionName[] = "CreateModuleClass";

	using DestroyModuleClassFunction = void(*)(Module* module);
	const char DestroyModuleClassFunctionName[] = "DestroyModuleClass";

	class ModuleData
	{
	public:

		ModuleData();

		~ModuleData();

	public:


		// ����ģ��
		bool				LoadModule(const char* pPath);


		// �ͷ�ģ��
		bool				DestoryModule();


	private:


		// ��ȡdll�еĺ�����ַ
		template<typename Function>
		Function GetFunction(const char* functionName) const;


	private:

		std::string			m_modulePath;
		Module*				m_pModule;
		HMODULE				m_handle;

	};

	ModuleData::ModuleData()
		:m_modulePath(""), m_pModule(nullptr), m_handle(NULL)
	{

	}

	ModuleData::~ModuleData()
	{

	}


	inline bool ModuleData::LoadModule(const char * pPath)
	{
		if(pPath == nullptr)
			return false;

		m_modulePath = pPath;
		m_handle = LoadLibrary(pPath);

		if (m_handle == NULL)
			return false;

		CreateModuleClassFunction createModuleFuc = GetFunction<CreateModuleClassFunction>(CreateModuleClassFunctionName);

		if (createModuleFuc == nullptr)
			return false;

		m_pModule = createModuleFuc();

		return true;
	}


	inline bool ModuleData::DestoryModule()
	{
		if (m_handle == NULL)
			return false;

		DestroyModuleClassFunction destroyModuleFuc = GetFunction<DestroyModuleClassFunction>(DestroyModuleClassFunctionName);

		if (destroyModuleFuc != nullptr && m_pModule != nullptr)
			destroyModuleFuc(m_pModule);

		FreeLibrary(m_handle);

		m_handle = NULL;
	}


	template<typename Function>
	inline Function ModuleData::GetFunction(const char * functionName) const
	{
		if (m_handle != NULL && functionName != nullptr)
		{
			return reinterpret_cast<Function>(::GetProcAddress(m_handle, functionName));
		}
		else
		{
			return nullptr;
		}
	}

}