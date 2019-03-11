//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	MemList.h
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#pragma once

#include "MemPool.h"

template <class Alloc> struct XMemoryList
{
    inline                  XMemoryList();
    inline                 ~XMemoryList();

    inline void             create(Alloc* pAlloc);
    inline void             Destroy();

private:
    inline void             init_unit(void* phugeUnit, unsigned int size);
#if (xDEBUG == xTRUE)
    inline verify_padding*  get_ccback(void* phugeUnit);
    inline int              verify_mark(void *phugeUnit);
#endif

public:
#if (xDEBUG == xTRUE)
    int                     verify_mark();
    void                    check();
    void*                   allocate(
        size_t size, const void* file = 0, unsigned int line = 0);
#else
    void*                   allocate(size_t size);
#endif
    void                    free(void* p);

#ifdef __MULTI_THREAD__
    XLock                   m_lock;
#endif
    Alloc*                  m_pAlloc;
    huge_unit*              m_pHead;
    huge_unit*              m_pTail;
};

template <class Alloc> inline XMemoryList<Alloc>::XMemoryList()
{
    m_pAlloc    = xNULL;
    m_pHead     = 0;
    m_pTail     = 0;
}

template <class Alloc> inline XMemoryList<Alloc>::~XMemoryList()
{
    Destroy();
}

template <class Alloc> inline void XMemoryList<Alloc>::Destroy()
{
    XMEMORY_LOCK(m_lock);

#if (xDEBUG == xTRUE)
    check();
#endif
    huge_unit* pCur = m_pHead;
    for (; pCur; )
    {
        huge_unit* pNext = pCur->__m_pNext;
        m_pAlloc->free(pCur);
        m_pHead = pCur = pNext;
    }

    XMEMORY_UNLOCK(m_lock);
    m_pHead = m_pTail = NULL;
}

template <class Alloc> inline void XMemoryList<Alloc>::create(Alloc* pAlloc)
{
    m_pAlloc    = pAlloc;
}

template <class Alloc> inline void XMemoryList<Alloc>::init_unit(void* p, unsigned int size)
{
	(reinterpret_cast<huge_unit*>(p))->size         = size;
#if (xDEBUG == xTRUE)
	xAssert((reinterpret_cast<huge_unit*>(p))->used == 0);
    (reinterpret_cast<huge_unit*>(p))->file         = 0;
    (reinterpret_cast<huge_unit*>(p))->line         = 0;
    (reinterpret_cast<huge_unit*>(p))->used         = 0;
    (reinterpret_cast<huge_unit*>(p))->front_verify.init();
    (*get_ccback(p)).init();
#endif
}

#if (xDEBUG == xTRUE)
template <class Alloc> inline verify_padding* XMemoryList<Alloc>::get_ccback(void* p)
{
    return reinterpret_cast<verify_padding*>(
        (reinterpret_cast<unsigned int>(p)) + 
        (reinterpret_cast<huge_unit*>(p))->size + 
        sizeof(huge_unit));
}

template <class Alloc> inline int  XMemoryList<Alloc>::verify_mark(void* p)
{
    int iRet = 0;
    verify_padding* pcc_back = get_ccback(p);
    register huge_unit* pUnit = reinterpret_cast<huge_unit*>(p);
    if (IsBadWritePtr(pUnit, 4))
    {
        __ReportMarkBeyond(
            "Unknown crash.", 
            NULL, 
            0, 
            0, 
            (ptrdiff_t)(pUnit->data));
        iRet = 1;
    }
    else if (!pUnit->front_verify.IsVailidCode() || 
        IsBadReadPtr(pcc_back, 4))
    {
        __ReportMarkBeyond(
            "Front Verify Code", 
            pUnit->file, 
            pUnit->line, 
            pUnit->size, 
            (ptrdiff_t)(pUnit->data));
        iRet = 1;
    }
    else if (!pcc_back->IsVailidCode())
    {
        __ReportMarkBeyond(
            "Back Verify Code", 
            pUnit->file, 
            pUnit->line, 
            pUnit->size, 
            (ptrdiff_t)(pUnit->data));
        iRet = 1;
    }

    return iRet;
}

template <class Alloc> int  XMemoryList<Alloc>::verify_mark()
{
    int iRet = 0;
    huge_unit* pCur = m_pHead;

    for (; pCur; )
    {
        iRet += verify_mark(pCur);
        if (IsBadReadPtr(pCur, 4))
        {
            break;
        }
        pCur = pCur->__m_pNext;
    }

    return iRet;
}

template <class Alloc> void XMemoryList<Alloc>::check()
{
    huge_unit* pCur = m_pHead;

    for (; pCur; )
    {
        verify_mark(pCur);
        if (IsBadReadPtr(pCur, 4))
        {
            break;
        }
        if (pCur->used)
        {
            __ReportMemoryLeak(
                "Big memory", 
                pCur->file, 
                pCur->line, 
                pCur->size, 
                (ptrdiff_t)(pCur->data));
        }
        pCur = pCur->__m_pNext;
    }
}

#endif

#if (xDEBUG == xTRUE)
template <class Alloc> void* XMemoryList<Alloc>::allocate(
    unsigned int size, const void* file, unsigned int line)
#else
template <class Alloc> void* XMemoryList<Alloc>::allocate(unsigned int size)
#endif
{
#if (xDEBUG == xTRUE)
    huge_unit* pUnit = (huge_unit*)m_pAlloc->allocate(
        size + sizeof(huge_unit) + sizeof(verify_padding));
    if (!pUnit)
    {
        return 0;
    }
	pUnit->used		= 0;	
#else
    huge_unit* pUnit = (huge_unit*)m_pAlloc->allocate(size + sizeof(huge_unit));
    if (!pUnit)
    {
        return 0;
    }
#endif

    init_unit(pUnit, size);
#if (xDEBUG == xTRUE)
	xAssert(pUnit->used == 0);
    pUnit->file = file;
    // MODIFY
	if (file)
	{
		strncpy(pUnit->file_data, GetPureFileName((const char*)file, 3), DBG_FILE_LEN);
		pUnit->file_data[DBG_FILE_LEN-1]=0;
	}
	else
	{
		pUnit->file_data[0] = 0;
	}
    pUnit->file = pUnit->file_data;

    pUnit->line = line;
    pUnit->used = 1;
#endif

    pUnit->__m_pPrev    = 0;
    XMEMORY_LOCK(m_lock);
    pUnit->__m_pNext        = m_pHead;
    if (m_pHead)
    {
        m_pHead->__m_pPrev  = pUnit;
    }
    else
    {
        m_pTail = pUnit;
    }
    m_pHead = pUnit;
    XMEMORY_UNLOCK(m_lock);
    return pUnit->data;
}
template <class Alloc> void XMemoryList<Alloc>::free(void* p)
{
    huge_unit* pUnit = (huge_unit*)((unsigned int)p - sizeof(huge_unit));

#if (xDEBUG == xTRUE)
    xAssert(pUnit->used);
    verify_mark(pUnit);
#endif

    XMEMORY_LOCK(m_lock);
    if (pUnit->__m_pPrev)
    {
        pUnit->__m_pPrev->__m_pNext = pUnit->__m_pNext;
    }
    if (pUnit->__m_pNext)
    {
        pUnit->__m_pNext->__m_pPrev = pUnit->__m_pPrev;
    }
    if (m_pHead == pUnit)
    {
        m_pHead = m_pHead->__m_pNext;
    }
    if (m_pTail == pUnit)
    {
        m_pTail = m_pTail->__m_pPrev;
    }
    XMEMORY_UNLOCK(m_lock);
    m_pAlloc->free(pUnit);
}

