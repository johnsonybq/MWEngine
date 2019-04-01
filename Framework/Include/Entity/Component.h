#pragma once
#include "MWCore.h"

namespace Framework
{
	// ��ʵ���ϵ�����ID
	using ComponentID = UID;
	using EntityID = UID;
	#define		INVALID_UID 0xffffffff

	class Component
	{
	public:

		Component();

		virtual ~Component();

	public:


		/**
			���õ�ǰ���������ʵ���е�������
		*/
		void					SetComponentID(ComponentID& id);


		/**
			��ȡ������
		*/
		ComponentID				GetComponentID();


		/**
			��������ʵ��ID
		*/
		void					SetEntityID(EntityID& id);


		/**
			��ȡ����ʵ��ID
		*/
		EntityID				GetEntityID();


		/**
			��ʼ�����
			�뼤�ͬ��ֻ����ӵ�ʵ��ʱִ��һ��
		*/
		virtual void			Initialization();


		/**
			�������
		*/
		virtual void			Activate() = 0;


		/**
			ͣ�����
		*/
		virtual void			Deactivate() = 0;


	protected:

		EntityID			m_entityID;
		ComponentID			m_componentID;

	};
}