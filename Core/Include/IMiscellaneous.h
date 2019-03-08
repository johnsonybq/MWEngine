#pragma once


namespace Core
{
	#define PURE =0

	#define FRAMEWORK_EXPORTS_LIB

	#ifdef FRAMEWORK_EXPORTS_LIB
	#define FRAMEWORK_EXPORTS __declspec(dllexport)
	#else
	#define FRAMEWORK_EXPORTS __declspec(dllimport)
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