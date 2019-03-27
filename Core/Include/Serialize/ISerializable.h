/************************************************************************/
/*
文件名: ISerializable.h
描  述:	可序列化接口
日  期: 26/03/2019
作  者: MibuWolf
版	本: 1.0
备  注:
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
		@breif		获取序列化类名

		@param		[OUT]
		return 		返回类名
		*/
		const char*				GetSerializeClassName()
		{
			return nullptr;
		}


	};



	// 定义序列化和反射接口
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