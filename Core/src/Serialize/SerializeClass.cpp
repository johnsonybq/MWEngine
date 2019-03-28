#include "Log\ILog.h"
#include "Serialize\SerializeClass.h"


namespace Core
{
	SerializeClass::SerializeClass()
		:className("")
	{

	}


	SerializeClass::~SerializeClass()
	{

	}

	void SerializeClass::SetName(const char * name)
	{
		if (name == nullptr)
			return;

		className = name;
	}

	const char * SerializeClass::GetName()
	{
		return className.c_str();
	}

	void SerializeClass::SetVersion(int v)
	{
		version = v;
	}

	int SerializeClass::GetVersion()
	{
		return version;
	}

	int SerializeClass::GetMemberCount()
	{
		return (int)members.size();
	}

	SerializeMember * SerializeClass::GetMember(int count)
	{
		if(count < 0 || count >= (int)members.size())
			return nullptr;

		return members[count];
	}
}