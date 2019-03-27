#pragma once
#include "Memory\MemoryDefine.h"

namespace Core
{
	#define VPURE =0
	#define UID unsigned int
	#define CORE_EXPORTS

	#ifdef CORE_EXPORTS
	#define DLL_EXPORTS __declspec(dllexport)
	#else
	#define DLL_EXPORTS __declspec(dllimport)
	#endif


	// 定义单键提供接口的函数
	#define		SINGLETON_IMPLEMENT( ClassName )			\
	private:											\
	ClassName();								\
	public:												\
	static ClassName* GetInstance()					\
	{													\
		static ClassName instance;							\
		return &instance;									\
	}
												
}