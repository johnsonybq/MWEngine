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
		virtual	bool	Initialize() = 0;


		/**
		@breif		�����ڴ�

		@param		[OUT]
		return 		������ڴ��ַ
		*/
		virtual void*		Allocation(size_t nSize, const char* pFile, int nLine) = 0;



		/**
		@breif		�ͷ��ڴ�

		@param		[OUT]
		return 		������ڴ��ַ
		*/
		virtual void		Retrieve(void* pPtr) = 0;

	};

	using MemoryEBus = Core::EBus<IMemoryManager>;
}
