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


		// ��ʼ��
		virtual	bool				Initialize();


		// ע��
		virtual	bool				Register(const char* className, IReflectFactory* factory);


		// ��ȡ���乤��
		virtual	IReflectFactory*	GetReflectFactory(const char* className);


		// ��ע��
		virtual	bool				UnRegister(const char* className);



	private:

		using ReflectMap = std::map<std::string, IReflectFactory*>;
		ReflectMap			m_reflectMap;
	};
}