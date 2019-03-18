#include <time.h>
#include <direct.h>
#include "LogManager.h"
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
		if (msg == nullptr || m_pFile == NULL)
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


		DWORD bytes;
		WriteFile(m_pFile, totalMsg, (DWORD)strlen(totalMsg), &bytes, 0);
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