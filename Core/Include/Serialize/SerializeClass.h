#pragma once
#include <vector>
#include <string>
#include "SerializeAttribute.h"
#include "Reflect\IReflectFactory.h"


namespace Core
{
	struct SerializeClass
	{
	public:

		SerializeClass();

		~SerializeClass();

	public:

		std::string				className;
		IReflectFactory*		pFactory;
		
		using AttributeList = std::vector<SerializeAttribute*>;
		AttributeList			attributes;

	};

}