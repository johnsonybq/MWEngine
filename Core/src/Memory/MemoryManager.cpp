#pragma once
#include "Memory\MemoryManager.h"


MemoryManager::MemoryManager()
{

}


MemoryManager::~MemoryManager()
{

}


void*						MemoryManager::Allocation(size_t nSize, const char* pFile, int nLine )
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