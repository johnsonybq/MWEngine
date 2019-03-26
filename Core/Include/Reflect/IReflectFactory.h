/************************************************************************/
/*
�ļ���: IReflectFactory.h
��  ��: ���乤������ӿ�
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
	class IReflectFactory
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



	template<typename Class>
	class DefaultReflectFactory : public IReflectFactory
	{
	public:


		DefaultReflectFactory() {};

		~DefaultReflectFactory() {};

	public:


		// ����
		virtual	void*	CreateClass(const char* className)
		{
			return MW_New Class();
		}


		// ����
		virtual void	DestoryClass(void* pClass)
		{
			if (pClass != nullptr)
				MW_Delete pClass��
		}
	};

}