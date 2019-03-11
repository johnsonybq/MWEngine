//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	MemPool.h
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#pragma once 

#include "MemBase.h"
#include "MemLock.h"
#include "MemArray.h"
#include "MemUnit.h"

template <class Alloc> struct XMemory_Pool
{
    inline                  XMemory_Pool();
    inline                 ~XMemory_Pool();

    inline void             Destroy();
    inline void             create(
        Alloc* pAlloc, size_t unitsize, size_t poolunit);

private:
    inline void             init_unit(void* pSmallUnit);
    inline small_unit*      get_nextunit(void* pSmallUnit);
#if (xDEBUG == xTRUE)
    inline verify_padding*  get_ccback(void* pSmallUnit);
    inline int              verify_mark(void *pSmallUnit);
#endif

public:
#if (xDEBUG == xTRUE)
    int                     verify_mark();
    void                    check();
    void                    assertValid();
    void*                   allocate(
        size_t size, const void* file = 0, unsigned int line = 0);
#else
    void*                   allocate(size_t size);
#endif
	void                    free(void* p);
	void                    free(void* p, const void* file, unsigned int line);

    typedef XSimplArray<void*, XDefAllocater> Addr_Array;

#ifdef __MULTI_THREAD__
    XLock                   m_lock;
#endif
    size_t                  m_unitsize;
    size_t                  m_poolunit;
    size_t                  m_actual_size;
    Alloc*                  m_pAlloc;
    small_unit*             m_pHeader;
    Addr_Array              m_allocated;

    unsigned int            m_nObjects;
};

template <class Alloc> inline XMemory_Pool<Alloc>::XMemory_Pool()
{
    m_unitsize      = 0;
    m_actual_size   = 0;
    m_poolunit      = 0;
    m_pAlloc        = 0;
    m_pHeader       = 0;

    m_nObjects      = 0;
}

template <class Alloc> inline XMemory_Pool<Alloc>::~XMemory_Pool()
{
    Destroy();
}

template <class Alloc> inline void XMemory_Pool<Alloc>::Destroy()
{
    XMEMORY_LOCK(m_lock);
#if (xDEBUG == xTRUE)
    check();
#endif
    for (unsigned int i = 0; i < m_allocated.GetSize(); ++i)
    {
        m_pAlloc->free(m_allocated[i]);
    }
    m_allocated.RemoveAll();
    m_unitsize      = 0;
    m_actual_size   = 0;
    m_poolunit      = 0;
    m_pHeader       = xNULL;
    m_nObjects      = 0;
    XMEMORY_UNLOCK(m_lock);
}

template <class Alloc> inline void XMemory_Pool<Alloc>::create(
    Alloc* pAlloc, size_t unitsize, size_t poolunit)
{
    m_pAlloc        = pAlloc;
    m_unitsize      = unitsize;
    m_poolunit      = poolunit;

#if (xDEBUG == xTRUE)
    m_actual_size   = 
        m_unitsize + 
        sizeof(small_unit) - 
        sizeof(small_unit*) + 
        sizeof(verify_padding);
#else
    m_actual_size   = 
        m_unitsize + 
        sizeof(small_unit) - 
        sizeof(small_unit*);
#endif
}

template <class Alloc> inline void XMemory_Pool<Alloc>::init_unit(void* p)
{
	(reinterpret_cast<small_unit*>(p))->size        = m_unitsize;
#if (xDEBUG == xTRUE)
	xAssert((reinterpret_cast<small_unit*>(p))->used == 0);
    (reinterpret_cast<small_unit*>(p))->file        = 0;
    (reinterpret_cast<small_unit*>(p))->line        = 0;
    (reinterpret_cast<small_unit*>(p))->used        = 0;
    (reinterpret_cast<small_unit*>(p))->front_verify.init();
    (*get_ccback(p)).init();
#endif
}

template <class Alloc> inline small_unit* XMemory_Pool<Alloc>::get_nextunit(void* p)
{
    return reinterpret_cast<small_unit*>
        (reinterpret_cast<unsigned int>(p) + m_actual_size);
}

#if (xDEBUG == xTRUE)
template <class Alloc> inline verify_padding* XMemory_Pool<Alloc>::get_ccback(void* p)
{
    return reinterpret_cast<verify_padding*>
        (reinterpret_cast<unsigned int>(p) + m_actual_size - sizeof(verify_padding));
}

template <class Alloc> inline int  XMemory_Pool<Alloc>::verify_mark(void* p)
{
    verify_padding* pcc_back = get_ccback(p);

    int iRet = 0;
    register small_unit* pUnit = reinterpret_cast<small_unit*>(p);
    if (IsBadWritePtr(pUnit, 4))
    {
        __ReportMarkBeyond(
            "Memory Pool crash.", 
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
            "Memory Pool Front Verify Code", 
            pUnit->file, 
            pUnit->line, 
            pUnit->size, 
            (ptrdiff_t)(pUnit->data));
        iRet = 1;
    }
    else if (!pcc_back->IsVailidCode())
    {
        __ReportMarkBeyond(
            "Memory Pool Back Verify Code", 
            pUnit->file, 
            pUnit->line, 
            pUnit->size, 
            (ptrdiff_t)(pUnit->data));
        iRet = 1;
    }

    return iRet;
}

