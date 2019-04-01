/************************************************************************/
/*
文件名: ISerialize.h
描  述: 序列化管理器接口
日  期: 27/03/2019
作  者: MibuWolf
版	本: 1.0
备  注:
*/
/************************************************************************/
#pragma once
#include "EBus\EBus.h"
#include "ISerializable.h"
#include "SerializeClass.h"
#include "ByteArray\ByteArray.h"



namespace Core
{
	class  ISerialize
	{
	public:



		/**
		@breif		初始化

		@param		[OUT]
		return 		加载成功/失败
		*/
		virtual	bool						Initialize() PURE;


		/**
		@breif		类文件描述

		@param		[OUT]
		return 		返回序列化类
		*/
		template<class T>
		SerializeClass*						Class() { return nullptr; };



		/**
		@breif		序列化到二级制

		@param		[OUT]
		return 		返回序列化类
		*/
		virtual	ByteArray*					ToByteArray(ISerializable* pSerializable, ByteArray* bytes = nullptr) PURE;



		/**
		@breif		反序列化二进制

		@param		[OUT]
		return 		返回序列化类
		*/
		virtual	ISerializable* 				FromByteArray(ByteArray* bytes) PURE;



	};

}