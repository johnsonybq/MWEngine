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
		virtual	void			SetPosition(glm::vec3& pos) PURE;

		
		/**
		@breif		����λ����Ϣ

		@param		[IN]
		posx		λ��X

		@param		[IN]
		posy		λ��Y

		@param		[IN]
		posz		λ��Z
		*/
		virtual	void			SetPositionByXYZ(glm::f32 posx, glm::f32 posy, glm::f32 posz) PURE;


		/**
		@breif		����X��λ����Ϣ

		@param		[IN]
		posx		λ��X
		*/
		virtual	void			SetPositionX(glm::f32 posx) PURE;


		/**
		@breif		����Y��λ����Ϣ

		@param		[IN]
		posy		λ��Y
		*/
		virtual	void			SetPositionY(glm::f32 posy) PURE;


		/**
		@breif		����Y��λ����Ϣ

		@param		[IN]
		posz		λ��Z
		*/
		virtual	void			SetPositionZ(glm::f32 posz) PURE;



		/**
		@breif		��ȡλ����Ϣ

		@param		[Out]
		pos			λ����Ϣ
		*/
		virtual	glm::vec3&		GetPosition() PURE;


		/**
		@breif		��ȡλ��X����Ϣ

		@param		[Out]
		posx			λ����Ϣ
		*/
		virtual	glm::f32		GetPositionX() PURE;


		/**
		@breif		��ȡλ��Y����Ϣ

		@param		[Out]
		posy			λ����Ϣ
		*/
		virtual	glm::f32		GetPositionY() PURE;


		/**
		@breif		��ȡλ��Z����Ϣ

		@param		[Out]
		posz			λ����Ϣ
		*/
		virtual	glm::f32		GetPositionZ() PURE;



		/**
		@breif		������ת��Ϣ

		@param		[IN]
		rot			��ת��Ϣ
		*/
		virtual	void			SetRotation(glm::vec3& rot) PURE;


		/**
		@breif		����X����ת��Ϣ

		@param		[In]
		rotx		��ת��Ϣ
		*/
		virtual	void			SetRotationX(glm::f32 rotx) PURE;


		/**
		@breif		����Y����ת��Ϣ

		@param		[In]
		rot			��ת��Ϣ
		*/
		virtual	void			SetRotationY(glm::f32 roty) PURE;


		/**
		@breif		����Z����ת��Ϣ

		@param		[In]
		rot			��ת��Ϣ
		*/
		virtual	void			SetRotationZ(glm::f32 rotz) PURE;


		/**
		@breif		��ȡ��ת��Ϣ

		@param		[Out]
		rot			��ת��Ϣ
		*/
		virtual	glm::vec3&		GetRotation() PURE;


		/**
		@breif		��ȡX����ת��Ϣ

		@param		[Out]
		rotx		��ת��Ϣ
		*/
		virtual	glm::f32&		GetRotationX() PURE;


		/**
		@breif		��ȡY����ת��Ϣ

		@param		[Out]
		rot			��ת��Ϣ
		*/
		virtual	glm::f32&		GetRotationY() PURE;


		/**
		@breif		��ȡZ����ת��Ϣ

		@param		[Out]
		rot			��ת��Ϣ
		*/
		virtual	glm::f32&		GetRotationZ() PURE;


		
		/**
		@breif		����������Ϣ

		@param		[IN]
		scale		������Ϣ
		*/
		virtual	void			SetScale(glm::vec3& scale) PURE;


		/**
		@breif		����X��������Ϣ

		@param		[IN]
		scale		������Ϣ
		*/
		virtual	void			SetScaleX(glm::f32& scalex) PURE;


		/**
		@breif		����Y��������Ϣ

		@param		[IN]
		scaley		������Ϣ
		*/
		virtual	void			SetScaleY(glm::f32& scaley) PURE;


		/**
		@breif		����Z��������Ϣ

		@param		[IN]
		scalez		������Ϣ
		*/
		virtual	void			SetScaleZ(glm::f32& scalez) PURE;


		/**
		@breif		��ȡ������Ϣ

		@param		[Out]
		scale			������Ϣ
		*/
		virtual	glm::vec3&		GetScale() PURE;


		/**
		@breif		��ȡX��������Ϣ

		@param		[Out]
		scalex		��ת��Ϣ
		*/
		virtual	glm::f32&		GetScaleX() PURE;


		/**
		@breif		��ȡY��������Ϣ

		@param		[Out]
		scaleY		��ת��Ϣ
		*/
		virtual	glm::f32&		GetScaleY() PURE;


		/**
		@breif		��ȡZ��������Ϣ

		@param		[Out]
		scalez		��ת��Ϣ
		*/
		virtual	glm::f32&		GetScaleZ() PURE;




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