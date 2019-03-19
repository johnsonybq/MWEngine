#include <time.h>
#include "System.h"


namespace Core
{

	System::System()
	{

	}


	System::~System()
	{

	}

	bool System::Initialize()
	{
		SystemEBus::BusConnect(this);
		return true;
	}

	const char * System::GetRootPath()
	{
		return nullptr;
	}

	int System::GetLocalTime(TIME_TYPE timeType)
	{
		time_t now = time(NULL);
		tm t;
		localtime_s(&t, &now);

		switch (timeType)
		{
		case Core::E_TIME_TYPE_YEAR:
			return t.tm_year;
			break;
		case Core::E_TIME_TYPE_MOTH:
			return t.tm_mon+1;
			break;
		case Core::E_TIME_TYPE_DAY:
			return t.tm_mday;
			break;
		case Core::E_TIME_TYPE_HOUR:
			return t.tm_hour;
			break;
		case Core::E_TIME_TYPE_MINUTE:
			return t.tm_min;
			break;
		case Core::E_TIME_TYPE_SECOND:
			return t.tm_sec;
			break;
		default:
			return 0;
			break;
		}
		return 0;
	}

}