#pragma once
#include <assert.h>
#include "MemoryChunk.h"
#include "MemoryHelper.h"
#include "MemoryChunkList.h"


namespace Core
{
	MemoryChunkList::MemoryChunkList()
		:m_pChunkHead(0)
	{

	}



	MemoryChunkList::~MemoryChunkList()
	{
		Clear();
	}



	// 请求分配内存
	void*					MemoryChunkList::Allocation(size_t nSize, const char* pFile, int nLine)
	{
		MemoryChunk* pChunk = 0;

		pChunk = AllocaChunk(nSize, pFile, nLine);

		if (0 == pChunk)
		{
			return 0;
		}

		MemoryHelper::GetInstance()->OnMemAlloc(nSize, sizeof(MemoryChunk));

		void* pAllocNode = reinterpret_cast<void*>(reinterpret_cast<char*>(pChunk) + sizeof(MemoryChunk));

		return pAllocNode;
	}



	// 请求释放内存
	void						MemoryChunkList::Retrieve(void* pVoid)
	{
		MemoryChunk* pChunk = GetChunk(pVoid);

		bool bSuc = RetrieveChunk(pChunk);

		assert(bSuc || "MemoryChunkList::RetrieveChunk Fail!");
	}



	MemoryChunk*				MemoryChunkList::AllocaChunk(size_t nSize, const char* pFile, int nLine)
	{
		MemoryChunk* pChunk = reinterpret_cast<MemoryChunk*>(::malloc(sizeof(MemoryChunk) + nSize + sizeof(PaddingCode)));

		if (0 == pChunk)
		{
			return 0;
		}

		pChunk->Init();
		pChunk->nLine = nLine;
		pChunk->nSize = nSize;
		memcpy(pChunk->sFile, pFile, MAX_FILE_PATH);

		PaddingCode* pPad = reinterpret_cast<PaddingCode*>(reinterpret_cast<char*>(pChunk) + nSize + sizeof(MemoryChunk));
		pPad->InitPadding();
		pChunk->pNext = m_pChunkHead;

		if (m_pChunkHead)
		{
			m_pChunkHead->pPer = pChunk;
		}

		m_pChunkHead = pChunk;

		return m_pChunkHead;
	}



	// 根据内存数据地址查找内存地址
	MemoryChunk*				MemoryChunkList::GetChunk(void* pVoid)
	{
		if (0 == pVoid)
		{
			return 0;
		}

		char* pBegin = reinterpret_cast<char*>(pVoid) - sizeof(MemoryChunk);

		return reinterpret_cast<MemoryChunk*>(pBegin);
	}




	bool						MemoryChunkList::RetrieveChunk(MemoryChunk* pChunk)
	{
		if (0 == pChunk)
		{
			return false;
		}

		MemoryChunk* pNode = m_pChunkHead;
		bool bSuc = false;

		while (pNode)
		{
			if (pNode == pChunk)
			{
				bSuc = true;
				CheckFlowOver(pChunk);

				MemoryHelper::GetInstance()->OnMemRetrieve(pChunk->nSize, sizeof(MemoryChunk));
				pChunk->Init();

				if (pNode->pPer)
				{
					pNode->pPer->pNext = pNode->pNext;
				}

				if (pNode->pNext)
				{
					pNode->pNext->pPer = pNode->pPer;
				}
			}
		}

		return bSuc;
	}



	void					MemoryChunkList::CheckLeak(MemoryChunk* pNode)
	{
		if (pNode)
		{
			MemoryHelper::GetInstance()->ReportMemLeak(pNode->sFile, pNode->nLine, pNode->nSize, reinterpret_cast<int>(pNode));
		}
	}



	void					MemoryChunkList::CheckFlowOver(MemoryChunk* pChunk)
	{
		PaddingCode* pPad = reinterpret_cast<PaddingCode*>(reinterpret_cast<char*>(pChunk) + pChunk->nSize + sizeof(MemoryChunk));

		if (0 == pChunk || 0 == pPad)
		{
			return;
		}

		if (pChunk->Invalid() || pPad->InvalidPtr())
		{
			MemoryHelper::GetInstance()->ReportMemFlowOver(pChunk->sFile, pChunk->nLine, reinterpret_cast<int>(pChunk));
		}
	}



	void					MemoryChunkList::Clear()
	{
		MemoryChunk* pChunk = m_pChunkHead;

		while (m_pChunkHead)
		{
			CheckFlowOver(m_pChunkHead);
			CheckLeak(m_pChunkHead);
			pChunk = m_pChunkHead->pNext;

			::free(m_pChunkHead);
			m_pChunkHead = pChunk;
		}

		m_pChunkHead = 0;
	}
}

