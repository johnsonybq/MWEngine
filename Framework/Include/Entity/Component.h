#pragma once
#include "MWCore.h"
#include "Serialize\ISerialize.h"
namespace Framework
{
	// 在实体上的索引ID
	using ComponentID = UID;
	using EntityID = UID;
	#define		INVALID_UID 0xffffffff

	class Component
	{
		SERIALIZE_DEFAULTREFLECT_CLASS(Framework::Component);

	public:

		Component();

		virtual ~Component();

	public:


		/**
			设置当前组件在所属实体中的组件编号
		*/
		void					SetComponentID(ComponentID& id);


		/**
			获取组件编号
		*/
		ComponentID				GetComponentID();


		/**
			设置所属实体ID
		*/
		void					SetEntityID(EntityID& id);


		/**
			获取所属实体ID
		*/
		EntityID				GetEntityID();


		/**
			初始化组件
			与激活不同，只在添加到实体时执行一次
		*/
		virtual void			Initialization();


		/**
			激活组件
		*/
		virtual void			Activate() {};


		/**
			停用组件
		*/
		virtual void			Deactivate() {};


	protected:

		EntityID			m_entityID;
		ComponentID			m_componentID;

	};
}