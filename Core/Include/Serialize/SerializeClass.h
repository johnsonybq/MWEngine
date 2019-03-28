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


		// 设置类名
		void				SetName(const char* name);


		// 获取类名
		const char*			GetName();


		// 设置类版本号
		void				SetVersion(int v);


		// 获取类版本号
		int					GetVersion();


		// 添加成员变量描述
		template<class ClassType, class FieldType>
		void				Member(ESMemberType eType, const char* memberName, FieldType ClassType::* member);


		// 获取成员变量个数
		int					GetMemberCount();


		// 获取成员变量数据
		SerializeMember*	GetMember(int count);


	private:

		std::string				className;					// 类名
		int						version;					// 版本号
		
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