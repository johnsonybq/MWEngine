/************************************************************************/
/*
文件名: IReflectFactory.h
描  述: 反射工厂基类接口
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
	class IReflectFactory
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



	template<typename Class>
	class DefaultReflectFactory : public IReflectFactory
	{
	public:


		DefaultReflectFactory() {};

		~DefaultReflectFactory() {};

	public:


		// 创建
		virtual	void*	CreateClass(const char* className)
		{
			return MW_New Class();
		}


		// 销毁
		virtual void	DestoryClass(void* pClass)
		{
			if (pClass != nullptr)
				MW_Delete pClass；
		}
	};

}