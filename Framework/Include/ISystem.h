/************************************************************************/
/*
文件名: ISystem.h
描  述: 所有系统管理类的基类
日  期: 18/12/2018
作  者: Sam
版	本: 1.0
备  注:
*/
/************************************************************************/
#pragma once
#include "IMiscellaneous.h"


namespace Framework
{
	class ISystem
	{
	public:


		/**
		@breif		初始化
		*/
		virtual	void				Initialization() PURE;


		/**
		@breif		销毁
		*/
		virtual	void				Destory() PURE;


	};
}