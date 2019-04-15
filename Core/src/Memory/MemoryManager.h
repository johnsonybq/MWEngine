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


		// ��ʼ��
		virtual	bool		Initialize();


		// �����ڴ�
		virtual void*		Allocation(size_t nSize, const char* pFile, int nLine);


		// �ͷ��ڴ�
		virtual void		Retrieve(void* pPtr);


	private:

		MemoryChunkList*				pChunkList;
		PoolManager*					pPoolManager;
	};

}