#pragma once
#include <map>
#include "Entity\IEntitySystem.h"


namespace Framework
{
	class EntitySystem : public IEntitySystem
	{
		SINGLETON_IMPLEMENT(EntitySystem);

	public:

		~EntitySystem();

	public:


		// ��ʼ��
		virtual	void					Initialization();


		// ����ʵ��
		virtual EntityID				CreateEntity(std::string name = "");


		// ��ȡʵ��
		virtual Entity*					GetEntity(EntityID& id);


		// ����ʵ��
		virtual void					DestoryEntity(EntityID& id);


		// ����ʵ��
		virtual void					ActivateEntity(EntityID& id);


		// ͣ��ʵ��
		virtual void					DeactivateEntity(EntityID& id);


		// ������
		virtual ComponentID				AddComponent(EntityID& id, Component* pComponent);


		// �Ƴ����
		virtual void					RemoveComponent(EntityID& id, Component* pComponent);


		// �Ƴ����
		virtual void					RemoveComponent(EntityID& eid, ComponentID& cid);


		// ����
		virtual void					Destory();


	private:

		using EntityMap = std::map<EntityID, Entity*>;
		EntityMap			m_entities;

		EntityID				m_curEntityID;
	};
}