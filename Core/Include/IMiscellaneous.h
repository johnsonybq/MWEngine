#pragma once
#include "Memory\IMemMan.h"
#include "Memory\IMemPort.h"
#include "Memory\MemManager.h"

namespace Core
{

	#define PURE	=0;
	#define CORE_EXPORTS

	#ifdef CORE_EXPORTS
	#define DLL_EXPORTS __declspec(dllexport)
	#else
	#define DLL_EXPORTS __declspec(dllimport)
	#endif



	//--------------------------------------------------------------------
	// 函数名: GetMemoryManager
	// 功  能: 获取内存管理器
	//--------------------------------------------------------------------
	extern DLL_EXPORTS IMemoryManager* GetMemoryManager(void);

	template <class Type>
	__forceinline Type* MW_New_Impl(size_t nCount, Type* pRef, const void* szFile = "", size_t nLine = 0)
	{
		Struct_Allocate<Type > tmp(GetMemoryManager());
		return tmp(nCount, szFile, nLine);
	}

	template <class Type>
	__forceinline void MW_Delete_Impl(Type*& pointer, const char* szFile = "", size_t nLine = 0)
	{
		Struct_Deallocate<Type > tmp(GetMemoryManager());
		tmp(pointer, szFile, nLine);
		pointer = NULL;
	}

	#ifdef _DEBUG

	#define MW_New(Type, nCount) \
			MW_New_Impl(nCount, (Type*)NULL, __FILE__, __LINE__)

	#define MW_Delete(p) \
			MW_Delete_Impl(p, __FILE__, __LINE__)

	#else

	#define Sam_New(Type, nCount) \
		Sam_New_Impl(nCount, (Type*)NULL)

	#define Sam_Delete(p) \
		Sam_Delete_Impl(p)

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