/************************************************************************/
/*
文件名: IFramework.h
描  述: 框架接口
日  期: 01/04/2019
作  者: MibuWolf
版	本: 1.0
备  注:
*/
/************************************************************************/
#pragma once
#include "MWCore.h"


namespace Framework
{
	class IFramework
	{
	public:


		/**
		@breif		初始化

		@param		[OUT]
		return 		加载成功/失败
		*/
		virtual	bool	Initialize() PURE;


	};
}