#pragma once
#include <Windows.h>
#include <iostream>



// 内存管理助手用于统计内存使用情况做日志输出

class		MemoryHelper
{
private:	

	MemoryHelper();

public:

	
	static MemoryHelper* GetInstance()
	{													
		static MemoryHelper instance;
		return &instance;									
	}


public:

	
	~MemoryHelper();


public:



	void				OnMemAlloc( unsigned int nMemSize, unsigned int nExMemSize ); 


	void				OnMemRetrieve( unsigned int nMemSize, unsigned int nExMemSize );


	void				ReportMemLeak( const char* pFile, int nLine, unsigned int nSize, int nPtrAddr );


	void				ReportMemFlowOver( const char* pFile, int nLine, int nPtrAddr );


	void				ReportMemoryInfo( const char* pInfo );


	void				ReportMemoryWarning();



private:


	unsigned int					m_nCurMemObjects;			// 当前内存对象个数
	unsigned int					m_nCurAllocMemSize;			// 当前正在使用的内存大小

	unsigned int					m_nMaxMemObjects;			// 最大对象个数
	unsigned int					m_nMaxAllocMemSize;			// 最大分配内存大小( 外部使用的 )

	unsigned int					m_nCurMemTotalSize;			// 当前所分配的内存总量( 包含基类内存信息部分 )
	unsigned int					m_nMaxMemTotalSize;			// 最大内存分配总量

};

