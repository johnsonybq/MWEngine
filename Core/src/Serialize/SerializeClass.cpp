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

	void SerializeClass::SetName(const char * name, int v)
	{
		if (name == nullptr)
			return;

		className = name;
		version = v;
	}

	const char * SerializeClass::GetName()
	{
		return className.c_str();
	}

	void SerializeClass::Member(ESMemberType eType, const char * memberName, int offset)
	{
		if (memberName == nullptr)
			return;

		int count = members.size();
		SerializeMember* member = nullptr;

		for (int i = 0; i < count; ++i)
		{
			member = members[i];

			if (member != nullptr && member->eMemberType == eType)
			{
				LogEBus::Broadcast(&ILog::Error, "Repeat addition Member for Class , Class Name is %s, Member Name is %s", className.c_str(), memberName);
				return;
			}
		}

		member = nullptr;

		member = MW_New SerializeMember;
		member->eMemberType = eType;
		member->memberName = memberName;
		member->offset = offset;
		members.push_back(member);
	}

	int SerializeClass::GetMemberCount()
	{
		return members.size();
	}

	SerializeMember * SerializeClass::GetMember(int count)
	{
		if(count < 0 || count >= members.size())
			return nullptr;

		return members[count];
	}
}