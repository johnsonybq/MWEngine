#pragma once
#include "System\ISystem.h"


namespace Core
{
	class System : public ISystem
	{
	public:

		SINGLETON_IMPLEMENT(System);


	public:

		~System();

	public:
		

		// 初始化
		virtual	bool			Initialize();


		// 获取根目录
		virtual	const char*		GetRootPath();


		// 获取系统时间小时
		virtual	int				GetLocalTime(TIME_TYPE timeType);


	};

}