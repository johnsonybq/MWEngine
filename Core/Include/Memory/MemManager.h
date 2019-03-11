//--------------------------------------------------------------------
//  ��Ȩ����:	
//  �ļ�����:	MemManager.h
//  �ļ�˵��:		
//  ��������:	2012��$��$��
//  -------------------------------------------------------------------
//  �汾��ʷ:
//               Sam(lil) 1.0  2012��$��$�� ������������        
//--------------------------------------------------------------------

#include "MemPool.h"
#include "MemList.h"
#include "MemMoniter.h"
#include "IMemMan.h"

class MemoryManager_Impl : public IMemoryManager
{
public:
    
	MemoryManager_Impl();
	~MemoryManager_Impl();

public:

    virtual void* Allocate(size_t nSize, const char* szFile = 0, size_t nLine = 0);
    virtual void* Reallocate(void* pPtr, size_t nSize, const char* szFile = 0, size_t nLine = 0);
    virtual void  Free(void* pPtr, const char* szFile = 0, size_t nLine = 0);
    virtual void  AssertValid();
    virtual void  GlobalFree();
};

struct XMemory
{
    XALGO_API  XMemory();
    XALGO_API ~XMemory();

    enum
    {
        _BlockSize      = 1024 * 1024,      // ÿ�� 1 M
        _ChunkSize      = 8192,             // 1M ��ÿһ��chunkΪ8192 byte
        _AlignByte      = 4,                // 4 �ֽڶ���
        _MaxPoolSize    = 256,              // ���ڴ������������λ�ֽ���
        _PoolCount      = _MaxPoolSize / _AlignByte, 
    };

    XDefAllocater       m_defAlloc;

    typedef XMemory_Pool<XDefAllocater> XGlobalPool;

    XGlobalPool         m_globalPool;

    typedef XMemory_Pool<XGlobalPool>   XSubPool;

    XSubPool            m_subPool[_PoolCount];

    XMemoryList<XDefAllocater> m_hugePool;

    XLock               m_lock;

#if (xDEBUG == xTRUE)
    XALGO_API void*           allocate(
        unsigned int size, const void* file = 0, unsigned int line = 0);
    XALGO_API int             VerifyMark();
    XALGO_API void            AssertValid();

    XMemMoniter               m_moniter;

    void                      DumpInfo()
    {
        m_moniter.DumpInfo();
    }

#else
    XALGO_API void*           allocate(unsigned int size);
    void                      DumpInfo()
    {
    }
#endif
    XALGO_API void            free(void* p);

    XALGO_API void            Destroy();
};

// ----------------------------------------------------------------------------

XALGO_API XMemory*  __GetMemoryManager();

struct XMemoryInit
{
    XMemoryInit()
    {
        m_pmmanger = __GetMemoryManager();
    }
    XMemory*    m_pmmanger;

    static XALGO_API XMemoryInit  sm_init;
};
extern XALGO_API XMemoryInit  g_init;

inline int xCheckVerifyMark()
{
#if (xDEBUG == xTRUE)
    return __GetMemoryManager()->VerifyMark();
#endif
    return 0;
}

