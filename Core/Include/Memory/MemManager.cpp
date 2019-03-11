//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	MemManager.cpp
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#include "MemManager.h"
#include "../../Include/IMemPort.h"
// ----------------------------------------------------------------------------

XALGO_API XMemory* __GetMemoryManager()
{
    static XMemory s_init;
    return &s_init;
}

MemoryManager_Impl::MemoryManager_Impl()
{
    __GetMemoryManager();
}

MemoryManager_Impl::~MemoryManager_Impl()
{

}

void  MemoryManager_Impl::GlobalFree()
{
    __GetMemoryManager()->Destroy();
    __GetMemoryManager()->DumpInfo();
}

void* MemoryManager_Impl::Allocate(size_t nSize, const char* szFile, size_t nLine)
{
#ifdef _DEBUG
    return __GetMemoryManager()->allocate(nSize, szFile, nLine);
#else
    return __GetMemoryManager()->allocate(nSize);
#endif
}

void* MemoryManager_Impl::Reallocate(void* pPtr, size_t nSize, const char* szFile, size_t nLine)
{
    if (nSize == 0)
    {
        __GetMemoryManager()->free(pPtr);
        return NULL;
    }
    if (!pPtr)
    {
        return Allocate(nSize, szFile, nLine);
    }
    small_unit* pUnit = 
        reinterpret_cast<small_unit*>(
        reinterpret_cast<unsigned int>(pPtr) - 
        sizeof(small_unit) + 
        sizeof(small_unit*));

    void* pNewAddr = Allocate(nSize + sizeof(unsigned int), szFile, nLine);
    if (!pNewAddr)
    {
        return 0;
    }
    memcpy(pNewAddr, pPtr, min(nSize, pUnit->size - sizeof(unsigned int)));
    Free(pPtr, szFile, nLine);
    return pNewAddr;
}

void MemoryManager_Impl::Free(void* pPtr, const char* szFile, size_t nLine)
{
    __GetMemoryManager()->free(pPtr);
}
void MemoryManager_Impl::AssertValid()
{
#ifdef _DEBUG
    __GetMemoryManager()->AssertValid();
#endif
}

XALGO_API XMemory::XMemory()
{
    m_globalPool.create(
        &m_defAlloc, 
        XMemory::_ChunkSize, 
        XMemory::_BlockSize / XMemory::_ChunkSize);

    unsigned int subpool_size = XMemory::_AlignByte;
    for (int i = 0; i < XMemory::_PoolCount; ++i)
    {
#if (xDEBUG == xTRUE)
        m_subPool[i].create(
            &m_globalPool, 
            subpool_size, 
            XMemory::_ChunkSize / 
            (subpool_size + 
            sizeof(small_unit) - 
            sizeof(small_unit*) + 
            sizeof(verify_padding)));
#else
        m_subPool[i].create(
            &m_globalPool, 
            subpool_size, 
            XMemory::_ChunkSize / 
            (subpool_size + 
            sizeof(small_unit) - 
            sizeof(small_unit*)));
#endif
        subpool_size += XMemory::_AlignByte;
    }

    m_hugePool.create(&m_defAlloc);
}

XALGO_API XMemory::~XMemory()
{
    Destroy();
}

XALGO_API void XMemory::Destroy()
{
    OutputMemoryDebugInfo( "********************** Memory log **********************" );

    for (int i = 0; i < XMemory::_PoolCount; ++i)
    {
        m_subPool[i].Destroy();
    }
    m_globalPool.Destroy();
    m_hugePool.Destroy();

#ifdef _DEBUG
	if( GetOutputTimes() > 1 )
	{
		char Buffer[256];
		::GetCurrentDirectoryA( 256, Buffer );
		std::string AbsPath = "notepad ";
		AbsPath += Buffer;
		AbsPath += "/MemoryLog.txt";
		WinExec( AbsPath.c_str(), SW_SHOWNORMAL );
	}
#endif
}

#if (xDEBUG == xTRUE)
XALGO_API void* XMemory::allocate(unsigned int size, const void* file, unsigned int line)
#else
XALGO_API void* XMemory::allocate(unsigned int size)
#endif
{
    xAssert(size);

#if (xDEBUG == xTRUE && defined(__MULTI_THREAD__))
    XLock_Section(m_lock);
#endif

#if (xDEBUG == xTRUE)
    m_moniter.OnNew(size);
#endif

    if (size <= XMemory::_MaxPoolSize)
    {
        int index = (size - 1) / XMemory::_AlignByte;
#if (xDEBUG == xTRUE)
        void* pRet = m_subPool[index].allocate(size, file, line);
#if (defined(__MULTI_THREAD__))
        XUnlock_Section(m_lock);
#endif
        return pRet;
#else
        return m_subPool[index].allocate(size);
#endif
    }
    else
    {
#if (xDEBUG == xTRUE)
        void* pRet = m_hugePool.allocate(size, file, line);
#if (defined(__MULTI_THREAD__))
        XUnlock_Section(m_lock);
#endif
        return pRet;
#else
        return m_hugePool.allocate(size);
#endif

    }
}

XALGO_API void XMemory::free(void* p)
{
#if (xDEBUG == xTRUE && defined(__MULTI_THREAD__))
    XLock_Section(m_lock);
#endif

    small_unit* pUnit = 
        reinterpret_cast<small_unit*>(
        reinterpret_cast<unsigned int>(p) - 
        sizeof(small_unit) + 
        sizeof(small_unit*));

#if (xDEBUG == xTRUE)
    m_moniter.OnDelete(pUnit->size);
#endif

    if (pUnit->size <= XMemory::_MaxPoolSize)
    {
        m_subPool[(pUnit->size-1) / XMemory::_AlignByte].free(p);
    }
    else
    {
        m_hugePool.free(p);
    }
#if (xDEBUG == xTRUE && defined(__MULTI_THREAD__))
    XUnlock_Section(m_lock);
#endif
}

#if (xDEBUG == xTRUE)
XALGO_API int XMemory::VerifyMark()
{
    int iRet = 0;
    for (int i = 0; i < XMemory::_PoolCount; ++i)
    {
        iRet += m_subPool[i].verify_mark();
    }
    iRet += m_hugePool.verify_mark();

    return iRet;
}
XALGO_API void XMemory::AssertValid()
{
#if (xDEBUG == xTRUE && defined(__MULTI_THREAD__))
    XLock_Section(m_lock);
#endif
    int iRet = VerifyMark();
    xAssert(iRet == 0);             // 如果断言不成功，说明出现了内存越界。
    m_globalPool.assertValid();
    for (int i = 0; i < XMemory::_PoolCount; ++i)
    {
        m_subPool[i].assertValid();
    }
#if (xDEBUG == xTRUE && defined(__MULTI_THREAD__))
    XUnlock_Section(m_lock);
#endif
}
#endif

// ----------------------------------------------------------------------------
static XMemoryInit  s_memInit;
XALGO_API XMemoryInit XMemoryInit::sm_init;
XALGO_API XMemoryInit  g_init;
