#pragma once

namespace Core
{
	#define UID unsigned int
	#define CORE_EXPORTS

	#ifdef CORE_EXPORTS
	#define DLL_EXPORTS __declspec(dllexport)
	#else
	#define DLL_EXPORTS __declspec(dllimport)
	#endif

	#define VPURE = 0;

	// ���嵥���ṩ�ӿڵĺ���
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