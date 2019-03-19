#include <direct.h>
#include "LogManager.h"
#include "System\ISystem.h"
#include "Memory\MemoryDefine.h"
using namespace std;

namespace Core
{
	LogManager::LogManager()
		:m_pFile(NULL)
	{
	}


	LogManager::~LogManager()
	{
	}


	bool LogManager::Initialize()
	{
		LogEBus::BusConnect(this);

		m_pFile = CreateFileA("F:\\Code\\MWEngine\\WorkSpace\\Game.log", GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		SetFilePointer(m_pFile, 0, 0, FILE_END);

		 LogManager* pLog = MW_New LogManager();

		return true;
	}


	void LogManager::Log(const char * msg, ...)
	{
		if (msg == nullptr)
			return;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		

		char msgBuf[4096];
		char totalMsg[4096] = "<%d:%d:%d> [Message] %s  \n";
		va_list ap;
		va_start(ap, msg);
		vsprintf_s(msgBuf, msg, ap);
		va_end(ap);

		int hour, min, sec = 0;
		SystemEBus::BroadcastResult(hour, &Core::ISystem::GetLocalTime, Core::E_TIME_TYPE_HOUR);
		SystemEBus::BroadcastResult(min, &Core::ISystem::GetLocalTime, Core::E_TIME_TYPE_MINUTE);
		SystemEBus::BroadcastResult(sec, &Core::ISystem::GetLocalTime, Core::E_TIME_TYPE_SECOND);

		printf_s(totalMsg, hour, min, sec, msgBuf);
	}


	void LogManager::Warning(const char * msg, ...)
	{
		if (msg == nullptr)
			return;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
			FOREGROUND_GREEN);

		int hour, min, sec = 0;
		SystemEBus::BroadcastResult(hour, &Core::ISystem::GetLocalTime, Core::E_TIME_TYPE_HOUR);
		SystemEBus::BroadcastResult(min, &Core::ISystem::GetLocalTime, Core::E_TIME_TYPE_MINUTE);
		SystemEBus::BroadcastResult(sec, &Core::ISystem::GetLocalTime, Core::E_TIME_TYPE_SECOND);

		char msgBuf[4096];
		char totalMsg[4096] = "<%d:%d:%d> [Warning] %s  \n";
		va_list ap;
		va_start(ap, msg);
		vsprintf_s(msgBuf, msg, ap);
		va_end(ap);


		printf_s(totalMsg, hour, min, sec, msgBuf);
	}


	void LogManager::Error(const char * msg, ...)
	{
		if (msg == nullptr)
			return;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED);

		char msgBuf[4096];
		char totalMsg[4096] = "<%d:%d:%d> [Error] %s  \n";
		va_list ap;
		va_start(ap, msg);
		vsprintf_s(msgBuf, msg, ap);
		va_end(ap);

		int hour = 0, min = 0, sec = 0;
		SystemEBus::BroadcastResult(hour, &Core::ISystem::GetLocalTime, Core::E_TIME_TYPE_HOUR);
		SystemEBus::BroadcastResult(min, &Core::ISystem::GetLocalTime, Core::E_TIME_TYPE_MINUTE);
		SystemEBus::BroadcastResult(sec, &Core::ISystem::GetLocalTime, Core::E_TIME_TYPE_SECOND);

		printf_s(totalMsg, hour, min, sec, msgBuf);
	}


	void LogManager::LogToFile(const char * msg, ...)
	{
		if (msg == nullptr || m_pFile == NULL)
			return;

		char msgBuf[4096];
		va_list ap;
		va_start(ap, msg);
		vsprintf_s(msgBuf, msg, ap);
		va_end(ap);

		DWORD bytes;
		WriteFile(m_pFile, msgBuf, (DWORD)strlen(msgBuf), &bytes, 0);
		_flushall();
		CloseHandle(m_pFile);
	}


	void LogManager::OpenLogFile(const char * path)
	{
		
	}


	void LogManager::CloseLogFile(const char * path)
	{
		
	}


}