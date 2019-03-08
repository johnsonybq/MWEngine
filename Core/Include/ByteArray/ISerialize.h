/************************************************************************/
/*
�ļ���: ISerialize.h
��  ��: �������л��ӿ�
��  ��: 16/04/2018
��  ��: Sam
��	��: 1.0
��  ע:
*/
/************************************************************************/

#pragma once
#include "ByteArray.h"


namespace Core
{
	class ITDSerialize
	{

		/**
		@breif		���л�

		@param		[IN]
		bytes		���������л���btyes
		*/
		virtual ByteArray*		toByteArray(ByteArray* bytes) = 0;


		/**
		@breif		�����л�

		@param		[IN]
		bytes		��bytes��ȡ����
		*/
		virtual void			fromByteArray(ByteArray* bytes) = 0;

	};
}
