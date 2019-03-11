//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	MemBase.h
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#pragma once

// ----------------------------------------------------------------------------
// over 256 type name
#pragma warning(disable:4786)
// ----------------------------------------------------------------------------
#define  WIN32_LEAN_AND_MEAN
// ----------------------------------------------------------------------------
#include <tchar.h>
#include <malloc.h>
#include <cstdio>
#include <cstdlib>
#include <cwchar>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cfloat>
#include <cmath>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <new>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <bitset>
#include <xtree>

#ifndef POINTER_64 
#define POINTER_64 __ptr64
#endif
#include <windows.h>

// ----------------------------------------------------------------------------
using namespace std;
// ----------------------------------------------------------------------------

#ifndef     xNULL
#define     xNULL           0
#endif

#ifndef     xTRUE
#define     xTRUE           1
#endif

#ifndef     xFALSE
#define     xFALSE          0
#endif

#ifndef     xSTREND
#define     xSTREND         0
#endif

#define     xUNICODE        xFALSE



// ----------------------------------------------------------------------------
// Supported Operation Systems
// ----------------------------------------------------------------------------
#define     xOS_WIN32       (0x01000000)
#define     xOS_WIN95       (1 | xOS_WIN32)
#define     xOS_WIN98       (2 | xOS_WIN32)
#define     xOS_WINNT4      (3 | xOS_WIN32)
#define     xOS_WIN2K       (4 | xOS_WIN32)
#define     xOS_WINXP       (5 | xOS_WIN32)

#define     xOS_WIN64       (0x02000000)

#define     xOS_LINUX       (0x02000000)
#define     xOS_UNIX        (0x04000000)
#define     xOS_APPLE       (0x08000000)
#define     xOS_OS2         (0x10000000)

#define     xOS_UNKNOWN     (0x00000000)


#if         defined(__WIN32__) || defined(_WIN32)
#define     xOS_PLATFORM    xOS_WIN32
#elif       defined(__APPLE_CC__)
#define     xOS_PLATFORM    xOS_APPLE
#else
#define     xOS_PLATFORM    xOS_UNIX
#endif


// ----------------------------------------------------------------------------
// Supported Compiler Types
// ----------------------------------------------------------------------------
#define     xCP_ICL         (0x00000005)
#define     xCP_MSVC        (0x0000000A)
#define     xCP_BCB         (0x00000014)


#if         defined(__INTEL_COMPILER)
#define     xCP_COMPILER    xCP_ICL
#define     xCP_VERSION     12000000
#elif       defined(_MSC_VER)
#define     xCP_COMPILER    xCP_MSVC
#define     xCP_VERSION     _MSC_FULL_VER
#elif       defined(BCB)
#define     xCP_COMPILER    xCP_BCB
#define     xCP_VERSION     __BCPLUSPLUS__
#else
#error      "unknown compiler !"
#endif



// ----------------------------------------------------------------------------
// Pre - Define Unicode Config
// ----------------------------------------------------------------------------
#if         (xUNICODE == xTRUE)
#if         (!defined(UNICODE))
#define     UNICODE
#endif
#if         (!defined(_UNICODE))
#define     _UNICODE
#endif
#else
#if         (defined(UNICODE))
#undef      UNICODE
#endif
#if         (defined(_UNICODE))
#undef      _UNICODE
#endif
#endif



// ----------------------------------------------------------------------------
// For Debug
// ----------------------------------------------------------------------------
#if         (xCP_COMPILER == xCP_ICL) || (xCP_COMPILER == xCP_MSVC)

#if         (defined(_DEBUG))
#define     xDEBUG          xTRUE
#define     xNDEBUG         xFALSE
#else
#define     xDEBUG          xFALSE
#define     xNDEBUG         xTRUE
#endif

#else

#if         (defined(DEBUG))
#define     xDEBUG          xTRUE
#define     xNDEBUG         xFALSE
#else
#define     xDEBUG          xFALSE
#define     xNDEBUG         xTRUE
#endif

#endif


