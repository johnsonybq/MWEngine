#pragma once
#include <map>
#include <string>
#include "MWCore.h"
#include "Component.h"


namespace Framework
{

	enum EntityState
	{
		ES_ACTIVATE,				// ����״̬
		ES_DEACTIVATE				// ͣ��״̬
	};

	class Entity
	{
	public:

		Entity();


		Entity(EntityID& id, std::string name = "");


		~Entity();


	public:


		/**
			��ȡʵ��ID
		*/
		EntityID&		GetEntityID();


		/**
			������
		*/
		ComponentID		AddComponent(Component* pComponent);


		/**
			�Ƴ����
		*/
		void			RemoveComponent(ComponentID id);


		/**
			�Ƴ����
		*/
		void			RemoveComponent(Component* pComponent);



		/**
			����
		*/
		virtual void	Activate();



		/**
			ͣ��
		*/
		virtual void	Deactivate();



	private:

		EntityID					m_entityID;
		std::string					m_name;
		typedef std::map<ComponentID, Component*>	ComponentMap;
		ComponentMap				m_components;
		
		ComponentID					m_curComponentID;		// ��ʱ���� ������ComponentTypeID���

	};
}