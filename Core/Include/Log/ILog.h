#pragma once
#include "EBus\EBus.h"

namespace Core
{
	class ILog
	{
	public:


		/**
		@breif		初始化

		@param		[OUT]
		return 		加载成功/失败
		*/
		virtual	bool	Initialize() VPURE;


		/**
		@breif		输出日志(最低优先级)

		@param		[IN]
		msg			日志内容
		*/
		virtual	void	Log(const char* path, ...) VPURE;



		/**
		@breif		输出警告

		@param		[IN]
		msg			日志内容
		*/
		virtual	void	Warning(const char* path, ...) VPURE;



		/**
		@breif		输出错误

		@param		[IN]
		msg			日志内容
		*/
		virtual	void	Error(const char* path, ...) VPURE;


		/**
		@breif		写入Log文件

		@param		[IN]
		msg			日志内容
		*/
		virtual	void	ToFile(const char* path, ...) VPURE;


		/**
		@breif		打开Log文件

		@param		[IN]
		path		日志地址
		*/
		virtual	void	OpenLogFile(const char* path) VPURE;


		/**
		@breif		关闭Log文件
		*/
		virtual	void	CloseLogFile(const char* path) VPURE;


	};

	using LogEBus = EBus<ILog>;
}