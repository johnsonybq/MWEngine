/************************************************************************/
/*
�ļ���: IFramework.h
��  ��: ��ܽӿ�
��  ��: 01/04/2019
��  ��: MibuWolf
��	��: 1.0
��  ע:
*/
/************************************************************************/
#pragma once
#include "MWCore.h"


namespace Framework
{
	class IFramework
	{
	public:


		/**
		@breif		��ʼ��

		@param		[OUT]
		return 		���سɹ�/ʧ��
		*/
		virtual	bool	Initialize() PURE;


	};
}