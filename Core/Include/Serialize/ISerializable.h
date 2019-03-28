/************************************************************************/
/*
�ļ���: ISerializable.h
��  ��:	�����л��ӿ�
��  ��: 26/03/2019
��  ��: MibuWolf
��	��: 1.0
��  ע:
*/
/************************************************************************/

#pragma once
#include <string>
#include "MWCore.h"
#include "Reflect\IReflectFactory.h"

namespace Core
{
	class ISerializable
	{
	public:


		/**
		@breif		��ȡ���л�����

		@param		[OUT]
		return 		��������
		*/
		virtual const char*				GetSerializeClassName() VPURE;



		/**
		@breif		��ȡ���л��೤��

		@param		[OUT]
		return 		�����೤��
		*/
		virtual	int						GetSerializeClassSize() VPURE;


	};



	// �������л��ͷ���ӿ�
	#define		SERIALIZE_REFLECT_CLASS(ClassName,Factory)					\
public:												\
	virtual	const char* GetSerializeClassName()		{return #ClassName;}	\
	virtual	int GetSerializeClassSize()		{return sizeof(ClassName);}	\
public:												\
	static	const char* __GetClassName__()		{return #ClassName;}	\
public:																		\
	static void	RegisterReflect()	{Core::ReflectionEBus::Broadcast(&Core::IReflectManager::Register, #ClassName, MW_New Factory());}

}



#define		SERIALIZE_DEFAULTREFLECT_CLASS(ClassName)					\
SERIALIZE_REFLECT_CLASS(ClassName,Core::DefaultReflectFactory<ClassName>)