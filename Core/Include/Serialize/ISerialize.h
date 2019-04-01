/************************************************************************/
/*
�ļ���: ISerialize.h
��  ��: ���л��������ӿ�
��  ��: 27/03/2019
��  ��: MibuWolf
��	��: 1.0
��  ע:
*/
/************************************************************************/
#pragma once
#include "EBus\EBus.h"
#include "ISerializable.h"
#include "SerializeClass.h"
#include "ByteArray\ByteArray.h"



namespace Core
{
	class  ISerialize
	{
	public:



		/**
		@breif		��ʼ��

		@param		[OUT]
		return 		���سɹ�/ʧ��
		*/
		virtual	bool						Initialize() PURE;


		/**
		@breif		���ļ�����

		@param		[OUT]
		return 		�������л���
		*/
		template<class T>
		SerializeClass*						Class() { return nullptr; };



		/**
		@breif		���л���������

		@param		[OUT]
		return 		�������л���
		*/
		virtual	ByteArray*					ToByteArray(ISerializable* pSerializable, ByteArray* bytes = nullptr) PURE;



		/**
		@breif		�����л�������

		@param		[OUT]
		return 		�������л���
		*/
		virtual	ISerializable* 				FromByteArray(ByteArray* bytes) PURE;



	};

}