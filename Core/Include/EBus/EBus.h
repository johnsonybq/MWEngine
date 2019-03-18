#pragma once
#include <map>
#include <set>
#include "MWCore.h"

namespace Core
{
	template<class Interface>
	class EBus
	{
	public:
		
		static void		BusConnect(Interface* pInterface);

		static void		BusConnect(UID id, Interface* pInterface);

		static void		BusDisconnect(Interface* pInterface);
		
		static void		BusDisconnect(UID id, Interface* pInterface);

		template<class Fuction, class ... InputArgs>
		static void		Event(UID uid, Fuction fuc, InputArgs&& ... args);

		template<class Fuction, class ... InputArgs>
		static void		Broadcast(Fuction fuc, InputArgs&& ... args);

		template<class Result,class Fuction, class ... InputArgs>
		static void		EventResult(Result& result, UID uid, Fuction fuc, InputArgs&& ... args);

		template<class Result, class Fuction, class ... InputArgs>
		static void		BroadcastResult(Result& result, Fuction fuc, InputArgs&& ... args);

	private:

		using CallBackList = std::set<Interface*>;
		using AllCallBack = std::map<UID, CallBackList>;

		static AllCallBack		m_callBacks;
		static CallBackList		m_noIDCallBacks;
	};
	
	template<class Interface>
	inline void EBus<Interface>::BusConnect(Interface * pInterface)
	{
		if (pInterface == nullptr)
			return;

		m_noIDCallBacks.insert(pInterface);
	}

	template<class Interface>
	inline void EBus<Interface>::BusConnect(UID id, Interface * pInterface)
	{
		if (pInterface == nullptr)
			return;

		AllCallBack::iterator itor = m_callBacks.find(id);
		CallBackList list;

		if (itor == m_callBacks.end())
		{
			m_callBacks.insert(std::pair<UID, CallBackList>(id, list));
			itor = m_callBacks.find(id);
		}

		itor->second.insert(pInterface);
	}

	template<class Interface>
	inline void EBus<Interface>::BusDisconnect(Interface * pInterface)
	{
		if (pInterface == nullptr)
			return;

		CallBackList::iterator itor = m_noIDCallBacks.find(pInterface);

		if (itor != m_noIDCallBacks.end())
			m_noIDCallBacks.erase(itor);
	}

	template<class Interface>
	inline void EBus<Interface>::BusDisconnect(UID id, Interface * pInterface)
	{
		if (pInterface == nullptr)
			return;

		AllCallBack::iterator itor = m_callBacks.find(id);

		if (itor == m_callBacks.end())
			return;

		CallBackList list = itor->second;

		CallBackList::iterator findItor = list.find(pInterface);

		if (findItor != list.end())
			list.erase(findItor);
	}

	template<class Interface>
	template<class Fuction, class ...InputArgs>
	inline void EBus<Interface>::Event(UID uid, Fuction fuc, InputArgs && ...args)
	{
		AllCallBack::iterator itor = m_callBacks.find(uid);

		if (itor == m_callBacks.end())
			return;

		CallBackList list = itor->second;

		CallBackList::iterator cbItor = list.begin();

		for (; cbItor != list.end(); ++cbItor)
		{
			Interface* pInterface = *cbItor;

			if (pInterface != nullptr)
				(pInterface->*fuc)(args...);
		}
	}

	template<class Interface>
	template<class Fuction, class ...InputArgs>
	inline void EBus<Interface>::Broadcast(Fuction fuc, InputArgs && ...args)
	{
		CallBackList::iterator noIDitor = m_noIDCallBacks.begin();

		for (; noIDitor != m_noIDCallBacks.end(); ++noIDitor)
		{
			Interface* pInterface = *noIDitor;

			if (pInterface != nullptr)
				(pInterface->*fuc)(args...);
		}


		AllCallBack::iterator itor = m_callBacks.begin();

		for (; itor != m_callBacks.end(); ++itor)
		{
			CallBackList list = itor->second;

			CallBackList::iterator cbItor = list.begin();

			for (; cbItor != list.end(); ++cbItor)
			{
				Interface* pInterface = *cbItor;

				if (pInterface != nullptr)
					(pInterface->*fuc)(args...);
			}
		}

	}

	template<class Interface>
	template<class Result, class Fuction, class ...InputArgs>
	inline void EBus<Interface>::EventResult(Result & result, UID uid, Fuction fuc, InputArgs && ...args)
	{
		AllCallBack::iterator itor = m_callBacks.find(uid);

		if (itor == m_callBacks.end())
			return;

		CallBackList list = itor->second;

		CallBackList::iterator cbItor = list.begin();

		for (; cbItor != list.end(); ++cbItor)
		{
			Interface* pInterface = *cbItor;

			if (pInterface != nullptr)
				result = (pInterface->*fuc)(args...);
		}
	}

	template<class Interface>
	template<class Result, class Fuction, class ...InputArgs>
	inline void EBus<Interface>::BroadcastResult(Result & result, Fuction fuc, InputArgs && ...args)
	{
		CallBackList::iterator noIDitor = m_noIDCallBacks.begin();

		for (; noIDitor != m_noIDCallBacks.end(); ++noIDitor)
		{
			Interface* pInterface = *noIDitor;

			if (pInterface != nullptr)
				result = (pInterface->*fuc)(args...);
		}

		AllCallBack::iterator itor = m_callBacks.begin();

		for (; itor != m_callBacks.end(); ++itor)
		{
			CallBackList list = itor->second;

			CallBackList::iterator cbItor = list.begin();

			for (; cbItor != list.end(); ++cbItor)
			{
				Interface* pInterface = *cbItor;

				if (pInterface != nullptr)
					result = (pInterface->*fuc)(args...);
			}
		}
	}


	template<class Interface>
	std::map<UID, std::set<Interface*>> EBus<Interface>::m_callBacks;

	template<class Interface>
	std::set<Interface*> EBus<Interface>::m_noIDCallBacks;

}