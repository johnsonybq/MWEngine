//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	MemMoniter.h
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#pragma once

#include "MemUnit.h"

#if (xDEBUG == xTRUE)
struct XMemMoniter
{
    XALGO_API  XMemMoniter();
    XALGO_API ~XMemMoniter();

    XALGO_API void  OnNew(unsigned int size);
    XALGO_API void  OnDelete(unsigned int size);
    XALGO_API void  DumpInfo();
    XALGO_API void  DumpSimpleInfo();

    unsigned int    m_nCurMemObj;
    unsigned int    m_nCurMemUsed;
    unsigned int    m_nMaxMemObj;
    unsigned int    m_nMaxMemUsed;
    unsigned int    m_nTotalMemUsed;
    unsigned int    m_nTotalMemFreed;
    unsigned int    m_nTotalMemObj;
    unsigned int    m_nTotalMemObjFreed;
};
#endif
