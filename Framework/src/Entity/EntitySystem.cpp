#include "EntitySystem.h"


namespace Framework
{

	EntitySystem::EntitySystem()
		:m_curEntityID(0)
	{

	}


	EntitySystem::~EntitySystem()
	{

	}


	void EntitySystem::Initialization()
	{
		EntityEBus::BusConnect(this);
	}

	EntityID EntitySystem::CreateEntity(std::string name)
	{
		EntityID eID(m_curEntityID++);
		Entity* pEntity = new Entity(eID,name);

		m_entities.insert(std::make_pair(eID, pEntity));

		return pEntity->GetEntityID();
	}


	Entity * EntitySystem::GetEntity(EntityID & id)
	{
		EntityMap::iterator itor = m_entities.find(id);

		if(itor == m_entities.end())
			return nullptr;

		return itor->second;
	}


	void EntitySystem::DestoryEntity(EntityID & id)
	{
		EntityMap::iterator itor = m_entities.find(id);

		if (itor == m_entities.end())
			return;

		EntityNotifyEBus::Event(id, &IEntityNotify::OnEntityDestory,id);
		
		Entity* pEntity = itor->second;

		if (pEntity != nullptr)
			delete pEntity;

		m_entities.erase(itor);
	}


	void EntitySystem::ActivateEntity(EntityID & id)
	{
		Entity* pEntity = GetEntity(id);

		if (pEntity != nullptr)
		{
			pEntity->Activate();
			EntityNotifyEBus::Event(id, &IEntityNotify::OnEntityActivated,id);
		}
	}


	void EntitySystem::DeactivateEntity(EntityID & id)
	{
		Entity* pEntity = GetEntity(id);

		if (pEntity != nullptr)
		{
			pEntity->Activate();
			EntityNotifyEBus::Event(id, &IEntityNotify::OnEntityDeactivate, id);
		}
	}


	ComponentID EntitySystem::AddComponent(EntityID & id, Component * pComponent)
	{
		if (pComponent == nullptr)
			return INVALID_UID;

		Entity* pEntity = GetEntity(id);

		if (pEntity == nullptr)
			return INVALID_UID;
		
		return pEntity->AddComponent(pComponent);
	}


	void EntitySystem::RemoveComponent(EntityID & id, Component * pComponent)
	{
		if (pComponent == nullptr)
			return;

		Entity* pEntity = GetEntity(id);

		if (pEntity == nullptr)
			return;

		pEntity->RemoveComponent(pComponent);
	}


	void EntitySystem::RemoveComponent(EntityID & eid, ComponentID & cid)
	{
		Entity* pEntity = GetEntity(eid);

		if (pEntity == nullptr)
			return;

		pEntity->RemoveComponent(cid);
	}

	void EntitySystem::Destory()
	{
	}

}