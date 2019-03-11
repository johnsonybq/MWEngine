//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	IMemMan.h
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#pragma once

class IMemoryManager
{
public:
    IMemoryManager() {}
    virtual ~IMemoryManager() {}

    virtual void* Allocate(size_t nSize, const char* szFile = 0, size_t nLine = 0) = 0;
    virtual void* Reallocate(void* pPtr, size_t nSize, const char* szFile = 0, size_t nLine = 0) = 0;
    virtual void  Free(void* pPtr, const char* szFile = 0, size_t nLine = 0) = 0;
    virtual void  AssertValid() = 0;
    virtual void  GlobalFree() = 0;
};

#define PADDING_SIZE    (16 / sizeof(unsigned int))

struct _Padding {
    unsigned int    _CODE[PADDING_SIZE];
};

#pragma warning(disable : 4200)
#pragma pack(push)
#pragma pack(1)
#ifdef _DEBUG
struct _SmallUnit_t {
    const void*         file;
    unsigned int        line;
    unsigned int        used;
    unsigned int        size;
    unsigned int        count;
    _Padding            front_verify;
    union
    {
        _SmallUnit_t*   next;
        char            data[4];
    };
};
struct _HugeUnit_t
{
    _HugeUnit_t*        __m_pPrev;
    _HugeUnit_t*        __m_pNext;
    const void*         file;
    unsigned int        line;
    unsigned int        used;
    unsigned int        size;
    unsigned int        count;
    _Padding            front_verify;
    char                data[0];
};
#else
struct _SmallUnit_t
{
    unsigned int        size;
    unsigned int        count;
    union
    {
        _SmallUnit_t*   next;
        char            data[4];
    };
};
struct _HugeUnit_t
{
    _HugeUnit_t*        __m_pPrev;
    _HugeUnit_t*        __m_pNext;
    unsigned int        size;
    unsigned int        count;
    char                data[0];
};
#endif
#pragma pack(pop)
#pragma warning(default : 4200)


