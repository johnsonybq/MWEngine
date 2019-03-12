#pragma once

namespace Core
{
	class IModuleManager
	{
	public:

		
		/**
		@breif		���ص���ģ��

		@param		[IN]
		path		ģ���ַ

		@param		[OUT]
		return 		���سɹ�/ʧ��
		*/
		virtual	bool	LoadModule(const char* path) PURE_VIRTUAL;



		/**
		@breif		ͨ�����ü���ģ���б�

		@param		[IN]
		config		���õ�ַ

		@param		[OUT]
		return 		���سɹ�/ʧ��
		*/
		virtual	bool	LoadAllModules(const char* path) PURE_VIRTUAL;



		/**
		@breif		�ж�ģ���Ƿ񱻼���

		@param		[IN]
		path		ģ���ַ

		@param		[OUT]
		return 		�Ƿ��Ѿ����ظ�ģ��
		*/
		virtual	bool	IsLoadModule(const char* path) PURE_VIRTUAL;


		/**
		@breif		�Ƴ�����ģ��

		@param		[IN]
		path		ģ���ַ

		@param		[OUT]
		return 		�Ƴ��ɹ�/ʧ��
		*/
		virtual	bool	RemoveModule(const char* path) PURE_VIRTUAL;


		/**
		@breif		�Ƴ�����ģ��

		@param		[OUT]
		return 		�Ƴ��ɹ�/ʧ��
		*/
		virtual	bool	RemoveAllModules() PURE_VIRTUAL;


	};
}