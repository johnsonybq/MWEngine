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


		// 初始化
		virtual	bool	Initialize();


		// 输出日志(最低优先级)
		virtual	void	Log(const char* msg, ...);


		// 输出警告
		virtual	void	Warning(const char* msg, ...);


		// 输出错误
		virtual	void	Error(const char* msg, ...);


		// 写入Log文件
		virtual	void	ToFile(const char* msg, ...);


		// 打开Log文件
		virtual	void	OpenLogFile(const char* path);


		//关闭Log文件
		virtual	void	CloseLogFile(const char* path);


	private:


	

	};

}
