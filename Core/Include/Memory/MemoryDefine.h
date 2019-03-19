/************************************************************************/
/*
文件名: MemoryDefine.h
描  述: 内存接口定义
日  期: 19/03/2019
作  者: MibuWolf
版	本: 1.0
备  注:
*/
/************************************************************************/

#pragma once
#include "MemoryManager.h"


#ifdef _DEBUG


static MemoryManager sMgr;

#ifndef MW_New

void*				AllocationMemory(size_t nSize, const char* pFile, int nLine);

void				RetrieveMemory(void* pPtr);



void*							operator new(std::size_t nSize, const char* pFile, int nLine);


void*							operator new[](size_t nSize, const char* pFile, int nLine);


void							operator delete(void* pPtr);


void							operator delete[](void* pPtr);




void							SetOwner(const char* pFile, int nLine);




#define					MW_New			new( __FILE__, __LINE__ )
#define					MW_Delete		( SetOwner( __FILE__, __LINE__ ), false ) ? SetOwner( "", 0 ) : delete


#define					MW_Malloc( nSize )		AllocationMemory( nSize, __FILE__, __LINE__ )
#define					MW_Free( pPtr )		RetrieveMemory( pPtr )

#endif // !MW_New




#endif