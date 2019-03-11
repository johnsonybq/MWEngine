#pragma once
#include "IMiscellaneous.h"

namespace Core
{
	class Module
	{
	public:

		Module() = default;

		virtual ~Module() {};

	private:

	};
}


#   define INITIALIZATION_MODULE_CLASS(MODULE_NAME, MODULE_CLASSNAME)                                \                                                           \
    extern "C" DLL_EXPORTS Core::Module * CreateModuleClass() { return aznew MODULE_CLASSNAME; } \
    extern "C" DLL_EXPORTS void DestroyModuleClass(AZ::Module * module) { delete module; }
