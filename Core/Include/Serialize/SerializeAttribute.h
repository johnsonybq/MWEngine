#pragma once
#include <string>

namespace Core
{

	enum ESAttributeType
	{
		ESAT_INVALID =	0,
		ESAT_BYTE,
		ESAT_UNBYTE,
		EAST_BOOL,
		EAST_INT,
		EAST_UNINT,
		EAST_DOUBLE,
		EAST_FLOAT,
		EAST_SHORT,
		EAST_UNSHORT,
		EAST_STRING,
		EAST_U29INT,
		EAST_BYTEARRAY,
		EAST_TOTAL
	};


	struct SerializeAttribute
	{
	public:

		SerializeAttribute()
			:eAttributeType(ESAT_INVALID), attributeName(""), pValue(nullptr)
		{

		}
		
		~SerializeAttribute()
		{

		}

	public:

		// 属性类型
		ESAttributeType			eAttributeType;

		// 属性名
		std::string				attributeName;

		// 默认属性值
		void*					pValue;

	};

}