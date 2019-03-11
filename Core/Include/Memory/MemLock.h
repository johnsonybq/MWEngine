//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	MemLock.h
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#pragma once

#include "MemBase.h"

struct XLock
{
    CRITICAL_SECTION        m_critical;
    x_bool                  m_bLocked;

#if (xDEBUG == xTRUE)
    x_char                  m_szFile[xMAX_PATH];
    x_uint                  m_nLine;
#endif

    XLock();
    ~XLock();

    x_bool  IsLocked() const {
        return m_bLocked;
    }

#if (xDEBUG == xTRUE)
    x_void  Lock(x_pcchar szFile, x_uint line);
#else
    x_void  Lock();
#endif
    x_bool  TryLock();
    x_void  Unlock();
};


#if (xDEBUG == xTRUE)
#define XLock_Section(lock) (lock).Lock(__FILE__, __LINE__)
#define XUnlock_Section(lock) (lock).Unlock()
#else
#define XLock_Section(lock) (lock).Lock()
#define XUnlock_Section(lock) (lock).Unlock()
#endif

#ifdef __MULTI_THREAD__
#define XMEMORY_LOCK(x) XLock_Section(x)
#define XMEMORY_UNLOCK(x) XUnlock_Section(x)
#else
#define XMEMORY_LOCK(x)
#define XMEMORY_UNLOCK(x)
#endif
