#pragma once
#include "GLM\glm.hpp"
#include "Entity\Component.h"
#include "Entity\ITransformComponent.h"

namespace Framework
{
	class TransformComponent 
			: public Component
			, public ITransformComponent

	{
	public:
		
		TransformComponent();
		
		~TransformComponent();

	public:


		// �������
		virtual void			Activate();


		// ͣ�����
		virtual void			Deactivate();


		// ����λ����Ϣ
		virtual	void			SetPosition(glm::vec3& pos);


		// ����λ����Ϣ
		virtual	void			SetPositionByXYZ(glm::f32 posx, glm::f32 posy, glm::f32 posz);


		// ����X��λ����Ϣ
		virtual	void			SetPositionX(glm::f32 posx);


		// ����Y��λ����Ϣ
		virtual	void			SetPositionY(glm::f32 posy);


		// ����Y��λ����Ϣ
		virtual	void			SetPositionZ(glm::f32 posz);


		// ��ȡλ����Ϣ
		virtual	glm::vec3&		GetPosition();


		// ��ȡλ��X����Ϣ
		virtual	glm::f32		GetPositionX();


		// ��ȡλ��Y����Ϣ
		virtual	glm::f32		GetPositionY();


		// ��ȡλ��Z����Ϣ
		virtual	glm::f32		GetPositionZ();


		// ������ת��Ϣ
		virtual	void			SetRotation(glm::vec3& rot);


		// ����X����ת��Ϣ
		virtual	void			SetRotationX(glm::f32 rotx);


		// ����Y����ת��Ϣ
		virtual	void			SetRotationY(glm::f32 roty);


		// ����Z����ת��Ϣ
		virtual	void			SetRotationZ(glm::f32 rotz);



		// ��ȡ��ת��Ϣ
		virtual	glm::vec3&		GetRotation();


		// ��ȡX����ת��Ϣ
		virtual	glm::f32&		GetRotationX();


		// ��ȡY����ת��Ϣ
		virtual	glm::f32&		GetRotationY();


		// ��ȡZ����ת��Ϣ
		virtual	glm::f32&		GetRotationZ();


		// ����������Ϣ
		virtual	void			SetScale(glm::vec3& scale);


		// ����X��������Ϣ
		virtual	void			SetScaleX(glm::f32& scalex);


		// ����Y��������Ϣ
		virtual	void			SetScaleY(glm::f32& scaley);


		// ����Z��������Ϣ
		virtual	void			SetScaleZ(glm::f32& scalez);


		// ��ȡ������Ϣ
		virtual	glm::vec3&		GetScale();


		// ��ȡX��������Ϣ
		virtual	glm::f32&		GetScaleX();


		// ��ȡY��������Ϣ
		virtual	glm::f32&		GetScaleY();


		// ��ȡZ��������Ϣ
		virtual	glm::f32&		GetScaleZ();


	private:


		void					UpdateMatrix();


	private:

		glm::mat4				m_matrix;

		glm::vec3				m_position;
		glm::vec3				m_rotation;
		glm::vec3				m_scale;

	};

}