// ----------------------------------------------------------------------------
// Macros
// ----------------------------------------------------------------------------
#if         (xCP_COMPILER == xCP_ICL) || (xCP_COMPILER == xCP_MSVC)
#define     xDllImport      __declspec(dllimport)
#define     xDllExport      __declspec(dllexport)
#define     xNoVtalbe       __declspec(novtable)
#define     xProperty(x)    __declspec(property(x))
#define     xAsmCode(c)     _asm _emit c
#elif       (xCP_COMPILER == xCP_BCB)
#define     xDllImport      __declspec(dllimport)
#define     xDllExport      __declspec(dllexport)
#define     xNoVtalbe       __declspec(novtable)
#define     xProperty(x)    __Property(x)
#define     xAsmCode(c)     _asm {db c};
#endif

#define     xForceInline    __forceinline
#define     xInline         inline
#define     xInterface      struct
#define     xConst          const



// ----------------------------------------------------------------------------
#define     xMakestring(x)  (#x)
#define     xNothing
#define     xComma          ,
#define     xLeftbracket    (
#define     xRightbracket   )



// over 256 type name
#pragma warning(disable:4786)

// 'type cast' : pointer truncation from '' to ''
#pragma warning(disable:4311)

// 'type cast' : conversion from '' to '' of greater size
#pragma warning(disable:4312)

// argument' : conversion from '' to '', possible loss of data
#pragma warning(disable:4267)

// nonstandard extension used : zero-sized array in struct/union
//#pragma warning(disable:4200)


// ----------------------------------------------------------------------------
#define XALGO_BEGIN namespace XAlgorithm {
#define XALGO_END   }

#define XALGO_API

#define xAssert     assert


typedef void                    x_void;
typedef char                    x_char;
typedef short                   x_short;
typedef int                     x_int;
typedef long                    x_long;
typedef int                     x_bool;

typedef unsigned char           x_uchar;
typedef unsigned short          x_ushort;
typedef x_ushort                x_wchar;
typedef unsigned int            x_uint;
typedef unsigned long           x_ulong;

#if (xUNICODE == xTRUE)
typedef x_wchar                 x_tchar;
#else
typedef x_char                  x_tchar;
#endif

typedef x_char                  x_int8;
typedef x_short                 x_int16;
typedef x_int                   x_int32;
typedef __int64                 x_int64;
typedef unsigned char           x_uint8;
typedef unsigned short          x_uint16;
typedef unsigned long           x_uint32;
typedef unsigned __int64        x_uint64;

typedef x_uint                  x_size;
typedef x_int                   x_ptrdiff;
typedef x_int32                 x_error;

typedef x_uint8                 x_byte;
typedef x_uint16                x_word;
typedef x_uint32                x_dword;
typedef x_uint64                x_qword;

typedef float                   x_float;
typedef double                  x_double;
typedef long double             x_ldouble;
typedef float                   x_float32;
typedef double                  x_float64;

typedef x_void*                 x_pvoid;
typedef x_char*                 x_pchar;
typedef x_pchar                 x_pstr;
typedef x_wchar*                x_pwchar;
typedef x_pwchar                x_pwstr;
typedef x_tchar*                x_ptchar;
typedef x_ptchar                x_ptstr;
typedef x_short*                x_pshort;
typedef x_int*                  x_pint;
typedef x_long*                 x_plong;
typedef x_uchar*                x_puchar;
typedef x_ushort*               x_pushort;
typedef x_uint*                 x_puint;
typedef x_ulong*                x_pulong;

typedef x_int8*                 x_pint8;
typedef x_int16*                x_pint16;
typedef x_int32*                x_pint32;
typedef x_int64*                x_pint64;
typedef x_uint8*                x_puint8;
typedef x_uint16*               x_puint16;
typedef x_uint32*               x_puint32;
typedef x_uint64*               x_puint64;

typedef x_byte*                 x_pbyte;
typedef x_word*                 x_pword;
typedef x_dword*                x_pdword;
typedef x_qword*                x_pqword;

typedef x_float*                x_pfloat;
typedef x_double*               x_pdouble;
typedef x_ldouble*              x_pldouble;
typedef x_float32*              x_pfloat32;
typedef x_float64*              x_pfloat64;

typedef xConst x_void*          x_pcvoid;
typedef xConst x_char*          x_pcchar;
typedef xConst x_char*          x_pcstr;
typedef xConst x_wchar*         x_pcwchar;
typedef xConst x_wchar*         x_pcwstr;
typedef xConst x_tchar*         x_pctchar;
typedef xConst x_tchar*         x_pctstr;
typedef xConst x_short*         x_pcshort;
typedef xConst x_int*           x_pcint;
typedef xConst x_long*          x_pclong;
typedef xConst x_uchar*         x_pcuchar;
typedef xConst x_ushort*        x_pcushort;
typedef xConst x_uint*          x_pcuint;
typedef xConst x_ulong*         x_pculong;

