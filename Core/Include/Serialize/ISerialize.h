/************************************************************************/
/*
�ļ���: ISerialize.h
��  ��:	���л��ӿ�
��  ��: 26/03/2019
��  ��: MibuWolf
��	��: 1.0
��  ע:
*/
/************************************************************************/

#pragma once
#include "MWCore.h"

namespace Core
{
	class ISerialize
	{
	public:


		/**
		@breif		������

		@param		[OUT]
		return 		���ض���
		*/
		virtual	void*	CreateClass(const char*) VPURE;



		/**
		@breif		����

		@param		[OUT]
		return 		����
		*/
		virtual	void	DestoryClass(void*) VPURE;


	};

}