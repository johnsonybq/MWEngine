/************************************************************************/
/*
�ļ���: IReflectManager.h
��  ��: ����������ӿ�
��  ��: 26/03/2019
��  ��: MibuWolf
��	��: 1.0
��  ע:
*/
/************************************************************************/

#pragma once
#include "EBus\EBus.h"
#include "IReflectFactory.h"

namespace Core
{
	class IReflectManager
	{
	public:


		/**
		@breif		��ʼ��

		@param		[OUT]
		return 		���سɹ�/ʧ��
		*/
		virtual	bool				Initialize() VPURE;


		/**
		@breif		ע��

		@param		[OUT]
		return 		���سɹ�/ʧ��
		*/
		virtual	bool				Register(const char* className, IReflectFactory* factory) VPURE;


		/**
		@breif		��ȡ���乤��

		@param		[OUT]
		return 		���乤��
		*/
		virtual	IReflectFactory*	GetReflectFactory(const char* className) VPURE;



		/**
		@breif		��ע��

		@param		[OUT]
		return 		���سɹ�/ʧ��
		*/
		virtual	bool				UnRegister(const char* className) VPURE;



	};

	using ReflectionEBus = EBus<IReflectManager>;
}