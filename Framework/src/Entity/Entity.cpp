#include "Entity\Entity.h"
#include "TransformComponent.h"

namespace Framework
{

	Entity::Entity()
		:m_curComponentID(0)
	{
	
		m_entityID = INVALID_UID;
		m_name = "";
		
		TransformComponent* pTransform = new TransformComponent();
		AddComponent(pTransform);
	}

	Entity::Entity(EntityID & id, std::string name)
		:m_curComponentID(0)
	{
		m_entityID = id;
		m_name = name;

		TransformComponent* pTransform = new TransformComponent();
		AddComponent(pTransform);
	}

	Entity::~Entity()
	{

	}

	EntityID & Entity::GetEntityID()
	{
		return m_entityID;
	}

	ComponentID Entity::AddComponent(Component * pComponent)
	{
		if (pComponent == nullptr)
			return INVALID_UID;

		pComponent->Initialization();
		pComponent->SetEntityID(m_entityID);
		pComponent->SetComponentID(m_curComponentID);
		m_components.insert(std::make_pair(m_curComponentID, pComponent));

		return m_curComponentID++;
	}

	void Entity::RemoveComponent(ComponentID id)
	{
		ComponentMap::iterator itor = m_components.find(id);

		if (itor == m_components.end())
			return;

		m_components.erase(itor);
	}

	void Entity::RemoveComponent(Component * pComponent)
	{
		if (pComponent == nullptr)
			return;

		RemoveComponent(pComponent->GetComponentID());
	}

	void Entity::Activate()
	{
		ComponentMap::iterator itor = m_components.begin();

		for (; itor != m_components.end(); ++itor)
		{
			Component * pComponent = itor->second;

			if (pComponent != nullptr)
				pComponent->Activate();

		}
	}

	void Entity::Deactivate()
	{
		ComponentMap::iterator itor = m_components.begin();

		for (; itor != m_components.end(); ++itor)
		{
			Component * pComponent = itor->second;

			if (pComponent != nullptr)
				pComponent->Deactivate();

		}
	}


}