template <class Alloc> int  XMemory_Pool<Alloc>::verify_mark()
{
    int iRet = 0;
    for (unsigned int i = 0; i < m_allocated.GetSize(); ++i)
    {
        small_unit* pUnit = reinterpret_cast<small_unit*>(m_allocated[i]);
        for (unsigned int j = 0; j < m_poolunit; ++j)
        {
            iRet += verify_mark(pUnit);
            if (IsBadWritePtr(pUnit, 4))
            {
                break;
            }
            if (!pUnit->used)
            {
                if (pUnit->next && IsBadWritePtr(pUnit->next, 4))
                {
                    __ReportMarkBeyond(
                        "Memory Pool crash.", 
                        pUnit->file, 
                        pUnit->line, 
                        pUnit->size, 
                        (ptrdiff_t)(pUnit->data));
                    iRet += 1;
                }
            }
            pUnit = get_nextunit(pUnit);
        }
    }
    if (iRet)
    {
        xAssert(FALSE);
    }
    return iRet;
}

template <class Alloc> void XMemory_Pool<Alloc>::check()
{
    for (unsigned int i = 0; i < m_allocated.GetSize(); ++i)
    {
        small_unit* pUnit = reinterpret_cast<small_unit*>(m_allocated[i]);
        for (unsigned int j = 0; j < m_poolunit; ++j)
        {
            verify_mark(pUnit);
            if (IsBadWritePtr(pUnit, 4))
            {
                break;
            }
            else
            {
                if (pUnit->used)
                {
                    __ReportMemoryLeak(
                        "Memory Pool", 
                        pUnit->file, 
                        pUnit->line, 
                        pUnit->size, 
                        (ptrdiff_t)(pUnit->data));
                }
                else if (pUnit->next && IsBadWritePtr(pUnit->next, 4))
                {
                    __ReportMarkBeyond(
                        "Memory Pool crash.", 
                        pUnit->file, 
                        pUnit->line, 
                        pUnit->size, 
                        (ptrdiff_t)(pUnit->data));
                }
                pUnit = get_nextunit(pUnit);
            }
        }
    }
}

template <class Alloc> void XMemory_Pool<Alloc>::assertValid()
{
    if (m_pHeader)
    {
        xAssert(!IsBadWritePtr(m_pHeader, NULL));
    }
    for (x_uint i = 0; i < m_allocated.GetSize(); ++i)
    {
        xAssert(!IsBadWritePtr(m_allocated[i], NULL));
    }
}
#endif

#if (xDEBUG == xTRUE)
template <class Alloc> void* XMemory_Pool<Alloc>::allocate(
    size_t size, const void* file, unsigned int line)
#else
template <class Alloc> void* XMemory_Pool<Alloc>::allocate(size_t size)
#endif
{
    XMEMORY_LOCK(m_lock);


#if (xDEBUG == xTRUE)
    ++m_nObjects;
#endif

    small_unit* p;
    unsigned int toAllocate;
    if (m_pHeader == NULL)
    {
        toAllocate = m_actual_size * m_poolunit;
        m_pHeader = (small_unit*)m_pAlloc->allocate(toAllocate);
        m_allocated.Add(m_pHeader);

        p = m_pHeader;
        for (unsigned int i = 1; i < m_poolunit; ++i)
        {
#if (xDEBUG == xTRUE)
			p->used = 0;
#endif
            init_unit(p);
            p = p->next = get_nextunit(p);
		}
#if (xDEBUG == xTRUE)
		p->used = 0;
#endif
        init_unit(p);
        p->next = NULL;
    }

    p = m_pHeader;
    m_pHeader = m_pHeader->next;

    XMEMORY_UNLOCK(m_lock);
#if (xDEBUG == xTRUE)
	xAssert(p->used == 0);
    p->used = 1;
    p->file = file;
    // MODIFY
	if (file)
    {
		strncpy(p->file_data, GetPureFileName((const char*)file, 3), DBG_FILE_LEN);
		p->file_data[DBG_FILE_LEN-1]=0;
	}
	else
	{
		p->file_data[0] = 0;
	}
    p->file = p->file_data;

    p->line = line;
#endif
    p->size = size;

    return p->data;
}

template <class Alloc> void XMemory_Pool<Alloc>::free(
	void* p, const void* file, unsigned int line)
{
	XMEMORY_LOCK(m_lock);

#if (xDEBUG == xTRUE)
	--m_nObjects;
#endif

	small_unit* pUnit = 
		reinterpret_cast<small_unit*>
		((unsigned int)p - sizeof(small_unit) + sizeof(small_unit*));
#if (xDEBUG == xTRUE)
	xAssert(pUnit->used);
	verify_mark(pUnit);
	pUnit->used = 0;
	pUnit->file = file;
	pUnit->line = line;
#endif
	pUnit->next = m_pHeader;
	m_pHeader = pUnit;

	XMEMORY_UNLOCK(m_lock);
}
template <class Alloc> void XMemory_Pool<Alloc>::free(void* p)
{
	free(p, NULL, 0);
//    XMEMORY_LOCK(m_lock);
//
//#if (xDEBUG == xTRUE)
//    --m_nObjects;
//#endif
//
//    small_unit* pUnit = 
//        reinterpret_cast<small_unit*>
//        ((unsigned int)p - sizeof(small_unit) + sizeof(small_unit*));
//#if (xDEBUG == xTRUE)
//    xAssert(pUnit->used);
//    verify_mark(pUnit);
//    pUnit->used = 0;
//#endif
//    pUnit->next = m_pHeader;
//    m_pHeader = pUnit;
//
//    XMEMORY_UNLOCK(m_lock);
}
