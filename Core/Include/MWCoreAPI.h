#pragma once
#include "MWCore.h"


namespace Core
{
	class DLL_EXPORTS MWCoreAPI
	{

		SINGLETON_IMPLEMENT(MWCoreAPI)

	public:

		~MWCoreAPI();

	public:


		// ≥ı ºªØ
		bool				Initialize();


	};
}