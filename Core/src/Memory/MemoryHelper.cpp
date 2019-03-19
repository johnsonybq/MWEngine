#pragma once
#include <Windows.h>
#include <iostream>
#include "Memory\MemoryHelper.h"
#include "System\ISystem.h"



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

	const char* rootPath = nullptr;
	char filePath[256] = {};
	Core::SystemEBus::BroadcastResult(rootPath,&Core::ISystem::GetRootPath);

	if (rootPath != nullptr)
	{
		sprintf_s(filePath, "%s%s", rootPath, "Memory.log");
	}
	else
	{
		sprintf_s(filePath, "%s", "Memory.log");
	}

	if ( s_bOpenFirst )
	{
		// 每次启动是都会删除此文件
		DeleteFileA(filePath);
		s_bOpenFirst = false;
	}

	// 写了就关
	HANDLE hFile = CreateFileA(filePath, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
	SetFilePointer( hFile, 0, 0, FILE_END );
	DWORD bytes;
	WriteFile( hFile, pInfo, ( DWORD )strlen( pInfo ), &bytes, 0 );
	CloseHandle( hFile );
	_flushall();
}