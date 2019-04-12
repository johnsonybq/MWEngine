#pragma once
#include "MWCore.h"

namespace Core
{
	class Module
	{
	public:

		Module() = default;

		virtual ~Module() {};

		virtual bool	Initialize() { return false; }

	};
}


#   define INITIALIZATION_MODULE_CLASS(MODULE_CLASSNAME)                                \                                                           \
    extern "C" extern DLL_EXPORTS  Core::Module * CreateModuleClass() { return MW_New MODULE_CLASSNAME; }  \
    extern "C" extern DLL_EXPORTS  void DestroyModuleClass(Core::Module * module) { MW_Delete module; } 
