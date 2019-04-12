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


		// 初始化
		virtual	void					Initialization();


		// 创建实体
		virtual EntityID				CreateEntity(std::string name = "");


		// 获取实体
		virtual Entity*					GetEntity(EntityID& id);


		// 销毁实体
		virtual void					DestoryEntity(EntityID& id);


		// 激活实体
		virtual void					ActivateEntity(EntityID& id);


		// 停用实体
		virtual void					DeactivateEntity(EntityID& id);


		// 添加组件
		virtual ComponentID				AddComponent(EntityID& id, Component* pComponent);


		// 移除组件
		virtual void					RemoveComponent(EntityID& id, Component* pComponent);


		// 移除组件
		virtual void					RemoveComponent(EntityID& eid, ComponentID& cid);


		// 销毁
		virtual void					Destory();


	private:

		using EntityMap = std::map<EntityID, Entity*>;
		EntityMap			m_entities;

		EntityID				m_curEntityID;
	};
}