#pragma once
#include <vector>
#include <string>
#include "SerializeMember.h"
#include "Reflect\IReflectFactory.h"


namespace Core
{
	struct SerializeClass
	{
	public:

		SerializeClass();

		~SerializeClass();

	public:


		// ��������
		void				SetName(const char* name);


		// ��ȡ����
		const char*			GetName();


		// ������汾��
		void				SetVersion(int v);


		// ��ȡ��汾��
		int					GetVersion();


		// ��ӳ�Ա��������
		template<class ClassType, class FieldType>
		void				Member(ESMemberType eType, const char* memberName, FieldType ClassType::* member);


		// ��ȡ��Ա��������
		int					GetMemberCount();


		// ��ȡ��Ա��������
		SerializeMember*	GetMember(int count);


	private:

		std::string				className;					// ����
		int						version;					// �汾��
		
		using MemberList = std::vector<SerializeMember*>;
		MemberList			members;

	};




	template<class ClassType, class FieldType>
	inline void SerializeClass::Member(ESMemberType eType, const char * memberName, FieldType ClassType::* member)
	{
		if (memberName == nullptr)
			return;

		int count = members.size();
		SerializeMember* smember = nullptr;

		for (int i = 0; i < count; ++i)
		{
			smember = members[i];

			if (smember != nullptr && smember->eMemberType == eType)
			{
				LogEBus::Broadcast(&ILog::Error, "Repeat addition Member for Class , Class Name is %s, Member Name is %s", className.c_str(), memberName);
				return;
			}
		}

		smember = nullptr;

		smember = MW_New SerializeMember;
		smember->eMemberType = eType;
		smember->memberName = memberName;
		smember->offset = reinterpret_cast<size_t>(&(reinterpret_cast<ClassType const volatile*>(0)->*member));
		members.push_back(smember);
	}

}