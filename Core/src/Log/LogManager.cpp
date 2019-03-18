#include <time.h>
#include <direct.h>
#include <windows.h>
#include "LogManager.h"
#include "Memory\MemoryDefine.h"

using namespace std;

namespace Core
{
	LogManager::LogManager()
		:m_pFile(nullptr)
	{
	}


	LogManager::~LogManager()
	{
	}


	bool LogManager::Initialize()
	{
		LogEBus::BusConnect(this);

		char buffer[_MAX_PATH];
		_getcwd(buffer, _MAX_PATH);

		char logPath[_MAX_PATH] = "%s//user//log.ini";
		vsprintf_s(logPath, logPath, buffer);
		m_pFile = fopen(logPath, "rw+");

		return true;
	}


	void LogManager::Log(const char * msg, ...)
	{
		if (msg == nullptr)
			return;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		time_t now = time(NULL);
		tm t;
		localtime_s(&t, &now);

		char msgBuf[4096];
		char totalMsg[4096] = "<%d:%d:%d> [Message] %s  \n";
		va_list ap;
		va_start(ap, msg);
		vsprintf_s(msgBuf, msg, ap);
		va_end(ap);


		printf_s(totalMsg, t.tm_hour, t.tm_min, t.tm_sec, msgBuf);
	}


	void LogManager::Warning(const char * msg, ...)
	{
		if (msg == nullptr)
			return;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
			FOREGROUND_GREEN);

		time_t now = time(NULL);
		tm t;
		localtime_s(&t, &now);

		char msgBuf[4096];
		char totalMsg[4096] = "<%d:%d:%d> [Warning] %s  \n";
		va_list ap;
		va_start(ap, msg);
		vsprintf_s(msgBuf, msg, ap);
		va_end(ap);


		printf_s(totalMsg, t.tm_hour, t.tm_min, t.tm_sec, msgBuf);
	}


	void LogManager::Error(const char * msg, ...)
	{
		if (msg == nullptr)
			return;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED);

		time_t now = time(NULL);
		tm t;
		localtime_s(&t, &now);

		char msgBuf[4096];
		char totalMsg[4096] = "<%d:%d:%d> [Error] %s  \n";
		va_list ap;
		va_start(ap, msg);
		vsprintf_s(msgBuf, msg, ap);
		va_end(ap);


		printf_s(totalMsg, t.tm_hour, t.tm_min, t.tm_sec, msgBuf);
	}


	void LogManager::ToFile(const char * msg, ...)
	{
		if (msg == nullptr)
			return;

		time_t now = time(NULL);
		tm t;
		localtime_s(&t, &now);

		char msgBuf[4096];
		char totalMsg[4096] = "<%d:%d:%d> [Error] %s  \n";
		va_list ap;
		va_start(ap, msg);
		vsprintf_s(msgBuf, msg, ap);
		va_end(ap);


	}


	void LogManager::OpenLogFile(const char * path)
	{
		
	}


	void LogManager::CloseLogFile(const char * path)
	{
		
	}


}