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
		void				SetName(const char* name, int version = 0);


		// 获取类名
		const char*			GetName();


		// 添加成员变量描述
		void				Member(ESMemberType eType, const char* memberName, int offset);


		// 获取成员变量个数
		int					GetMemberCount();


		// 获取成员变量数据
		SerializeMember*	GetMember(int count);


	private:

		std::string				className;					// 类名
		int						version;					// 版本号
		IReflectFactory*		pFactory;
		
		using MemberList = std::vector<SerializeMember*>;
		MemberList			members;

	};

}