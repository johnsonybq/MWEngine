#pragma once
#include <string>
#include "GLM\glm.hpp"
#include "Reflect\IReflectFactory.h"


namespace Core
{
	class BaseDataReflectFactory : public IReflectFactory
	{
	public:


		BaseDataReflectFactory() {};

		~BaseDataReflectFactory() {};

	public:


		// ´´½¨
		virtual	void*	CreateClass(const char* className)
		{
			if (className == nullptr)
				return nullptr;
			
			std::string name = className;

			if (name == "string" || name == "std::string")
				return MW_New std::string();

			if (name == "int16" || name == "Core::int16")
				return MW_New int16();

			if (name == "vec1" || name == "Core::vec1")
				return MW_New vec1();

			if (name == "vec2" || name == "Core::vec2")
				return MW_New vec2();

			if (name == "vec3" || name == "Core::vec3")
				return MW_New vec3();

			if (name == "mat4" || name == "Core::mat4")
				return MW_New mat4();

			if (name == "mat3" || name == "Core::mat3")
				return MW_New mat3();

			if (name == "mat2" || name == "Core::mat2")
				return MW_New mat2();
			return nullptr;
		}


		// Ïú»Ù
		virtual void	DestoryClass(void* pClass)
		{
			if (pClass != nullptr)
				MW_Delete pClass;
		}
	};
}