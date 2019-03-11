//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	MemUnit.h
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#pragma once

#include "MemBase.h"

#define DBG_FILE_LEN        64

#pragma warning(disable : 4200)
#pragma pack(push)
#pragma pack(1)
#if (xDEBUG == xTRUE)
struct verify_padding
{
    enum
    {
        padding_size    = 16 / sizeof(unsigned int), 
    };
    unsigned int  verify_code[padding_size];

    void            init()
    {
        for (int i = 0; i < padding_size; ++i)
        {
            verify_code[i] = 0x01234567;
        }
    }
    int             IsVailidCode()
    {
        for (int i = 0; i < padding_size; ++i)
        {
            if (verify_code[i] != 0x01234567)
            {
                return 0;
            }
        }
        return 1;
    }
};
struct small_unit
{
    const void*     file;
    unsigned int    line;
    // MODIFY
    char            file_data[DBG_FILE_LEN];
    unsigned int    used;
    unsigned int    size;
    unsigned int    count;
    verify_padding  front_verify;
    union
    {
        small_unit* next;
        char        data[4];
    };
};
struct huge_unit
{
    huge_unit*      __m_pPrev;
    huge_unit*      __m_pNext;
    const void*     file;
    unsigned int    line;
    // MODIFY
    char            file_data[DBG_FILE_LEN];
    unsigned int    used;
    unsigned int    size;
    unsigned int    count;
    verify_padding  front_verify;
    char            data[0];
};
#else
struct small_unit
{
    unsigned int    size;
    unsigned int    count;
    union
    {
        small_unit* next;
        char        data[4];
    };
};
struct huge_unit
{
    huge_unit*      __m_pPrev;
    huge_unit*      __m_pNext;
    unsigned int    size;
    unsigned int    count;
    char            data[0];
};
#endif
#pragma pack(pop)
#pragma warning(default : 4200)


struct XDefAllocater
{
#if (xDEBUG == xTRUE)
    void*       allocate(size_t size, const void* f = 0, unsigned int l = 0) const
    {
        void* pRet = ::malloc(size);

        return pRet;
    }
#else
    void*       allocate(size_t size) const
    {
        return ::malloc(size);
    }
#endif
    void        free(void* p) const
    {
        ::free(p);
    }
};

const unsigned int  MEMORY_VERIFY_CODE  = 0xabcdef01;


XALGO_API void __ReportMemoryLeak(
                               const char* szPosition, 
                               const void* szFileName, 
                               unsigned int line, 
                               unsigned int bytes, 
                               ptrdiff_t addr);
XALGO_API void __ReportMarkBeyond(
                               const char* szPosition, 
                               const void* szFileName, 
                               unsigned int line, 
                               unsigned int bytes, 
                               ptrdiff_t addr);

extern void OutputMemoryDebugInfo( const char* szString );
extern int GetOutputTimes( void );
