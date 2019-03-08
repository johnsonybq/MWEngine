/************************************************************************/
/*
文件名: ISerialize.h
描  述: 数据序列化接口
日  期: 16/04/2018
作  者: Sam
版	本: 1.0
备  注:
*/
/************************************************************************/

#pragma once
#include "ByteArray.h"


namespace Core
{
	class ITDSerialize
	{

		/**
		@breif		序列化

		@param		[IN]
		bytes		将数据序列化到btyes
		*/
		virtual ByteArray*		toByteArray(ByteArray* bytes) = 0;


		/**
		@breif		反序列化

		@param		[IN]
		bytes		从bytes读取数据
		*/
		virtual void			fromByteArray(ByteArray* bytes) = 0;

	};
}
