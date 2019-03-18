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


	// 分配内存
	void*							Allocation( size_t nSize, const char* pFile, int nLine );



	// 释放内存
	void							Retrieve( void* pPtr );


};

