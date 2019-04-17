#include "MemoryManager.h"

namespace Core
{

	MemoryManager::MemoryManager()
	{
		pChunkList = new MemoryChunkList();
		pPoolManager = new PoolManager();
	}

	MemoryManager::~MemoryManager()
	{

	}

	bool MemoryManager::Initialize()
	{
		MemoryEBus::pTest = new int;
		MemoryEBus::BusConnect(this);
		return true;
	}

	void * MemoryManager::Allocation(size_t nSize, const char * pFile, int nLine)
	{
		if (nSize > 256)
		{
			return pChunkList->Allocation(nSize, pFile, nLine);
		}
		else
		{
			return pPoolManager->Allocation(nSize, pFile, nLine);
		}
	}

	void MemoryManager::Retrieve(void * pPtr)
	{
		unsigned int* pSize = reinterpret_cast<unsigned int*>(reinterpret_cast<int>(pPtr) - sizeof(unsigned int));

		if (0 == pSize)
		{
			return;
		}

		if (*pSize > 256)
		{
			pChunkList->Retrieve(pPtr);
		}
		else
		{
			pPoolManager->Retrieve(pPtr);
		}
	}

}

