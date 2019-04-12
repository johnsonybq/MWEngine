/************************************************************************/
/*
�ļ���: ISystem.h
��  ��: ��ȡ����ϵͳ����
��  ��: 19/03/2019
��  ��: MibuWolf
��	��: 1.0
��  ע:
*/
/************************************************************************/
#pragma once
#include "EBus\EBus.h"

namespace Core
{
	enum TIME_TYPE
	{
		E_TIME_TYPE_YEAR = 0,			// ��
		E_TIME_TYPE_MOTH = 1,			// ��
		E_TIME_TYPE_DAY = 2,			// ��
		E_TIME_TYPE_HOUR = 3,			// ʱ
		E_TIME_TYPE_MINUTE = 4,			// ��
		E_TIME_TYPE_SECOND = 5,			// ��
		E_TIME_TYPE_MILLUSECOND = 6,    // ����
	};

	class ISystem
	{
	public:


		/**
		@breif		��ʼ��

		@param		[OUT]
		return 		���سɹ�/ʧ��
		*/
		virtual	bool			Initialize() VPURE;



		/**
		@breif		��ȡ��Ŀ¼

		@param		[OUT]
		return 		��Ŀ¼
		*/
		virtual	const char*		GetRootPath() VPURE;


		/**
		@breif		��ȡϵͳʱ��Сʱ

		@param		[OUT]
		return 		Сʱ
		*/
		virtual	int				GetLocalTime(TIME_TYPE timeType) VPURE;


	};

	using SystemEBus = EBus<ISystem>;
}