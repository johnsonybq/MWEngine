/************************************************************************/
/*
文件名: IFramework.h
描  述: 框架接口
日  期: 01/04/2019
作  者: MibuWolf
版	本: 1.0
备  注:
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


		// 初始化
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