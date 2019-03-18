#pragma once
#include <assert.h>
#include <stdarg.h>
#include "MemoryPool.h"
#include "MemoryArray.h"




#define					POOLCOUNT			64
#define					NORAMLPOOLSIZE		1024




class	PoolManager
{
public:


	PoolManager();


	~PoolManager();


public:


	
	// 分配内存
	void*							Allocation(unsigned int nSize, const char* pFile, int nLine );



	// 释放内存
	void							Retrieve( void* pPtr );


	// 释放所有缓冲区内存
	void							Release();


private:


	MemoryArray<void*>					m_arrMemeory;			// 保存所有分配的内存
	MemoryArray<MemoryPool*>			m_arrMemPool;			// 保存所有内存缓冲区
	unsigned short						m_ByteAligning;			// 字节对齐方式
	unsigned short						m_MaxPoolSize;			// 每次为内存池分配内存的上限
	unsigned short						m_MaxNodeSize;			// 可以放在内存池中的最大节点大小(当用户请求内存大小大于此数值时将不适用缓冲区存储改用内存块列表)
	unsigned short						m_nCurPoolCount;		// 当前创建的缓冲区个数					

};
