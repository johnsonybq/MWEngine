/************************************************************************/
/*
文件名: IMemoryManager.h
描  述: IMemoryManager接口
日  期: 12/04/2019
作  者: MibuWolf
版	本: 1.0
备  注:
*/
/************************************************************************/

#pragma once
#include "EBus\EBus.h"

namespace Core
{

	class IMemoryManager
	{
	public:


		/**
		@breif		初始化

		@param		[OUT]
		return 		加载成功/失败
		*/
		virtual	bool	Initialize() = 0;


		/**
		@breif		分配内存

		@param		[OUT]
		return 		分配的内存地址
		*/
		virtual void*		Allocation(size_t nSize, const char* pFile, int nLine) = 0;



		/**
		@breif		释放内存

		@param		[OUT]
		return 		分配的内存地址
		*/
		virtual void		Retrieve(void* pPtr) = 0;

	};

	using MemoryEBus = Core::EBus<IMemoryManager>;
}
