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
	void*							Allocation( size_t nSize, const char* pFile, int nLine );



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



PoolManager::PoolManager()
:m_arrMemeory(), m_arrMemPool( POOLCOUNT ), m_ByteAligning( 4 ), m_nCurPoolCount( 0 )
{
	m_MaxPoolSize = m_ByteAligning * NORAMLPOOLSIZE;
	m_MaxNodeSize = m_ByteAligning * POOLCOUNT;

	unsigned short nIndex = 0;

	for ( nIndex = 0; nIndex < POOLCOUNT; ++nIndex )
	{
		MemoryPool* pPool = reinterpret_cast<MemoryPool*>( ::malloc( sizeof( MemoryPool ) ) );
		assert( pPool );
		memset( pPool, 0, sizeof( MemoryPool ) );
		m_arrMemPool.Add( pPool );
	}
}



PoolManager::~PoolManager()
{
	Release();
}



void*					PoolManager::Allocation( size_t nSize, const char* pFile, int nLine )
{
	assert( nSize <= m_MaxNodeSize || "PoolManager::Allocation Size Error!" );

	unsigned short nIndex = ( nSize - 1 ) / m_ByteAligning;

	if ( 0 == m_arrMemPool[nIndex] )
	{
		return 0;
	}

	unsigned short nUnitSize = 0;
	unsigned short nActualSize = 0;
	unsigned short nUnitCount = 0;

	nUnitSize = ( nIndex + 1 ) * m_ByteAligning;
	nActualSize = sizeof( MemoryNode ) + nUnitSize + sizeof( PaddingCode );
	nUnitCount = m_MaxPoolSize / nActualSize;

	if ( m_arrMemPool[nIndex]->IsEmpty() )
	{
		void* pNewPool = ::malloc( nUnitCount * nActualSize );
		assert( pNewPool || "PoolManager::Allocation Malloc Failed!" );
		memset( pNewPool, 0, nUnitCount * nActualSize );
		m_arrMemPool[nIndex]->InitMemoryPool( pNewPool, nUnitSize, nUnitCount );
		m_arrMemeory.Add( pNewPool );
		++ m_nCurPoolCount;
	}

	MemoryNode* pNode = m_arrMemPool[nIndex]->Allocation( nSize, pFile, nLine );

	if ( 0 == pNode )
	{
		return 0;
	}

	MemoryHelper::GetInstance()->OnMemAlloc( nUnitSize, sizeof( MemoryNode ) );

	void* pAllocNode = reinterpret_cast<void*>( reinterpret_cast<char*>( pNode ) + sizeof( MemoryNode ) );
	
	return pAllocNode;
}



void					PoolManager::Retrieve( void* pPtr )
{
	if ( 0 == pPtr )
	{
		return;
	}

	MemoryNode* pNode = reinterpret_cast<MemoryNode*>( reinterpret_cast<char*>( pPtr ) - sizeof( MemoryNode ) );

	unsigned short nIndex = ( pNode->nSize - 1 ) / m_ByteAligning;

	assert( nIndex < POOLCOUNT || "PoolManager::Retrieve Error!" );

	if ( 0 == m_arrMemPool[nIndex] )
	{
		return;
	}

	if ( nIndex < POOLCOUNT )
	{
		m_arrMemPool[nIndex]->Retrieve( pNode );

		MemoryHelper::GetInstance()->OnMemRetrieve( ( nIndex + 1 ) * m_ByteAligning, sizeof( MemoryNode ) );
	}
}




// 释放所有内存
void						PoolManager::Release()
{
	unsigned short nIndex = 0;

	for ( ; nIndex < POOLCOUNT; ++nIndex )
	{
		if ( m_arrMemPool[nIndex] )
		{
			m_arrMemPool[nIndex]->Clear();
			::free( m_arrMemPool[nIndex] );
		}
	}

	m_arrMemPool.Clear();

	unsigned int nMemIndex = 0;

	for ( ; nMemIndex < m_nCurPoolCount; ++nMemIndex )
	{
		::free( m_arrMemeory[nMemIndex] );
	}

	m_arrMemeory.Clear();

}