#include "MWCore.h"
#include "PoolManager.h"
#include "MemoryChunkList.h"
#include "Memory\IMemoryManager.h"


namespace Core
{
	class MemoryManager : public IMemoryManager
	{
		SINGLETON_IMPLEMENT(MemoryManager);

	public:

		~MemoryManager();

	public:


	public:


		// 初始化
		virtual	bool		Initialize();


		// 分配内存
		virtual void*		Allocation(size_t nSize, const char* pFile, int nLine);


		// 释放内存
		virtual void		Retrieve(void* pPtr);


	private:

		MemoryChunkList*				pChunkList;
		PoolManager*					pPoolManager;
	};

}