#pragma once
#include "MemoryPool.h"



namespace Core
{
	MemoryPool::MemoryPool()
		:m_nDataSize(0), m_nTotalSize(0), m_pPoolHead(0), m_AllocList()
	{

	}


	MemoryPool::MemoryPool(unsigned short nPoolID, unsigned short nDataSize)
		:m_nDataSize(nDataSize), m_nTotalSize(0), m_pPoolHead(0), m_AllocList()
	{

	}


	MemoryPool::~MemoryPool()
	{
		Clear();
	}



	// 初始化内存缓冲
	void								MemoryPool::InitMemoryPool(void* pPool, unsigned short nDataSize, unsigned short nCount)
	{
		if (0 == pPool)
		{
			return;
		}

		m_nDataSize = nDataSize;
		m_pPoolHead = reinterpret_cast<MemoryNode*>(pPool);
		MemoryNode* pNode = m_pPoolHead;

		int nIndex = 0;
		for (nIndex = 0; nIndex < nCount - 1; ++nIndex)
		{
			pNode->Init();
			PaddingCode* pPad = reinterpret_cast<PaddingCode*>(reinterpret_cast<char*>(pNode) + m_nDataSize + sizeof(MemoryNode));

			if (pPad)
			{
				pPad->InitPadding();
			}

			MemoryNode*		pNextNode = GetNextNode(pNode);
			pNode->pNext = pNextNode;
			pNode = pNextNode;
		}

		pNode->Init();
		pNode->pNext = 0;

		m_nTotalSize = nCount;


	}



	MemoryNode*							MemoryPool::Allocation(unsigned short nSize, const char* pFile, int nLine)
	{
		if (0 == m_pPoolHead)
		{
			m_nTotalSize = 0;
			return 0;
		}

		MemoryNode* pAllocNode = m_pPoolHead;
		m_pPoolHead = m_pPoolHead->pNext;

		--m_nTotalSize;

		pAllocNode->bUsed = true;
		memcpy(pAllocNode->sFile, pFile, MAX_FILE_PATH);
		pAllocNode->sFile[MAX_FILE_PATH - 1] = '\0';
		pAllocNode->nLine = nLine;
		pAllocNode->nSize = nSize;

		if (!pAllocNode->bGuarded)
		{
			pAllocNode->bGuarded = true;
			m_AllocList.Add(pAllocNode);
		}

		return pAllocNode;
	}




	void							MemoryPool::Retrieve(MemoryNode* pNode)
	{
		CheckFlowOver(pNode);

		pNode->Init();
		pNode->bGuarded = true;

		if (0 == m_pPoolHead)
		{
			m_pPoolHead = pNode;
			pNode->pNext = 0;
		}
		else
		{
			pNode->pNext = m_pPoolHead;
			m_pPoolHead = pNode;
		}

		++m_nTotalSize;
	}



	// 清空内存缓冲区
	// 清空内存缓冲区时在缓冲区中只是将头节点置空
	// 并不释放内存 真正的内存释放由Alloc释放( 谁分配 谁释放 )
	void							MemoryPool::Clear()
	{
		unsigned int nCount = m_AllocList.GetSize();
		unsigned int nIndex = 0;

		for (; nIndex < nCount; ++nIndex)
		{
			CheckFlowOver(m_AllocList[nIndex]);
			CheckLeak(m_AllocList[nIndex]);
		}

		m_nDataSize = m_nTotalSize = 0;
		m_pPoolHead = 0;
	}




	// 获取下一个内存节点
	MemoryNode*						MemoryPool::GetNextNode(MemoryNode* pNode)
	{
		if (0 == pNode)
		{
			return 0;
		}

		char* pNext = 0;
		pNext = reinterpret_cast<char*>(pNode) + sizeof(MemoryNode) + m_nDataSize + sizeof(PaddingCode);

		return reinterpret_cast<MemoryNode*>(pNext);
	}




	MemoryPool&							MemoryPool::operator =(const MemoryPool& _other)
	{
		m_nDataSize = _other.m_nDataSize;
		m_nTotalSize = _other.m_nTotalSize;
		m_pPoolHead = _other.m_pPoolHead;

		return *this;
	}



	bool								MemoryPool::IsEmpty()
	{
		if (m_pPoolHead == 0 || m_nTotalSize == 0)
		{
			return true;
		}

		return false;
	}



	void								MemoryPool::CheckFlowOver(MemoryNode* pNode)
	{
		PaddingCode* pPad = reinterpret_cast<PaddingCode*>(reinterpret_cast<char*>(pNode) + pNode->nSize + sizeof(MemoryNode));

		if (0 == pNode || 0 == pPad)
		{
			return;
		}

		if (pNode->Invalid() || pPad->InvalidPtr())
		{
			MemoryHelper::GetInstance()->ReportMemFlowOver(pNode->sFile, pNode->nLine, reinterpret_cast<int>(pNode));
		}
	}



	void								MemoryPool::CheckLeak(MemoryNode* pNode)
	{
		if (pNode && pNode->bUsed)
		{
			MemoryHelper::GetInstance()->ReportMemLeak(pNode->sFile, pNode->nLine, pNode->nSize, reinterpret_cast<int>(pNode));
		}
	}
}

