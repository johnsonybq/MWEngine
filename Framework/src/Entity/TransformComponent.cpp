#include <glm/ext/matrix_transform.hpp>
#include "TransformComponent.h"

namespace Framework
{

	TransformComponent::TransformComponent()
	{
		m_position = glm::vec3(0.0, 0.0, 0.0);
		m_rotation = glm::vec3(0.0, 0.0, 0.0);
		m_scale = glm::vec3(1.0, 1.0, 1.0);
		m_matrix = glm::mat4(1.0);
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

	void TransformComponent::SetPosition(glm::vec3 & pos)
	{
		m_position = pos;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnPositionChanged);
	}

	void TransformComponent::SetPositionByXYZ(glm::f32 posx, glm::f32 posy, glm::f32 posz)
	{
		m_position.x = posx;
		m_position.y = posy;
		m_position.z = posz;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnPositionChanged);
	}

	void TransformComponent::SetPositionX(glm::f32 posx)
	{
		m_position.x = posx;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnPositionChanged);
	}

	void TransformComponent::SetPositionY(glm::f32 posy)
	{
		m_position.y = posy;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnPositionChanged);
	}

	void TransformComponent::SetPositionZ(glm::f32 posz)
	{
		m_position.z = posz;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnPositionChanged);
	}

	glm::vec3 & TransformComponent::GetPosition()
	{
		return m_position;
	}

	glm::f32 TransformComponent::GetPositionX()
	{
		return m_position.x;
	}

	glm::f32 TransformComponent::GetPositionY()
	{
		return m_position.y;
	}

	glm::f32 TransformComponent::GetPositionZ()
	{
		return m_position.z;
	}

	void TransformComponent::SetRotation(glm::vec3 & rot)
	{
		m_rotation = rot;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetRotationX(glm::f32 rotx)
	{
		m_rotation.x = rotx;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetRotationY(glm::f32 roty)
	{
		m_rotation.y = roty;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetRotationZ(glm::f32 rotz)
	{
		m_rotation.z = rotz;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	glm::vec3 & TransformComponent::GetRotation()
	{
		return m_rotation;
	}

	glm::f32 & TransformComponent::GetRotationX()
	{
		return m_rotation.x;
	}

	glm::f32 & TransformComponent::GetRotationY()
	{
		return m_rotation.y;
	}

	glm::f32 & TransformComponent::GetRotationZ()
	{
		return m_rotation.z;
	}

	void TransformComponent::SetScale(glm::vec3 & scale)
	{
		m_scale = scale;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetScaleX(glm::f32 & scalex)
	{
		m_scale.x = scalex;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetScaleY(glm::f32 & scaley)
	{
		m_scale.y = scaley;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	void TransformComponent::SetScaleZ(glm::f32 & scalez)
	{
		m_scale.z = scalez;

		UpdateMatrix();

		TransformNotifyEBus::Event(GetEntityID(), &ITransformNotify::OnRotationChanged);
	}

	glm::vec3 & TransformComponent::GetScale()
	{
		return m_scale;
	}

	glm::f32 & TransformComponent::GetScaleX()
	{
		return m_scale.x;
	}

	glm::f32 & TransformComponent::GetScaleY()
	{
		return m_scale.y;
	}

	glm::f32 & TransformComponent::GetScaleZ()
	{
		return m_scale.z;
	}

	void TransformComponent::UpdateMatrix()
	{
		m_matrix = glm::mat4(1.0);
		m_matrix = glm::rotate(m_matrix, m_rotation.x, glm::vec3(1, 0, 0));
		m_matrix = glm::rotate(m_matrix, m_rotation.y, glm::vec3(0, 1, 0));
		m_matrix = glm::rotate(m_matrix, m_rotation.z, glm::vec3(0, 0, 1));
		m_matrix = glm::scale(m_matrix,m_scale);
		m_matrix = glm::translate(m_matrix,m_position);
	}

}
