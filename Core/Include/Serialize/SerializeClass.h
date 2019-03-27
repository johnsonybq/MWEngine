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
		void			SetName(const char* name);


		// ��ȡ����
		const char*		GetName();


		// �����������
		void			Member(ESMemberType eType, const char* memberName);


	private:

		std::string				className;
		IReflectFactory*		pFactory;
		
		using MemberList = std::vector<SerializeMember*>;
		MemberList			members;

	};

}