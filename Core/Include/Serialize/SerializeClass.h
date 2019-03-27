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
		void				SetName(const char* name, int version = 0);


		// ��ȡ����
		const char*			GetName();


		// ��ӳ�Ա��������
		void				Member(ESMemberType eType, const char* memberName, int offset);


		// ��ȡ��Ա��������
		int					GetMemberCount();


		// ��ȡ��Ա��������
		SerializeMember*	GetMember(int count);


	private:

		std::string				className;					// ����
		int						version;					// �汾��
		IReflectFactory*		pFactory;
		
		using MemberList = std::vector<SerializeMember*>;
		MemberList			members;

	};

}