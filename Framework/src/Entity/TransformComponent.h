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


		// 激活组件
		virtual void			Activate();


		// 停用组件
		virtual void			Deactivate();


		// 设置位置信息
		virtual	void			SetPosition(Core::vec3& pos);


		// 设置位置信息
		virtual	void			SetPositionByXYZ(Core::f32 posx, Core::f32 posy, Core::f32 posz);


		// 设置X轴位置信息
		virtual	void			SetPositionX(Core::f32 posx);


		// 设置Y轴位置信息
		virtual	void			SetPositionY(Core::f32 posy);


		// 设置Y轴位置信息
		virtual	void			SetPositionZ(Core::f32 posz);


		// 获取位置信息
		virtual	Core::vec3&		GetPosition();


		// 获取位置X轴信息
		virtual	Core::f32		GetPositionX();


		// 获取位置Y轴信息
		virtual	Core::f32		GetPositionY();


		// 获取位置Z轴信息
		virtual	Core::f32		GetPositionZ();


		// 设置旋转信息
		virtual	void			SetRotation(Core::vec3& rot);


		// 设置X轴旋转信息
		virtual	void			SetRotationX(Core::f32 rotx);


		// 设置Y轴旋转信息
		virtual	void			SetRotationY(Core::f32 roty);


		// 设置Z轴旋转信息
		virtual	void			SetRotationZ(Core::f32 rotz);



		// 获取旋转信息
		virtual	Core::vec3&		GetRotation();


		// 获取X轴旋转信息
		virtual	Core::f32&		GetRotationX();


		// 获取Y轴旋转信息
		virtual	Core::f32&		GetRotationY();


		// 获取Z轴旋转信息
		virtual	Core::f32&		GetRotationZ();


		// 设置缩放信息
		virtual	void			SetScale(Core::vec3& scale);


		// 设置X轴缩放信息
		virtual	void			SetScaleX(Core::f32& scalex);


		// 设置Y轴缩放信息
		virtual	void			SetScaleY(Core::f32& scaley);


		// 设置Z轴缩放信息
		virtual	void			SetScaleZ(Core::f32& scalez);


		// 获取缩放信息
		virtual	Core::vec3&		GetScale();


		// 获取X轴缩放信息
		virtual	Core::f32&		GetScaleX();


		// 获取Y轴缩放信息
		virtual	Core::f32&		GetScaleY();


		// 获取Z轴缩放信息
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