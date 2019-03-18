#pragma once
#include "PoolManager.h"
#include "MemoryChunkList.h"




static PoolManager			sPoolMgr;
static MemoryChunkList		sChunkList;




class	MemoryManager
{
public:

		
	MemoryManager();


	~MemoryManager();


public:


	// �����ڴ�
	void*							Allocation( size_t nSize, const char* pFile, int nLine );



	// �ͷ��ڴ�
	void							Retrieve( void* pPtr );


};