typedef xConst x_int8*          x_pcint8;
typedef xConst x_int16*         x_pcint16;
typedef xConst x_int32*         x_pcint32;
typedef xConst x_int64*         x_pcint64;
typedef xConst x_uint8*         x_pcuint8;
typedef xConst x_uint16*        x_pcuint16;
typedef xConst x_uint32*        x_pcuint32;
typedef xConst x_uint64*        x_pcuint64;

typedef xConst x_byte*          x_pcbyte;
typedef xConst x_word*          x_pcword;
typedef xConst x_dword*         x_pcdword;
typedef xConst x_qword*         x_pcqword;

typedef xConst x_float*         x_pcfloat;
typedef xConst x_double*        x_pcdouble;
typedef xConst x_ldouble*       x_pcldouble;
typedef xConst x_float32*       x_pcfloat32;
typedef xConst x_float64*       x_pcfloat64;




// ----------------------------------------------------------------------------
#define xMAX_INT8               127
#define xMAX_INT16              32767
#define xMAX_INT32              2147483647
#define xMAX_INT64              9223372036854775807
#define xMAX_UINT8              255
#define xMAX_UINT16             65535
#define xMAX_UINT32             4294967295
#define xMAX_UINT64             18446744073709551615

#define xMIN_INT8               -128
#define xMIN_INT16              -32768
#define xMIN_INT32              -2147483648
#define xMIN_INT64              -9223372036854775808
#define xMIN_UINT8              0
#define xMIN_UINT16             0
#define xMIN_UINT32             0
#define xMIN_UINT64             0

#define xMAX_CHAR               xMAX_INT8
#define xMAX_SHORT              xMAX_INT16
#define xMAX_INT                xMAX_INT32
#define xMAX_LONG               xMAX_INT32
#define xMAX_UCHAR              xMAX_UINT8
#define xMAX_USHORT             xMAX_UINT16
#define xMAX_UINT               xMAX_UINT32
#define xMAX_ULONG              xMAX_UINT32

#define xMIN_CHAR               xMIN_INT8
#define xMIN_SHORT              xMIN_INT16
#define xMIN_INT                xMIN_INT32
#define xMIN_LONG               xMIN_INT32
#define xMIN_UCHAR              xMIN_UINT8
#define xMIN_USHORT             xMIN_UINT16
#define xMIN_UINT               xMIN_UINT32
#define xMIN_ulong              xMIN_UINT32

#define xMAX_SIZE               xMAX_UINT32
#define xMIN_SIZE               xMIN_UINT32

#define xMAX_WCHAR              xMAX_UINT16
#define xMIN_WCHAR              xMIN_UINT16
#if (xUNICODE == xTRUE)
#define xMAX_TCHAR              xMAX_WCHAR
#define xMIN_TCHAR              xMIN_WCHAR
#else
#define xMAX_TCHAR              xMAX_CHAR
#define xMIN_TCHAR              xMIN_CHAR
#endif

#define xMAX_QWORD              xMAX_UINT64
#define xMAX_DWORD              xMAX_UINT32
#define xMAX_WORD               xMAX_UINT16
#define xMAX_BYTE               xMAX_UINT8
#define xMIN_QWORD              xMIN_UINT64
#define xMIN_DWORD              xMIN_UINT32
#define xMIN_WORD               xMIN_UINT16
#define xMIN_BYTE               xMIN_UINT8

#define xMAX_FLOAT              ((x_float)3.4E+38)
#define xMAX_DOUBLE             ((x_double)1.7E+308)
#define xMIN_FLOAT              ((x_float)3.4E-38)
#define xMIN_DOUBLE             ((x_double)1.7E-308)

#define xMAX_PATH               256

#define __MULTI_THREAD__

inline const char* GetPureFileName(const char* szFile, size_t nMaxPath)
{
    if (!szFile)
    {
        return "";
    }
    size_t nLen = strlen(szFile);

    const char* pEnd = szFile + nLen;

    size_t nCount = 0;
    for (; pEnd != szFile; --pEnd)
    {
        if (*pEnd == '\\')
        {
            ++nCount;
            if (nCount > nMaxPath)
            {
                ++pEnd;
                break;
            }
        }
    }
    return pEnd;
}
