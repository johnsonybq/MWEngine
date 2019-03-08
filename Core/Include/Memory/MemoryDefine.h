#pragma once
#include "MemoryManager.h"


#ifdef _DEBUG


static MemoryManager sMgr;


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


#define					new			new( __FILE__, __LINE__ )
#define					delete		( SetOwner( __FILE__, __LINE__ ), false ) ? SetOwner( "", 0 ) : delete


#define					malloc( nSize )		AllocationMemory( nSize, __FILE__, __LINE__ )
#define					free( pPtr )		RetrieveMemory( pPtr )


#endif