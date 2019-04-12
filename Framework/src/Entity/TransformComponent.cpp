#include <glm/ext/matrix_transform.hpp>
#include "TransformComponent.h"
#include "Serialize\ISerialize.h"

namespace Framework
{

	TransformComponent::TransformComponent()
	{
		m_position = Core::vec3(0.0, 0.0, 0.0);
		m_rotation = Core::vec3(0.0, 0.0, 0.0);
		m_scale = Core::vec3(1.0, 1.0, 1.0);
		m_matrix = Core::mat4(1.0);
	}

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::Activate()
	{
		Framework::EntityID entityID = GetEntityID();
		TransformEBus::BusConnect(entityID, this);
	}

	void TransformComponent::Deactivate()
	{
		Framework::EntityID entityID = GetEntityID();
		TransformEBus::BusDisconnect(entityID, this);
	}


	void TransformComponent::SerializeReflect()
	{
		Core::SerializeClass* pSerialize = nullptr;
		Core::SerializeEBus::BroadcastResult(pSerialize, &Core::ISerialize::Class<Framework::TransformComponent>);

		if (pSerialize != nullptr)
		{

		}
	}

	void TransformComponent::SetPosition(Core::vec3 & pos)
	{
		m_position = pos;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnPositionChanged);
	}

	void TransformComponent::SetPositionByXYZ(Core::f32 posx, Core::f32 posy, Core::f32 posz)
	{
		m_position.x = posx;
		m_position.y = posy;
		m_position.z = posz;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnPositionChanged);
	}

	void TransformComponent::SetPositionX(Core::f32 posx)
	{
		m_position.x = posx;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnPositionChanged);
	}

	void TransformComponent::SetPositionY(Core::f32 posy)
	{
		m_position.y = posy;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnPositionChanged);
	}

	void TransformComponent::SetPositionZ(Core::f32 posz)
	{
		m_position.z = posz;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnPositionChanged);
	}

	Core::vec3 & TransformComponent::GetPosition()
	{
		return m_position;
	}

	Core::f32 TransformComponent::GetPositionX()
	{
		return m_position.x;
	}

	Core::f32 TransformComponent::GetPositionY()
	{
		return m_position.y;
	}

	Core::f32 TransformComponent::GetPositionZ()
	{
		return m_position.z;
	}

	void TransformComponent::SetRotation(Core::vec3 & rot)
	{
		m_rotation = rot;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetRotationX(Core::f32 rotx)
	{
		m_rotation.x = rotx;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetRotationY(Core::f32 roty)
	{
		m_rotation.y = roty;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetRotationZ(Core::f32 rotz)
	{
		m_rotation.z = rotz;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	Core::vec3 & TransformComponent::GetRotation()
	{
		return m_rotation;
	}

	Core::f32 & TransformComponent::GetRotationX()
	{
		return m_rotation.x;
	}

	Core::f32 & TransformComponent::GetRotationY()
	{
		return m_rotation.y;
	}

	Core::f32 & TransformComponent::GetRotationZ()
	{
		return m_rotation.z;
	}

	void TransformComponent::SetScale(Core::vec3 & scale)
	{
		m_scale = scale;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetScaleX(Core::f32 & scalex)
	{
		m_scale.x = scalex;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetScaleY(Core::f32 & scaley)
	{
		m_scale.y = scaley;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetScaleZ(Core::f32 & scalez)
	{
		m_scale.z = scalez;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	Core::vec3 & TransformComponent::GetScale()
	{
		return m_scale;
	}

	Core::f32 & TransformComponent::GetScaleX()
	{
		return m_scale.x;
	}

	Core::f32 & TransformComponent::GetScaleY()
	{
		return m_scale.y;
	}

	Core::f32 & TransformComponent::GetScaleZ()
	{
		return m_scale.z;
	}

	void TransformComponent::UpdateMatrix()
	{
		m_matrix = Core::mat4(1.0);
		m_matrix = Core::rotate(m_matrix, m_rotation.x, Core::vec3(1, 0, 0));
		m_matrix = Core::rotate(m_matrix, m_rotation.y, Core::vec3(0, 1, 0));
		m_matrix = Core::rotate(m_matrix, m_rotation.z, Core::vec3(0, 0, 1));
		m_matrix = Core::scale(m_matrix,m_scale);
		m_matrix = Core::translate(m_matrix,m_position);
	}

}
