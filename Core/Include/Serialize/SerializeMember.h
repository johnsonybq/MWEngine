#pragma once
#include <string>

namespace Core
{

	enum ESMemberType
	{
		ESMT_INVALID =	0,
		ESMT_BYTE,
		ESMT_UNBYTE,
		EAMT_BOOL,
		EAMT_INT,
		EAMT_UNINT,
		EAMT_DOUBLE,
		EAMT_FLOAT,
		EAMT_SHORT,
		EAMT_UNSHORT,
		EAMT_STRING,
		EAMT_U29INT,
		EAMT_BYTEARRAY,
		EAMT_TOTAL
	};


	struct SerializeMember
	{
	public:

		SerializeMember()
			:eMemberType(ESMT_INVALID), memberName("")
		{

		}
		
		~SerializeMember()
		{

		}

	public:

		// 属性类型
		ESMemberType			eMemberType;

		// 属性名
		std::string				memberName;

	};

}