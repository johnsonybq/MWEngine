#pragma once
#include <map>
#include <string>
#include "Serialize\ISerialize.h"



namespace Core
{
	class SerializeManger : public ISerialize
	{
	public:

		SINGLETON_IMPLEMENT(SerializeManger);

		~SerializeManger();


	public:


		// 初始化
		virtual	bool						Initialize();


		// 类文件描述
		template<class T>
		SerializeClass*						Class();



		// 序列化到二级制
		virtual	ByteArray*					ToByteArray(ISerializable* pSerializable, ByteArray* bytes = nullptr);



		// 反序列化二进制
		virtual	void						FromByteArray(ISerializable* pSerializable, ByteArray* bytes);


	private:


		using SerializeClassMap = std::map<std::string, SerializeClass*>;
		SerializeClassMap		m_allClass;

	};


	template<class T>
	inline SerializeClass * SerializeManger::Class()
	{
		const char* pClassName = T::__GetClassName__();

		if (pClassName == nullptr)
			return nullptr;

		SerializeClassMap::iterator itor = m_allClass.find(pClassName);

		if (itor != m_allClass.end())
			return itor->second;

		SerializeClass* pClass = MW_New SerializeClass();
		pClass->SetName(pClassName);

		m_allClass.insert(std::pair<std::string, SerializeClass*>(pClassName, pClass));

		return pClass;
	}

}