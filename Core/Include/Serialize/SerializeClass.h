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
		void			SetName(const char* name);


		// 获取类名
		const char*		GetName();


		// 添加属性描述
		void			Member(ESMemberType eType, const char* memberName);


	private:

		std::string				className;
		IReflectFactory*		pFactory;
		
		using MemberList = std::vector<SerializeMember*>;
		MemberList			members;

	};

}