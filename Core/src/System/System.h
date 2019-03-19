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
		

		// ��ʼ��
		virtual	bool			Initialize();


		// ��ȡ��Ŀ¼
		virtual	const char*		GetRootPath();


		// ��ȡϵͳʱ��Сʱ
		virtual	int				GetLocalTime(TIME_TYPE timeType);


	};

}