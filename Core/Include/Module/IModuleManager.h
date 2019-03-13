#pragma once
#include "EBus\EBus.h"

namespace Core
{
	class IModuleManager
	{
	public:


		/**
		@breif		初始化

		@param		[OUT]
		return 		加载成功/失败
		*/
		virtual	bool	Initialize() PURE;

		
		/**
		@breif		加载单个模块

		@param		[IN]
		path		模块地址

		@param		[OUT]
		return 		加载成功/失败
		*/
		virtual	bool	LoadModule(const char* path) PURE;



		/**
		@breif		通过配置加载模块列表

		@param		[IN]
		config		配置地址

		@param		[OUT]
		return 		加载成功/失败
		*/
		virtual	bool	LoadAllModules(const char* path) PURE;



		/**
		@breif		判断模块是否被加载

		@param		[IN]
		path		模块地址

		@param		[OUT]
		return 		是否已经加载该模块
		*/
		virtual	bool	IsLoadModule(const char* path) PURE;


		/**
		@breif		移除单个模块

		@param		[IN]
		path		模块地址

		@param		[OUT]
		return 		移除成功/失败
		*/
		virtual	bool	RemoveModule(const char* path) PURE;


		/**
		@breif		移除所有模块

		@param		[OUT]
		return 		移除成功/失败
		*/
		virtual	bool	RemoveAllModules() PURE;


	};

	using ModuleManagerEBus = EBus<IModuleManager>;
}