#include "Module\ModuleData.h"


namespace Core
{
	// 每个继承Module的模块都会有的两个方法
	using CreateModuleClassFunction = Module * (*)();
	const char CreateModuleClassFunctionName[] = "CreateModuleClass";

	using DestroyModuleClassFunction = void(*)(Module* module);
	const char DestroyModuleClassFunctionName[] = "DestroyModuleClass";


	ModuleData::ModuleData()
		:m_modulePath(""), m_pModule(nullptr), m_handle(NULL)
	{

	}

	ModuleData::~ModuleData()
	{

	}


	bool ModuleData::LoadModule(const char * pPath)
	{
		if (pPath == nullptr)
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


	bool ModuleData::DestoryModule()
	{
		if (m_handle == NULL)
			return false;

		DestroyModuleClassFunction destroyModuleFuc = GetFunction<DestroyModuleClassFunction>(DestroyModuleClassFunctionName);

		if (destroyModuleFuc != nullptr && m_pModule != nullptr)
			destroyModuleFuc(m_pModule);

		FreeLibrary(m_handle);

		m_handle = NULL;

		return true;
	}


	template<typename Function>
	inline Function ModuleData::GetFunction(const char * functionName) const
	{
		if (m_handle != NULL && functionName != nullptr)
		{
			void* pFuc = ::GetProcAddress(m_handle, functionName);
			return reinterpret_cast<Function>(::GetProcAddress(m_handle, functionName));
		}
		else
		{
			return nullptr;
		}
	}

}