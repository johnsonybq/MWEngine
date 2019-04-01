#pragma once
#include <map>
#include <string>
#include "MWCore.h"
#include "Component.h"


namespace Framework
{

	enum EntityState
	{
		ES_ACTIVATE,				// 激活状态
		ES_DEACTIVATE				// 停用状态
	};

	class Entity
	{
	public:

		Entity();


		Entity(EntityID& id, std::string name = "");


		~Entity();


	public:


		/**
			获取实体ID
		*/
		EntityID&		GetEntityID();


		/**
			添加组件
		*/
		ComponentID		AddComponent(Component* pComponent);


		/**
			移除组件
		*/
		void			RemoveComponent(ComponentID id);


		/**
			移除组件
		*/
		void			RemoveComponent(Component* pComponent);



		/**
			激活
		*/
		virtual void	Activate();



		/**
			停用
		*/
		virtual void	Deactivate();



	private:

		EntityID					m_entityID;
		std::string					m_name;
		typedef std::map<ComponentID, Component*>	ComponentMap;
		ComponentMap				m_components;
		
		ComponentID					m_curComponentID;		// 临时方案 后期用ComponentTypeID替代

	};
}