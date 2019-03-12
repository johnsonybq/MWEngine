/************************************************************************/
/*
�ļ���: FrameworkManager.h
��  ��: ������
��  ��: 14/12/2018
��  ��: Sam
��	��: 1.0
��  ע:
*/
/************************************************************************/
#pragma once
#include "Entity\IEntitySystem.h"
//#include "Asset\IAssetSystem.h"


namespace Framework
{
	class  FrameworkManager
	{
		SINGLETON_IMPLEMENT(FrameworkManager);

	public:
		
		~FrameworkManager();

	public:


		/**
		@breif		��ʼ�����
		*/
		void					Initialization();


		/**
		@breif		��ȡ��Դϵͳ
		*/
		//IAssetSystem*			GetAssetSystem();


		/**
		@breif		��ȡʵ��ϵͳ
		*/
		IEntitySystem*			GetEntitySystem();


		/**
		@breif		���ٿ��
		*/
		void					Destory();


	};
}