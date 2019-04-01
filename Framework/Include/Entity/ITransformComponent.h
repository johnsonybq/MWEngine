/************************************************************************/
/*
文件名: ITransformComponent.h
描  述: 矩阵组件接口
日  期: 14/12/2018
作  者: Sam
版	本: 1.0
备  注:
*/
/************************************************************************/
#pragma once
#include <glm/glm.hpp>
#include "EBus\EBus.h"

namespace Framework
{
	class ITransformComponent
	{
	public:


		/**
		@breif		设置位置信息

		@param		[IN]
		pos			位置信息
		*/
		virtual	void			SetPosition(glm::vec3& pos) PURE;

		
		/**
		@breif		设置位置信息

		@param		[IN]
		posx		位置X

		@param		[IN]
		posy		位置Y

		@param		[IN]
		posz		位置Z
		*/
		virtual	void			SetPositionByXYZ(glm::f32 posx, glm::f32 posy, glm::f32 posz) PURE;


		/**
		@breif		设置X轴位置信息

		@param		[IN]
		posx		位置X
		*/
		virtual	void			SetPositionX(glm::f32 posx) PURE;


		/**
		@breif		设置Y轴位置信息

		@param		[IN]
		posy		位置Y
		*/
		virtual	void			SetPositionY(glm::f32 posy) PURE;


		/**
		@breif		设置Y轴位置信息

		@param		[IN]
		posz		位置Z
		*/
		virtual	void			SetPositionZ(glm::f32 posz) PURE;



		/**
		@breif		获取位置信息

		@param		[Out]
		pos			位置信息
		*/
		virtual	glm::vec3&		GetPosition() PURE;


		/**
		@breif		获取位置X轴信息

		@param		[Out]
		posx			位置信息
		*/
		virtual	glm::f32		GetPositionX() PURE;


		/**
		@breif		获取位置Y轴信息

		@param		[Out]
		posy			位置信息
		*/
		virtual	glm::f32		GetPositionY() PURE;


		/**
		@breif		获取位置Z轴信息

		@param		[Out]
		posz			位置信息
		*/
		virtual	glm::f32		GetPositionZ() PURE;



		/**
		@breif		设置旋转信息

		@param		[IN]
		rot			旋转信息
		*/
		virtual	void			SetRotation(glm::vec3& rot) PURE;


		/**
		@breif		设置X轴旋转信息

		@param		[In]
		rotx		旋转信息
		*/
		virtual	void			SetRotationX(glm::f32 rotx) PURE;


		/**
		@breif		设置Y轴旋转信息

		@param		[In]
		rot			旋转信息
		*/
		virtual	void			SetRotationY(glm::f32 roty) PURE;


		/**
		@breif		设置Z轴旋转信息

		@param		[In]
		rot			旋转信息
		*/
		virtual	void			SetRotationZ(glm::f32 rotz) PURE;


		/**
		@breif		获取旋转信息

		@param		[Out]
		rot			旋转信息
		*/
		virtual	glm::vec3&		GetRotation() PURE;


		/**
		@breif		获取X轴旋转信息

		@param		[Out]
		rotx		旋转信息
		*/
		virtual	glm::f32&		GetRotationX() PURE;


		/**
		@breif		获取Y轴旋转信息

		@param		[Out]
		rot			旋转信息
		*/
		virtual	glm::f32&		GetRotationY() PURE;


		/**
		@breif		获取Z轴旋转信息

		@param		[Out]
		rot			旋转信息
		*/
		virtual	glm::f32&		GetRotationZ() PURE;


		
		/**
		@breif		设置缩放信息

		@param		[IN]
		scale		缩放信息
		*/
		virtual	void			SetScale(glm::vec3& scale) PURE;


		/**
		@breif		设置X轴缩放信息

		@param		[IN]
		scale		缩放信息
		*/
		virtual	void			SetScaleX(glm::f32& scalex) PURE;


		/**
		@breif		设置Y轴缩放信息

		@param		[IN]
		scaley		缩放信息
		*/
		virtual	void			SetScaleY(glm::f32& scaley) PURE;


		/**
		@breif		设置Z轴缩放信息

		@param		[IN]
		scalez		缩放信息
		*/
		virtual	void			SetScaleZ(glm::f32& scalez) PURE;


		/**
		@breif		获取缩放信息

		@param		[Out]
		scale			缩放信息
		*/
		virtual	glm::vec3&		GetScale() PURE;


		/**
		@breif		获取X轴缩放信息

		@param		[Out]
		scalex		旋转信息
		*/
		virtual	glm::f32&		GetScaleX() PURE;


		/**
		@breif		获取Y轴缩放信息

		@param		[Out]
		scaleY		旋转信息
		*/
		virtual	glm::f32&		GetScaleY() PURE;


		/**
		@breif		获取Z轴缩放信息

		@param		[Out]
		scalez		旋转信息
		*/
		virtual	glm::f32&		GetScaleZ() PURE;




	};

	using TransformEBus = Core::EBus<ITransformComponent>;



	class ITransformNotify
	{
	public:

		/**
		@breif		位置更改回调
		*/
		virtual	void			OnPositionChanged() PURE;


		/**
		@breif		朝向更改回调
		*/
		virtual	void			OnRotationChanged() PURE;

		/**
		@breif		缩放更改回调
		*/
		virtual	void			OnScaleChanged() PURE;
	};

	using TransformNotifyEBus = Core::EBus<ITransformNotify>;

}