/************************************************************************/
/*
�ļ���: IMemoryManager.h
��  ��: IMemoryManager�ӿ�
��  ��: 12/04/2019
��  ��: MibuWolf
��	��: 1.0
��  ע:
*/
/************************************************************************/

#pragma once
#include "EBus\EBus.h"

namespace Core
{
	class IMemoryManager
	{
	public:


		/**
		@breif		��ʼ��

		@param		[OUT]
		return 		���سɹ�/ʧ��
		*/
		virtual	bool	Initialize() VPURE;


		
		/**
		@breif		�����ڴ�

		@param		[OUT]
		return 		������ڴ��ַ
		*/
		virtual void*		Allocation(size_t nSize, const char* pFile, int nLine) VPURE;



		/**
		@breif		�ͷ��ڴ�

		@param		[OUT]
		return 		������ڴ��ַ
		*/
		virtual void		Retrieve(void* pPtr) VPURE;

	};

	using MemoryEBus = EBus<IMemoryManager>;
}