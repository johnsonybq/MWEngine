#pragma once
#include "Log\ILog.h"
#include "MWCore.h"

namespace Core
{

	class LogManager : public ILog
	{

		SINGLETON_IMPLEMENT(LogManager);


	public:


		~LogManager();


	public:


		// ��ʼ��
		virtual	bool	Initialize();


		// �����־(������ȼ�)
		virtual	void	Log(const char* msg, ...);


		// �������
		virtual	void	Warning(const char* msg, ...);


		// �������
		virtual	void	Error(const char* msg, ...);


		// д��Log�ļ�
		virtual	void	ToFile(const char* msg, ...);


		// ��Log�ļ�
		virtual	void	OpenLogFile(const char* path);


		//�ر�Log�ļ�
		virtual	void	CloseLogFile(const char* path);


	private:


	

	};

}
