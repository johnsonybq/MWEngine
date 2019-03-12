#pragma once
#include <assert.h>
#include "MemoryChunk.h"
#include "MemoryHelper.h"



// ���ڴ���б����
class				MemoryChunkList
{
public:

	
	MemoryChunkList();


	~MemoryChunkList();


public:


	// �������һ����С���ڴ�����
	void*						Allocation( unsigned short nSize, const char* pFile, int nLine );



	// �����ͷ�ĳһ���ڴ�����
	void						Retrieve( void* pVoid );


private:


	// �����ڴ����ݵ�ַ�����ڴ���ַ
	MemoryChunk*				GetChunk( void* pVoid );


	// Ϊ�ڴ�����ָ����С���ڴ�����
	MemoryChunk*				AllocaChunk( size_t nSize, const char* pFile, int nLine );


	// �ͷ��ڴ�������ݲ����ڴ������ڴ滺����
	bool						RetrieveChunk( MemoryChunk* pChunk );


	// ����ڴ���Ƿ����Խ��
	void						CheckFlowOver( MemoryChunk* pChunk );


	// ����ڴ���ڴ�й©
	void						CheckLeak( MemoryChunk* pChunk );


	// ���
	void						Clear();


private:


	MemoryChunk*				m_pChunkHead;		// ��ǰʹ�õĴ��ڴ���б��ͷ

};




MemoryChunkList::MemoryChunkList()
:m_pChunkHead( 0 )
{

}



MemoryChunkList::~MemoryChunkList()
{
	Clear();
}



// ��������ڴ�
void*					MemoryChunkList::Allocation( unsigned short nSize, const char* pFile, int nLine )
{
	MemoryChunk* pChunk = 0;

	pChunk = AllocaChunk( nSize, pFile, nLine );

	if ( 0 == pChunk )
	{
		return 0;
	}

	MemoryHelper::GetInstance()->OnMemAlloc( nSize, sizeof( MemoryChunk ) );

	void* pAllocNode = reinterpret_cast<void*>( reinterpret_cast<char*>( pChunk ) + sizeof( MemoryChunk ) );

	return pAllocNode;
}



// �����ͷ��ڴ�
void						MemoryChunkList::Retrieve( void* pVoid )
{
	MemoryChunk* pChunk = GetChunk( pVoid );

	bool bSuc = RetrieveChunk( pChunk );

	assert( bSuc || "MemoryChunkList::RetrieveChunk Fail!" );
}



MemoryChunk*				MemoryChunkList::AllocaChunk( size_t nSize, const char* pFile, int nLine )
{
	MemoryChunk* pChunk = reinterpret_cast<MemoryChunk*>( ::malloc( sizeof( MemoryChunk ) + nSize + sizeof( PaddingCode ) ) );

	if ( 0 == pChunk )
	{
		return 0;
	}

	pChunk->Init();
	pChunk->nLine = nLine;
	pChunk->nSize = nSize;
	memcpy( pChunk->sFile, pFile, MAX_FILE_PATH );

	PaddingCode* pPad = reinterpret_cast<PaddingCode*>( reinterpret_cast<char*>( pChunk ) + nSize + sizeof( MemoryChunk ) );
	pPad->InitPadding();
	pChunk->pNext = m_pChunkHead;

	if ( m_pChunkHead )
	{
		m_pChunkHead->pPer = pChunk;
	}

	m_pChunkHead = pChunk;

	return m_pChunkHead;
}



// �����ڴ����ݵ�ַ�����ڴ��ַ
MemoryChunk*				MemoryChunkList::GetChunk( void* pVoid )
{
	if ( 0 == pVoid )
	{
		return 0;
	}

	char* pBegin = reinterpret_cast<char*>( pVoid ) - sizeof( MemoryChunk );

	return reinterpret_cast<MemoryChunk*>( pBegin );
}




bool						MemoryChunkList::RetrieveChunk( MemoryChunk* pChunk )
{
	if ( 0 == pChunk )
	{
		return false;
	}

	MemoryChunk* pNode = m_pChunkHead;
	bool bSuc = false;

	while ( pNode )
	{
		if ( pNode == pChunk )
		{
			bSuc = true;
			CheckFlowOver( pChunk );

			MemoryHelper::GetInstance()->OnMemRetrieve( pChunk->nSize, sizeof( MemoryChunk ) );
			pChunk->Init();

			if ( pNode->pPer )
			{
				pNode->pPer->pNext = pNode->pNext;
			}

			if ( pNode->pNext )
			{
				pNode->pNext->pPer = pNode->pPer;
			}
		}
	}

	return bSuc;
}



void					MemoryChunkList::CheckLeak( MemoryChunk* pNode )
{
	if ( pNode )
	{
		MemoryHelper::GetInstance()->ReportMemLeak( pNode->sFile, pNode->nLine, pNode->nSize, reinterpret_cast<int>( pNode ) );
	}
}



void					MemoryChunkList::CheckFlowOver( MemoryChunk* pChunk )
{
	PaddingCode* pPad = reinterpret_cast<PaddingCode*>( reinterpret_cast<char*>( pChunk ) + pChunk->nSize + sizeof( MemoryChunk ) );

	if ( 0 == pChunk || 0 == pPad )
	{
		return;
	}

	if( pChunk->Invalid() || pPad->InvalidPtr() )
	{
		MemoryHelper::GetInstance()->ReportMemFlowOver( pChunk->sFile, pChunk->nLine, reinterpret_cast<int>( pChunk ) );
	}
}



void					MemoryChunkList::Clear()
{
	MemoryChunk* pChunk = m_pChunkHead;

	while( m_pChunkHead )
	{
		CheckFlowOver( m_pChunkHead );
		CheckLeak( m_pChunkHead );
		pChunk = m_pChunkHead->pNext;

		::free( m_pChunkHead );
		m_pChunkHead = pChunk;
	}

	m_pChunkHead = 0;
}