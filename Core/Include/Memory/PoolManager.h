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


	
	// �����ڴ�
	void*							Allocation( size_t nSize, const char* pFile, int nLine );



	// �ͷ��ڴ�
	void							Retrieve( void* pPtr );


	// �ͷ����л������ڴ�
	void							Release();


private:


	MemoryArray<void*>					m_arrMemeory;			// �������з�����ڴ�
	MemoryArray<MemoryPool*>			m_arrMemPool;			// ���������ڴ滺����
	unsigned short						m_ByteAligning;			// �ֽڶ��뷽ʽ
	unsigned short						m_MaxPoolSize;			// ÿ��Ϊ�ڴ�ط����ڴ������
	unsigned short						m_MaxNodeSize;			// ���Է����ڴ���е����ڵ��С(���û������ڴ��С���ڴ���ֵʱ�������û������洢�����ڴ���б�)
	unsigned short						m_nCurPoolCount;		// ��ǰ�����Ļ���������					

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




// �ͷ������ڴ�
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