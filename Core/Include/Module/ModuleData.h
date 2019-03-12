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


		// 加载模块
		bool				LoadModule(const char* pPath);


		// 释放模块
		bool				DestoryModule();


	private:


		// 获取dll中的函数地址
		template<typename Function>
		Function GetFunction(const char* functionName) const;


	private:

		std::string			m_modulePath;
		Module*				m_pModule;
		HMODULE				m_handle;

	};

}