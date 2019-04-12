#pragma once
#include "GLM\glm.hpp"
#include "Entity\Component.h"
#include "Entity\ITransformComponent.h"
#include "Serialize\ISerializable.h"


namespace Framework
{
	class TransformComponent 
			: public Component
			, public ITransformComponent

	{
		SERIALIZE_DEFAULTREFLECT_CLASS(Framework::TransformComponent);

	public:
		
		TransformComponent();
		
		~TransformComponent();

	public:


		// �������
		virtual void			Activate();


		// ͣ�����
		virtual void			Deactivate();


		// ����λ����Ϣ
		virtual	void			SetPosition(Core::vec3& pos);


		// ����λ����Ϣ
		virtual	void			SetPositionByXYZ(Core::f32 posx, Core::f32 posy, Core::f32 posz);


		// ����X��λ����Ϣ
		virtual	void			SetPositionX(Core::f32 posx);


		// ����Y��λ����Ϣ
		virtual	void			SetPositionY(Core::f32 posy);


		// ����Y��λ����Ϣ
		virtual	void			SetPositionZ(Core::f32 posz);


		// ��ȡλ����Ϣ
		virtual	Core::vec3&		GetPosition();


		// ��ȡλ��X����Ϣ
		virtual	Core::f32		GetPositionX();


		// ��ȡλ��Y����Ϣ
		virtual	Core::f32		GetPositionY();


		// ��ȡλ��Z����Ϣ
		virtual	Core::f32		GetPositionZ();


		// ������ת��Ϣ
		virtual	void			SetRotation(Core::vec3& rot);


		// ����X����ת��Ϣ
		virtual	void			SetRotationX(Core::f32 rotx);


		// ����Y����ת��Ϣ
		virtual	void			SetRotationY(Core::f32 roty);


		// ����Z����ת��Ϣ
		virtual	void			SetRotationZ(Core::f32 rotz);



		// ��ȡ��ת��Ϣ
		virtual	Core::vec3&		GetRotation();


		// ��ȡX����ת��Ϣ
		virtual	Core::f32&		GetRotationX();


		// ��ȡY����ת��Ϣ
		virtual	Core::f32&		GetRotationY();


		// ��ȡZ����ת��Ϣ
		virtual	Core::f32&		GetRotationZ();


		// ����������Ϣ
		virtual	void			SetScale(Core::vec3& scale);


		// ����X��������Ϣ
		virtual	void			SetScaleX(Core::f32& scalex);


		// ����Y��������Ϣ
		virtual	void			SetScaleY(Core::f32& scaley);


		// ����Z��������Ϣ
		virtual	void			SetScaleZ(Core::f32& scalez);


		// ��ȡ������Ϣ
		virtual	Core::vec3&		GetScale();


		// ��ȡX��������Ϣ
		virtual	Core::f32&		GetScaleX();


		// ��ȡY��������Ϣ
		virtual	Core::f32&		GetScaleY();


		// ��ȡZ��������Ϣ
		virtual	Core::f32&		GetScaleZ();


	private:


		void					UpdateMatrix();


	private:

		Core::mat4				m_matrix;

		Core::vec3				m_position;
		Core::vec3				m_rotation;
		Core::vec3				m_scale;

	};

}