#pragma once
#include <Windows.h>
#include <iostream>
#include "SingleModel.h"



// 内存管理助手用于统计内存使用情况做日志输出

class		MemoryHelper
{
	
	SINGLE_INSTANCE( MemoryHelper );


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




MemoryHelper::MemoryHelper()
:m_nCurMemObjects( 0 ), m_nCurAllocMemSize( 0 ),
m_nMaxMemObjects( 0 ), m_nMaxAllocMemSize( 0 ),
m_nCurMemTotalSize( 0 ), m_nMaxMemTotalSize( 0 )
{

}



MemoryHelper::~MemoryHelper()
{
	ReportMemoryWarning();
}



void				MemoryHelper::OnMemAlloc( unsigned int nMemSize, unsigned int nExMemSize )
{
	++m_nCurMemObjects;
	m_nCurAllocMemSize += nMemSize;

	m_nMaxMemObjects = m_nMaxMemObjects > m_nCurMemObjects ? m_nCurMemObjects : m_nCurMemObjects;
	m_nMaxAllocMemSize = m_nMaxAllocMemSize > m_nCurAllocMemSize ? m_nCurAllocMemSize : m_nCurAllocMemSize;

	m_nCurMemTotalSize += ( nMemSize + nExMemSize );
	m_nMaxMemTotalSize = m_nMaxMemTotalSize > m_nCurMemTotalSize ? m_nMaxMemTotalSize : m_nCurMemTotalSize;
}



void				MemoryHelper::OnMemRetrieve( unsigned int nMemSize, unsigned int nExMemSize )
{
	-- m_nCurMemObjects;
	m_nCurAllocMemSize -= nMemSize;
	m_nCurMemTotalSize -= ( nMemSize + nExMemSize );
}



void				MemoryHelper::ReportMemLeak( const char* pFile, int nLine, unsigned int nSize, int nPtrAddr )
{
	char szWarning[512] = {};

	_snprintf_s(
		szWarning, 512,
		"\r\n\r\n---------------------------------------------------------------------\r\n"
		"	Memory Manager Leak:	File:  %s,  Line: %d,  Size: %d,  Addr: %x\r\n"
		"-----------------------------------------------------------------------\r\n",
		pFile, nLine, nSize, nPtrAddr );

	ReportMemoryInfo( szWarning );
}



void				MemoryHelper::ReportMemFlowOver( const char* pFile, int nLine, int nPtrAddr )
{
	char szWarning[256] = {};

	_snprintf_s( szWarning, 256,
		"\r\n\r\n-----------------------------------------------------------\r\n"
		"	Memory Manager Flow Over:	File:  %s,  Line:  %d,  Addr:  %x\r\n"
		"----------------------------------------------------------------\r\n",
		pFile, nLine, nPtrAddr );

	ReportMemoryInfo( szWarning );
}



void				MemoryHelper::ReportMemoryWarning()
{
	char szToOutput[1024] = {};

	_snprintf_s( szToOutput, 1024,
		"\r\n\r\n------------------------------------------------------------\r\n"
		"						Memory	Manager Report\r\n"
		"--------------------------------------------------------------\r\n"
		"Current Memory Object			:	%d\r\n"
		"Current Memory Used			:	%d bytes\r\n"
		"Maximal Memory Object Allocated:	%d\r\n"
		"Maximal Memory Used			:	%d bytes,	%f kb\r\n"
		"Total	Memory Used				:	%d bytes,	%f kb\r\n"
		"Maximal Total Memory Used		:	%d bytes,	%f kb\r\n"
		"-----------------------------------------------------------------\r\n\r\n",
		m_nCurMemObjects, m_nCurAllocMemSize, m_nMaxMemObjects, m_nMaxAllocMemSize,
		( float )( m_nMaxAllocMemSize ) / 1024.0f, m_nCurMemTotalSize, ( float )( m_nCurMemTotalSize ) / 1024.0f,
		m_nMaxMemTotalSize, ( float )( m_nMaxMemTotalSize ) / 1024.0f );
		

	ReportMemoryInfo( szToOutput );
}



void				MemoryHelper::ReportMemoryInfo( const char* pInfo )
{
	static bool s_bOpenFirst = true;

	if ( s_bOpenFirst )
	{
		// 每次启动是都会删除此文件
		DeleteFileA( "Memory.log" );
		s_bOpenFirst = false;
	}

	// 写了就关
	HANDLE hFile = CreateFileA( "Memory.log", GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
	SetFilePointer( hFile, 0, 0, FILE_END );
	DWORD bytes;
	WriteFile( hFile, pInfo, ( DWORD )strlen( pInfo ), &bytes, 0 );
	CloseHandle( hFile );
	_flushall();
}