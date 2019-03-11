//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	MemUnit.cpp
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#include "MemUnit.h"
#include "MemManager.h"
#include "../../Include/IMemPort.h"
 
static int S_MemLogOutputTimes = 0;

int GetOutputTimes( void )
{
	return S_MemLogOutputTimes;
}

void OutputMemoryDebugInfo( const char* szString )
{
    static BOOL s_bOpenFirst = true;

    if( s_bOpenFirst )
    {
        // 每次引擎启动，此日志文件都将被删除
        DeleteFileA( "MemoryLog.txt" );
        s_bOpenFirst = false;
		S_MemLogOutputTimes = 0;
    }

    // 写了就关
    HANDLE hFile = CreateFileA( "MemoryLog.txt", GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
    SetFilePointer( hFile, 0, 0, FILE_END );
    DWORD bytes;
    WriteFile( hFile, szString, (DWORD)strlen(szString), &bytes, 0 );
    CloseHandle( hFile );

    _flushall();

	++S_MemLogOutputTimes;
}

// ----------------------------------------------------------------------------
// 内存泄漏报告
// ----------------------------------------------------------------------------
XALGO_API void __ReportMemoryLeak(
                        const char* szPosition, 
                        const void* szFileName, 
                        unsigned int line, 
                        unsigned int bytes, 
                        ptrdiff_t addr)
{
    char toReport[1024];
    if (!szFileName || IsBadReadPtr(szFileName, 8))
    {
        _snprintf(
            toReport, 1024, 
            "\r\n--------------------------------------------------------------\r\n"
            "Unknown position(%d) : memory leak!\r\n"
            "(%s) there are %d bytes not freed. addr = 0x%x"
            "\r\n--------------------------------------------------------------\r\n", 
            line, szPosition, bytes - 4, addr);
        toReport[1023] = 0;
    }
    else
    {
        _snprintf(
            toReport, 1024, 
            "\r\n--------------------------------------------------------------\r\n"
            "%s(%d) : memory leak!\r\n"
            "(%s) there are %d bytes not freed. addr = 0x%x"
            "\r\n--------------------------------------------------------------\r\n", 
            (const char*)szFileName, line, szPosition, bytes - 4, addr);
        toReport[1023] = 0;
    }

    OutputMemoryDebugInfo( toReport );

#if (xDEBUG == xTRUE)
    __GetMemoryManager()->m_moniter.DumpSimpleInfo();
#endif
}




// ----------------------------------------------------------------------------
// 内存越界报告
// ----------------------------------------------------------------------------
XALGO_API void __ReportMarkBeyond(
                        const char* szPosition, 
                        const void* szFileName, 
                        unsigned int line, 
                        unsigned int bytes, 
                        ptrdiff_t addr)
{
    char toReport[1024];
    if (!szFileName || IsBadReadPtr(szFileName, 8))
    {
        _snprintf(
            toReport, 1024, 
            "\r\n--------------------------------------------------------------\r\n"
            "Unknown position(%d) : Beyond Mark!\r\n"
            "(%s) %d bytes. addr = 0x%x"
            "\r\n--------------------------------------------------------------\r\n", 
            line, szPosition, bytes, addr);
        toReport[1023] = 0;
    }
    else
    {
        _snprintf(
            toReport, 1024, 
            "\r\n--------------------------------------------------------------\r\n"
            "%s(%d) : Beyond Mark!\r\n"
            "(%s) %d bytes. addr = 0x%x"
            "\r\n--------------------------------------------------------------\r\n", 
            (const char*)szFileName, line, szPosition, bytes, addr);
        toReport[1023] = 0;
    }

    OutputMemoryDebugInfo( toReport );
}