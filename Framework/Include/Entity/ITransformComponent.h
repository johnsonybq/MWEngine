/************************************************************************/
/*
�ļ���: ITransformComponent.h
��  ��: ��������ӿ�
��  ��: 14/12/2018
��  ��: Sam
��	��: 1.0
��  ע:
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
		@breif		����λ����Ϣ

		@param		[IN]
		pos			λ����Ϣ
		*/
		virtual	void			SetPosition(Core::vec3& pos) PURE;

		
		/**
		@breif		����λ����Ϣ

		@param		[IN]
		posx		λ��X

		@param		[IN]
		posy		λ��Y

		@param		[IN]
		posz		λ��Z
		*/
		virtual	void			SetPositionByXYZ(Core::f32 posx, Core::f32 posy, Core::f32 posz) PURE;


		/**
		@breif		����X��λ����Ϣ

		@param		[IN]
		posx		λ��X
		*/
		virtual	void			SetPositionX(Core::f32 posx) PURE;


		/**
		@breif		����Y��λ����Ϣ

		@param		[IN]
		posy		λ��Y
		*/
		virtual	void			SetPositionY(Core::f32 posy) PURE;


		/**
		@breif		����Y��λ����Ϣ

		@param		[IN]
		posz		λ��Z
		*/
		virtual	void			SetPositionZ(Core::f32 posz) PURE;



		/**
		@breif		��ȡλ����Ϣ

		@param		[Out]
		pos			λ����Ϣ
		*/
		virtual	Core::vec3&		GetPosition() PURE;


		/**
		@breif		��ȡλ��X����Ϣ

		@param		[Out]
		posx			λ����Ϣ
		*/
		virtual	Core::f32		GetPositionX() PURE;


		/**
		@breif		��ȡλ��Y����Ϣ

		@param		[Out]
		posy			λ����Ϣ
		*/
		virtual	Core::f32		GetPositionY() PURE;


		/**
		@breif		��ȡλ��Z����Ϣ

		@param		[Out]
		posz			λ����Ϣ
		*/
		virtual	Core::f32		GetPositionZ() PURE;



		/**
		@breif		������ת��Ϣ

		@param		[IN]
		rot			��ת��Ϣ
		*/
		virtual	void			SetRotation(Core::vec3& rot) PURE;


		/**
		@breif		����X����ת��Ϣ

		@param		[In]
		rotx		��ת��Ϣ
		*/
		virtual	void			SetRotationX(Core::f32 rotx) PURE;


		/**
		@breif		����Y����ת��Ϣ

		@param		[In]
		rot			��ת��Ϣ
		*/
		virtual	void			SetRotationY(Core::f32 roty) PURE;


		/**
		@breif		����Z����ת��Ϣ

		@param		[In]
		rot			��ת��Ϣ
		*/
		virtual	void			SetRotationZ(Core::f32 rotz) PURE;


		/**
		@breif		��ȡ��ת��Ϣ

		@param		[Out]
		rot			��ת��Ϣ
		*/
		virtual	Core::vec3&		GetRotation() PURE;


		/**
		@breif		��ȡX����ת��Ϣ

		@param		[Out]
		rotx		��ת��Ϣ
		*/
		virtual	Core::f32&		GetRotationX() PURE;


		/**
		@breif		��ȡY����ת��Ϣ

		@param		[Out]
		rot			��ת��Ϣ
		*/
		virtual	Core::f32&		GetRotationY() PURE;


		/**
		@breif		��ȡZ����ת��Ϣ

		@param		[Out]
		rot			��ת��Ϣ
		*/
		virtual	Core::f32&		GetRotationZ() PURE;


		
		/**
		@breif		����������Ϣ

		@param		[IN]
		scale		������Ϣ
		*/
		virtual	void			SetScale(Core::vec3& scale) PURE;


		/**
		@breif		����X��������Ϣ

		@param		[IN]
		scale		������Ϣ
		*/
		virtual	void			SetScaleX(Core::f32& scalex) PURE;


		/**
		@breif		����Y��������Ϣ

		@param		[IN]
		scaley		������Ϣ
		*/
		virtual	void			SetScaleY(Core::f32& scaley) PURE;


		/**
		@breif		����Z��������Ϣ

		@param		[IN]
		scalez		������Ϣ
		*/
		virtual	void			SetScaleZ(Core::f32& scalez) PURE;


		/**
		@breif		��ȡ������Ϣ

		@param		[Out]
		scale			������Ϣ
		*/
		virtual	Core::vec3&		GetScale() PURE;


		/**
		@breif		��ȡX��������Ϣ

		@param		[Out]
		scalex		��ת��Ϣ
		*/
		virtual	Core::f32&		GetScaleX() PURE;


		/**
		@breif		��ȡY��������Ϣ

		@param		[Out]
		scaleY		��ת��Ϣ
		*/
		virtual	Core::f32&		GetScaleY() PURE;


		/**
		@breif		��ȡZ��������Ϣ

		@param		[Out]
		scalez		��ת��Ϣ
		*/
		virtual	Core::f32&		GetScaleZ() PURE;




	};

	using TransformEBus = Core::EBus<ITransformComponent>;



	class ITransformNotify
	{
	public:

		/**
		@breif		λ�ø��Ļص�
		*/
		virtual	void			OnPositionChanged() PURE;


		/**
		@breif		������Ļص�
		*/
		virtual	void			OnRotationChanged() PURE;

		/**
		@breif		���Ÿ��Ļص�
		*/
		virtual	void			OnScaleChanged() PURE;
	};

	using TransformNotifyEBus = Core::EBus<ITransformNotify>;

}