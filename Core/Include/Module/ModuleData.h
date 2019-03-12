#pragma once
#include <string>
#include <Windows.h>
#include "Module\Module.h"


namespace Core
{

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

}