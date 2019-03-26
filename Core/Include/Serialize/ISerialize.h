/************************************************************************/
/*
文件名: ISerialize.h
描  述:	序列化接口
日  期: 26/03/2019
作  者: MibuWolf
版	本: 1.0
备  注:
*/
/************************************************************************/

#pragma once
#include "MWCore.h"

namespace Core
{
	class ISerialize
	{
	public:


		/**
		@breif		创建类

		@param		[OUT]
		return 		返回对象
		*/
		virtual	void*	CreateClass(const char*) VPURE;



		/**
		@breif		销毁

		@param		[OUT]
		return 		销毁
		*/
		virtual	void	DestoryClass(void*) VPURE;


	};

}