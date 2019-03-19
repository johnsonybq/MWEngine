/************************************************************************/
/*
文件名: ISystem.h
描  述: 获取各种系统数据
日  期: 19/03/2019
作  者: MibuWolf
版	本: 1.0
备  注:
*/
/************************************************************************/
#pragma once
#include "EBus\EBus.h"

namespace Core
{
	enum TIME_TYPE
	{
		E_TIME_TYPE_YEAR = 0,			// 年
		E_TIME_TYPE_MOTH = 1,			// 月
		E_TIME_TYPE_DAY = 2,			// 日
		E_TIME_TYPE_HOUR = 3,			// 时
		E_TIME_TYPE_MINUTE = 4,			// 分
		E_TIME_TYPE_SECOND = 5,			// 秒
		E_TIME_TYPE_MILLUSECOND = 6,    // 毫秒
	};

	class ISystem
	{
	public:


		/**
		@breif		初始化

		@param		[OUT]
		return 		加载成功/失败
		*/
		virtual	bool			Initialize() VPURE;



		/**
		@breif		获取根目录

		@param		[OUT]
		return 		根目录
		*/
		virtual	const char*		GetRootPath() VPURE;


		/**
		@breif		获取系统时间小时

		@param		[OUT]
		return 		小时
		*/
		virtual	int				GetLocalTime(TIME_TYPE timeType) VPURE;


	};

	using SystemEBus = EBus<ISystem>;
}