/************************************************************************/
/*
�ļ���: IEntitySystem.h
��  ��: ʵ�弰�����������ӿ���
��  ��: 14/12/2018
��  ��: Sam
��	��: 1.0
��  ע:
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
		@breif		����ʵ��

		@param		[IN]
		name		ʵ����

		@param		[OUT]
		return 		ʵ��ID
		*/
		virtual EntityID			CreateEntity(std::string name = "") = 0;


		/**
		@breif		��ȡʵ��

		@param		[IN]
		id			ʵ��ID

		@param		[OUT]
		return 		ʵ��
		*/
		virtual Entity*				GetEntity(EntityID& id) = 0;



		/**
		@breif		����ʵ��

		@param		[IN]
		id			ʵ��ID
		*/
		virtual void				DestoryEntity(EntityID& id) = 0;


		/**
		@breif		����ʵ��

		@param		[IN]
		id			ʵ��ID
		*/
		virtual void				ActivateEntity(EntityID& id) = 0;


		/**
		@breif		ͣ��ʵ��

		@param		[IN]
		id			ʵ��ID
		*/
		virtual void				DeactivateEntity(EntityID& id) = 0;


		/**
		@breif		������

		@param		[IN]
		id			ʵ��ID

		@param		[IN]
		pComponent	�������
		*/
		virtual ComponentID			AddComponent(EntityID& id, Component* pComponent) = 0;



		/**
		@breif		�Ƴ����

		@param		[IN]
		id			ʵ��ID

		@param		[IN]
		pComponent	�������
		*/
		virtual void				RemoveComponent(EntityID& id, Component* pComponent) = 0;



		/**
		@breif		�Ƴ����

		@param		[IN]
		eid			ʵ��ID

		@param		[IN]
		cid			���ID
		*/
		virtual void				RemoveComponent(EntityID& eid, ComponentID& cid) = 0;


	};

	using EntityEBus = Core::EBus<IEntitySystem>;



	class IEntityNotify
	{
	public:


		/**
		@breif		����ʵ��ص�

		@param		[IN]
		id			ʵ��ID
		*/
		virtual void			OnEntityCreated(EntityID& id) = 0;


		/**
		@breif		����ʵ��ص�

		@param		[IN]
		id			ʵ��ID
		*/
		virtual void			OnEntityDestory(EntityID& id) = 0;


		/**
		@breif		����ʵ��ص�

		@param		[IN]
		id			ʵ��ID
		*/
		virtual void			OnEntityActivated(EntityID& id) = 0;


		/**
		@breif		ͣ��ʵ��ص�

		@param		[IN]
		id			ʵ��ID
		*/
		virtual void			OnEntityDeactivate(EntityID& id) = 0;
	};

	using EntityNotifyEBus = Core::EBus<IEntityNotify>;

}
