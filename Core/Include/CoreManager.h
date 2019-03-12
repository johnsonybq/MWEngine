/************************************************************************/
/*
文件名: CoreManager.h
描  述: 核心库入口
日  期: 14/12/2018
作  者: Sam
版	本: 1.0
备  注:
*/
/************************************************************************/
#pragma once
#include "MWCore.h"
#include "Module\IModuleManager.h"


namespace Core
{
	class  CoreManager
	{
		SINGLETON_IMPLEMENT(CoreManager);

	public:
		
		~CoreManager();

	public:


		/**
		@breif		初始化框架
		*/
		void					Initialization();


		/**
		@breif		获取模块管理器
		*/
		IModuleManager*			GetModuleManager();


		/**
		@breif		销毁框架
		*/
		void					Destory();


	};
}