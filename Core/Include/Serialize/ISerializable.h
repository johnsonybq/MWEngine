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
		const char*				GetSerializeClassName()
		{
			return nullptr;
		}


	};



	// �������л��ͷ���ӿ�
	#define		SERIALIZE_REFLECT_CLASS(ClassName,Factory)					\
public:												\
	virtual	const char* GetSerializeClassName()		{return #ClassName;}	\
public:												\
	static	const char* __GetClassName__()		{return #ClassName;}	\
public:																		\
	static void	RegisterReflect()	{Core::ReflectionEBus::Broadcast(&Core::IReflectManager::Register, #ClassName, MW_New Factory());}

}



#define		SERIALIZE_DEFAULTREFLECT_CLASS(ClassName)					\
SERIALIZE_REFLECT_CLASS(ClassName,Core::DefaultReflectFactory<ClassName>)