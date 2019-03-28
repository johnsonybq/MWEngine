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


		// ��ʼ��
		virtual	bool						Initialize();


		// ���ļ�����
		template<class T>
		SerializeClass*						Class(int version = 0);



		// ���л���������
		virtual	ByteArray*					ToByteArray(ISerializable* pSerializable, ByteArray* bytes = nullptr);



		// �����л�������
		virtual	ISerializable* 				FromByteArray(ByteArray* bytes);


	private:


		// ���л���Ա����
		void								MemberToByteArray(SerializeMember* pMember, ISerializable* pSerializable, ByteArray* bytes);


		// �����л���Ա����
		void								MemberFromByteArray(SerializeMember* pMember, ISerializable* pSerializable, ByteArray* bytes, int configVersion);


	private:


		using SerializeClassMap = std::map<std::string, SerializeClass*>;
		SerializeClassMap		m_allClass;

	};


	template<class T>
	inline SerializeClass * SerializeManger::Class(int version)
	{
		const char* pClassName = T::__GetClassName__();

		if (pClassName == nullptr)
			return nullptr;

		SerializeClassMap::iterator itor = m_allClass.find(pClassName);

		if (itor != m_allClass.end())
			return itor->second;

		SerializeClass* pClass = MW_New SerializeClass();

		pClass->SetName(pClassName);
		pClass->SetVersion(version);

		m_allClass.insert(std::pair<std::string, SerializeClass*>(pClassName, pClass));

		return pClass;
	}

}