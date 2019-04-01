/************************************************************************/
/*
�ļ���: ILog.h
��  ��: Log�ӿ�
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
	class ILog
	{
	public:


		/**
		@breif		��ʼ��

		@param		[OUT]
		return 		���سɹ�/ʧ��
		*/
		virtual	bool	Initialize() PURE;


		/**
		@breif		�����־(������ȼ�)

		@param		[IN]
		msg			��־����
		*/
		virtual	void	Log(const char* path, ...) PURE;



		/**
		@breif		�������

		@param		[IN]
		msg			��־����
		*/
		virtual	void	Warning(const char* path, ...) PURE;



		/**
		@breif		�������

		@param		[IN]
		msg			��־����
		*/
		virtual	void	Error(const char* path, ...) PURE;


		/**
		@breif		д��Log�ļ�

		@param		[IN]
		msg			��־����
		*/
		virtual	void	LogToFile(const char* path, ...) PURE;


		/**
		@breif		��Log�ļ�

		@param		[IN]
		path		��־��ַ
		*/
		virtual	void	OpenLogFile(const char* path) PURE;


		/**
		@breif		�ر�Log�ļ�
		*/
		virtual	void	CloseLogFile(const char* path) PURE;


	};

	using LogEBus = EBus<ILog>;
}