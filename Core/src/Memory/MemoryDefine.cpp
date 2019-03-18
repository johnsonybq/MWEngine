#pragma once
#include "Memory\MemoryDefine.h"


#ifdef _DEBUG




void*				AllocationMemory( size_t nSize, const char* pFile, int nLine )
{
	void* p = sMgr.Allocation( nSize, pFile, nLine );

	return p;
}


void				RetrieveMemory( void* pPtr )
{
	return sMgr.Retrieve( pPtr );
}



void*							operator new( size_t nSize, const char* pFile, int nLine )
{
	return AllocationMemory( nSize, pFile, nLine );
}


void*							operator new[]( size_t nSize, const char* pFile, int nLine )
{
	return AllocationMemory( nSize, pFile, nLine );
}


void							operator delete( void* pPtr )
{
	RetrieveMemory( pPtr );
}


void							operator delete[]( void* pPtr )
{
	RetrieveMemory( pPtr );
}



void							SetOwner( const char* pFile, int nLine )
{

}




#endif