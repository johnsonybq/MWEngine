//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	MemLock.cpp
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#include "MemLock.h"

XLock::XLock()
{
    m_bLocked   = FALSE;
    InitializeCriticalSection(&m_critical);
#if (xDEBUG == xTRUE)
    m_szFile[0] = 0;
    m_nLine     = 0;
#endif
}
XLock::~XLock()
{
    DeleteCriticalSection(&m_critical);
}

#if (xDEBUG == xTRUE)
x_void XLock::Lock(x_pcchar szFile, x_uint line)
{
    EnterCriticalSection(&m_critical);
    strncpy(m_szFile, szFile, xMAX_PATH);
    m_szFile[xMAX_PATH - 1] = 0;
    m_nLine = line;
    m_bLocked = TRUE;
}
x_void XLock::Unlock()
{
    memset(m_szFile, 0, xMAX_PATH);
    m_nLine = 0;
    m_bLocked = FALSE;
    LeaveCriticalSection(&m_critical);
}
#else
x_void XLock::Lock()
{
    EnterCriticalSection(&m_critical);
    m_bLocked = TRUE;
}
x_void XLock::Unlock()
{
    m_bLocked = FALSE;
    LeaveCriticalSection(&m_critical);
}
#endif

x_bool XLock::TryLock()
{
    return FALSE;
}
