/************************************************************************/
/*
�ļ���: ISystem.h
��  ��: ����ϵͳ������Ļ���
��  ��: 18/12/2018
��  ��: Sam
��	��: 1.0
��  ע:
*/
/************************************************************************/
#pragma once
#include "IMiscellaneous.h"


namespace Framework
{
	class ISystem
	{
	public:


		/**
		@breif		��ʼ��
		*/
		virtual	void				Initialization() PURE;


		/**
		@breif		����
		*/
		virtual	void				Destory() PURE;


	};
}