/************************************************************************/
/*
�ļ���: CoreManager.h
��  ��: ���Ŀ����
��  ��: 14/12/2018
��  ��: Sam
��	��: 1.0
��  ע:
*/
/************************************************************************/
#pragma once
#include "IMiscellaneous.h"

namespace Core
{
	class  CoreManager
	{
		SINGLETON_IMPLEMENT(CoreManager);

	public:
		
		~CoreManager();

	public:


		/**
		@breif		��ʼ�����
		*/
		void					Initialization();


		/**
		@breif		���ٿ��
		*/
		void					Destory();


	};
}