#pragma once
//#include <GLM\integer.hpp>

namespace Framework
{
	//typedef		glm::uint UUID;
	typedef		int UUID;
	#define		INVALID_UUID 0xffffffff

	using		EntityID = int;

	#define PURE =0

	#define FRAMEWORK_EXPORTS_LIB

	#ifdef FRAMEWORK_EXPORTS_LIB
	#define FRAMEWORK_EXPORTS __declspec(dllexport)
	#else
	#define FRAMEWORK_EXPORTS __declspec(dllimport)
	#endif


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