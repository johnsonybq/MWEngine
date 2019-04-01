/************************************************************************/
/*
文件名: IReflectManager.h
描  述: 反射管理器接口
日  期: 26/03/2019
作  者: MibuWolf
版	本: 1.0
备  注:
*/
/************************************************************************/

#pragma once
#include "EBus\EBus.h"
#include "IReflectFactory.h"

namespace Core
{
	class IReflectManager
	{
	public:


		/**
		@breif		初始化

		@param		[OUT]
		return 		加载成功/失败
		*/
		virtual	bool				Initialize() PURE;


		/**
		@breif		注册

		@param		[OUT]
		return 		加载成功/失败
		*/
		virtual	bool				Register(const char* className, IReflectFactory* factory) PURE;


		/**
		@breif		获取反射工厂

		@param		[OUT]
		return 		反射工厂
		*/
		virtual	IReflectFactory*	GetReflectFactory(const char* className) PURE;



		/**
		@breif		解注册

		@param		[OUT]
		return 		加载成功/失败
		*/
		virtual	bool				UnRegister(const char* className) PURE;



	};

	using ReflectionEBus = EBus<IReflectManager>;
}