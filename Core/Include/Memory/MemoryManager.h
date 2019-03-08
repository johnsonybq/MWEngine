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



MemoryManager::MemoryManager()
{

}



MemoryManager::~MemoryManager()
{

}




void*						MemoryManager::Allocation( size_t nSize, const char* pFile, int nLine )
{
	if ( nSize > 256 )
	{
		return sChunkList.Allocation( nSize, pFile, nLine );
	}
	else
	{
		return sPoolMgr.Allocation( nSize, pFile, nLine );
	}
}




void						MemoryManager::Retrieve( void* pPtr )
{
	unsigned int* pSize = reinterpret_cast<unsigned int*>( reinterpret_cast<int>( pPtr ) - sizeof( unsigned int ) );
	
	if ( 0 == pSize )
	{
		return;
	}

	if ( *pSize > 256 )
	{
		sChunkList.Retrieve( pPtr );
	}
	else
	{
		sPoolMgr.Retrieve( pPtr );
	}
}