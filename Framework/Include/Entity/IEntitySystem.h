/************************************************************************/
/*
文件名: IEntitySystem.h
描  述: 实体及组件基础管理接口类
日  期: 14/12/2018
作  者: Sam
版	本: 1.0
备  注:
*/
/************************************************************************/

#pragma once
#include <string>
#include "Entity.h"
#include "ISystem.h"
#include "EBus\EBus.h"


namespace Framework
{
	class IEntitySystem : public ISystem
	{
	public:


		/**
		@breif		创建实体

		@param		[IN]
		name		实体名

		@param		[OUT]
		return 		实体ID
		*/
		virtual EntityID			CreateEntity(std::string name = "") = 0;


		/**
		@breif		获取实体

		@param		[IN]
		id			实体ID

		@param		[OUT]
		return 		实体
		*/
		virtual Entity*				GetEntity(EntityID& id) = 0;



		/**
		@breif		销毁实体

		@param		[IN]
		id			实体ID
		*/
		virtual void				DestoryEntity(EntityID& id) = 0;


		/**
		@breif		激活实体

		@param		[IN]
		id			实体ID
		*/
		virtual void				ActivateEntity(EntityID& id) = 0;


		/**
		@breif		停用实体

		@param		[IN]
		id			实体ID
		*/
		virtual void				DeactivateEntity(EntityID& id) = 0;


		/**
		@breif		添加组件

		@param		[IN]
		id			实体ID

		@param		[IN]
		pComponent	组件对象
		*/
		virtual ComponentID			AddComponent(EntityID& id, Component* pComponent) = 0;



		/**
		@breif		移除组件

		@param		[IN]
		id			实体ID

		@param		[IN]
		pComponent	组件对象
		*/
		virtual void				RemoveComponent(EntityID& id, Component* pComponent) = 0;



		/**
		@breif		移除组件

		@param		[IN]
		eid			实体ID

		@param		[IN]
		cid			组件ID
		*/
		virtual void				RemoveComponent(EntityID& eid, ComponentID& cid) = 0;


	};

	using EntityEBus = Core::EBus<IEntitySystem>;



	class IEntityNotify
	{
	public:


		/**
		@breif		创建实体回调

		@param		[IN]
		id			实体ID
		*/
		virtual void			OnEntityCreated(EntityID& id) = 0;


		/**
		@breif		销毁实体回调

		@param		[IN]
		id			实体ID
		*/
		virtual void			OnEntityDestory(EntityID& id) = 0;


		/**
		@breif		激活实体回调

		@param		[IN]
		id			实体ID
		*/
		virtual void			OnEntityActivated(EntityID& id) = 0;


		/**
		@breif		停用实体回调

		@param		[IN]
		id			实体ID
		*/
		virtual void			OnEntityDeactivate(EntityID& id) = 0;
	};

	using EntityNotifyEBus = Core::EBus<IEntityNotify>;

}
