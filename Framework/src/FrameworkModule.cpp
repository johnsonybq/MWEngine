/************************************************************************/
/*
�ļ���: IFramework.h
��  ��: ��ܽӿ�
��  ��: 01/04/2019
��  ��: MibuWolf
��	��: 1.0
��  ע:
*/
/************************************************************************/
#pragma once
#include "MWCore.h"
#include "Module\Module.h"
#include "Entity\Entity.h"
#include "Entity\Component.h"
#include "Serialize\ISerializable.h"
#include "Entity\TransformComponent.h"

namespace Framework
{
	class FrameworkModule : public Core::Module
	{
		SERIALIZE_DEFAULTREFLECT_CLASS(Framework::FrameworkModule);

	public:

		FrameworkModule()
		{

		}

		virtual ~FrameworkModule()
		{

		}


	public:


		// ��ʼ��
		virtual	bool	Initialize()
		{
			Framework::FrameworkModule::RegisterSerializeReflect();
			//Framework::Entity::RegisterSerializeReflect();
			//Framework::Component::RegisterSerializeReflect();
			Framework::TransformComponent::RegisterSerializeReflect();

			return true;
		}


	};

	void		FrameworkModule::SerializeReflect()
	{

	}

}



INITIALIZATION_MODULE_CLASS(Framework::FrameworkModule);