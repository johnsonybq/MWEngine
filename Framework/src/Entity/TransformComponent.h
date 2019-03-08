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


		// 激活组件
		virtual void			Activate();


		// 停用组件
		virtual void			Deactivate();


		// 设置位置信息
		virtual	void			SetPosition(glm::vec3& pos);


		// 设置位置信息
		virtual	void			SetPositionByXYZ(glm::f32 posx, glm::f32 posy, glm::f32 posz);


		// 设置X轴位置信息
		virtual	void			SetPositionX(glm::f32 posx);


		// 设置Y轴位置信息
		virtual	void			SetPositionY(glm::f32 posy);


		// 设置Y轴位置信息
		virtual	void			SetPositionZ(glm::f32 posz);


		// 获取位置信息
		virtual	glm::vec3&		GetPosition();


		// 获取位置X轴信息
		virtual	glm::f32		GetPositionX();


		// 获取位置Y轴信息
		virtual	glm::f32		GetPositionY();


		// 获取位置Z轴信息
		virtual	glm::f32		GetPositionZ();


		// 设置旋转信息
		virtual	void			SetRotation(glm::vec3& rot);


		// 设置X轴旋转信息
		virtual	void			SetRotationX(glm::f32 rotx);


		// 设置Y轴旋转信息
		virtual	void			SetRotationY(glm::f32 roty);


		// 设置Z轴旋转信息
		virtual	void			SetRotationZ(glm::f32 rotz);



		// 获取旋转信息
		virtual	glm::vec3&		GetRotation();


		// 获取X轴旋转信息
		virtual	glm::f32&		GetRotationX();


		// 获取Y轴旋转信息
		virtual	glm::f32&		GetRotationY();


		// 获取Z轴旋转信息
		virtual	glm::f32&		GetRotationZ();


		// 设置缩放信息
		virtual	void			SetScale(glm::vec3& scale);


		// 设置X轴缩放信息
		virtual	void			SetScaleX(glm::f32& scalex);


		// 设置Y轴缩放信息
		virtual	void			SetScaleY(glm::f32& scaley);


		// 设置Z轴缩放信息
		virtual	void			SetScaleZ(glm::f32& scalez);


		// 获取缩放信息
		virtual	glm::vec3&		GetScale();


		// 获取X轴缩放信息
		virtual	glm::f32&		GetScaleX();


		// 获取Y轴缩放信息
		virtual	glm::f32&		GetScaleY();


		// 获取Z轴缩放信息
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