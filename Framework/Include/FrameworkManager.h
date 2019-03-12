/************************************************************************/
/*
文件名: FrameworkManager.h
描  述: 框架入口
日  期: 14/12/2018
作  者: Sam
版	本: 1.0
备  注:
*/
/************************************************************************/
#pragma once
#include "Entity\IEntitySystem.h"
//#include "Asset\IAssetSystem.h"


namespace Framework
{
	class  FrameworkManager
	{
		SINGLETON_IMPLEMENT(FrameworkManager);

	public:
		
		~FrameworkManager();

	public:


		/**
		@breif		初始化框架
		*/
		void					Initialization();


		/**
		@breif		获取资源系统
		*/
		//IAssetSystem*			GetAssetSystem();


		/**
		@breif		获取实体系统
		*/
		IEntitySystem*			GetEntitySystem();


		/**
		@breif		销毁框架
		*/
		void					Destory();


	};
}