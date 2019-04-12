#pragma once
#include <map>
#include <string>
#include "Reflect\IReflectManager.h"



namespace Core
{
	class ReflectManager : public IReflectManager
	{
	public:

		SINGLETON_IMPLEMENT(ReflectManager);

	public:


		~ReflectManager();


	public:


		// 初始化
		virtual	bool				Initialize();


		// 注册
		virtual	bool				Register(const char* className, IReflectFactory* factory);


		// 获取反射工厂
		virtual	IReflectFactory*	GetReflectFactory(const char* className);


		// 解注册
		virtual	bool				UnRegister(const char* className);



	private:

		using ReflectMap = std::map<std::string, IReflectFactory*>;
		ReflectMap			m_reflectMap;
	};
}