#include "Entity\Component.h"


namespace Framework
{

	Component::Component()
		:m_entityID(INVALID_UUID), m_componentID(INVALID_UUID)
	{
		
	}

	Component::~Component()
	{

	}

	void Component::SetComponentID(ComponentID & id)
	{
		m_componentID = id;
	}

	ComponentID Component::GetComponentID()
	{
		return m_componentID;
	}

	void Component::SetEntityID(EntityID & id)
	{
		m_entityID = id;
	}

	EntityID Component::GetEntityID()
	{
		return m_entityID;
	}

	void Component::Initialization()
	{
	}



}