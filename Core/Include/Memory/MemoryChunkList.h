#pragma once
#include <assert.h>
#include "MemoryChunk.h"
#include "MemoryHelper.h"



// 大内存块列表管理
class				MemoryChunkList
{
public:

	
	MemoryChunkList();


	~MemoryChunkList();


public:


	// 请求分配一定大小的内存区域
	void*						Allocation(size_t nSize, const char* pFile, int nLine );



	// 请求释放某一大内存区域
	void						Retrieve( void* pVoid );


private:


	// 根据内存数据地址查找内存块地址
	MemoryChunk*				GetChunk( void* pVoid );


	// 为内存块分配指定大小的内存数据
	MemoryChunk*				AllocaChunk( size_t nSize, const char* pFile, int nLine );


	// 释放内存块中数据并将内存块放入内存缓冲区
	bool						RetrieveChunk( MemoryChunk* pChunk );


	// 检测内存块是否访问越界
	void						CheckFlowOver( MemoryChunk* pChunk );


	// 检测内存块内存泄漏
	void						CheckLeak( MemoryChunk* pChunk );


	// 清空
	void						Clear();


private:


	MemoryChunk*				m_pChunkHead;		// 当前使用的大内存块列表表头

};

