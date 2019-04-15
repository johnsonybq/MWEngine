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
#include "IMemoryManager.h"

#pragma warning(disable:4595)
#pragma warning(disable:4291)

#ifndef MW_New


inline void*							operator new(std::size_t nSize, const char* pFile, int nLine)
	{
		void* pVoid = nullptr;
		Core::MemoryEBus::BroadcastResult(pVoid, &Core::IMemoryManager::Allocation, nSize, pFile, nLine);
		return pVoid;
	}


inline void*							operator new[](size_t nSize, const char* pFile, int nLine)
	{
		void* pVoid = nullptr;
		Core::MemoryEBus::BroadcastResult(pVoid, &Core::IMemoryManager::Allocation, nSize, pFile, nLine);

		return pVoid;
	}


inline	void							operator delete(void* pPtr)
	{
		Core::MemoryEBus::Broadcast(&Core::IMemoryManager::Retrieve, pPtr);
	}


inline void							operator delete[](void* pPtr)
	{
		Core::MemoryEBus::Broadcast(&Core::IMemoryManager::Retrieve, pPtr);
	}


inline	void							SetOwner(const char* pFile, int nLine)
	{

	}

#define					MW_New			new( __FILE__, __LINE__ )
#define					MW_Delete		( SetOwner( __FILE__, __LINE__ ), false ) ? SetOwner( "", 0 ) : delete


#define					MW_Malloc( nSize )		AllocationMemory( nSize, __FILE__, __LINE__ )
#define					MW_Free( pPtr )		RetrieveMemory( pPtr )






#endif