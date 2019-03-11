//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	MemMoniter.h
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#include "../../Include/IMemPort.h"
#include "MemMoniter.h"

#if (xDEBUG == xTRUE)
XALGO_API XMemMoniter::XMemMoniter()
{
    m_nCurMemObj        = 0;
    m_nCurMemUsed       = 0;
    m_nMaxMemObj        = 0;
    m_nMaxMemUsed       = 0;
    m_nTotalMemUsed     = 0;
    m_nTotalMemFreed    = 0;
    m_nTotalMemObj      = 0;
    m_nTotalMemObjFreed = 0;
}

XALGO_API XMemMoniter::~XMemMoniter()
{
    //DumpInfo();
}

XALGO_API void XMemMoniter::OnNew(unsigned int size)
{
    ++m_nTotalMemObj;
    m_nTotalMemUsed += size;

    ++m_nCurMemObj;
    m_nCurMemUsed += size;

    if (m_nCurMemObj > m_nMaxMemObj)
    {
        m_nMaxMemObj = m_nCurMemObj;
    }
    if (m_nCurMemUsed > m_nMaxMemUsed)
    {
        m_nMaxMemUsed = m_nCurMemUsed;
    }
}

XALGO_API void XMemMoniter::OnDelete(unsigned int size)
{
    --m_nCurMemObj;
    m_nCurMemUsed -= size;

    ++m_nTotalMemObjFreed;
    m_nTotalMemFreed += size;
}

XALGO_API void XMemMoniter::DumpSimpleInfo()
{
}

XALGO_API void XMemMoniter::DumpInfo()
{
    char szToOutput[1024];
    char szWarning[256];

    szWarning[0] = xSTREND;
    if (m_nTotalMemObj > m_nTotalMemObjFreed || 
        m_nTotalMemUsed > m_nTotalMemFreed)
    {
        _snprintf(
            szWarning, 256, 
            "\r\nWarning : There are %d memory objects in %d bytes are not freed!\r\n", 
            m_nTotalMemObj - m_nTotalMemObjFreed, 
            m_nTotalMemUsed - m_nTotalMemFreed);
        szWarning[255] = xSTREND;
    }

    _snprintf(
        szToOutput, 1024, 
        "\r\n\r\n-----------------------------------------------------------------\r\n"
        "                   Memory Manager Report\r\n"
        "-----------------------------------------------------------------\r\n"
        "Current Memory Object          : %d\r\n"
        "Current Memory Used            : %d bytes\r\n"
        "Maximal Memory Object Allocated: %d\r\n"
        "Maximal Memory Used            : %d bytes, %f kb, %f mb\r\n"
        "Total Memory Used              : %d bytes, %f kb, %f mb\r\n"
        "Total Memory Freed             : %d bytes, %f kb, %f mb\r\n"
        "Total Memory Object Allocated  : %d\r\n"
        "Total Memory Object Freed      : %d\r\n%s"
        "-----------------------------------------------------------------\r\n\r\n", 
        m_nCurMemObj, 
        m_nCurMemUsed, 
        m_nMaxMemObj, 
        m_nMaxMemUsed, 
        m_nMaxMemUsed / 1024.0f, 
        m_nMaxMemUsed / (1024.0f * 1024.0f), 
        m_nTotalMemUsed, 
        m_nTotalMemUsed / 1024.0f, 
        m_nTotalMemUsed / (1024.0f * 1024.0f), 
        m_nTotalMemFreed, 
        m_nTotalMemFreed / 1024.0f, 
        m_nTotalMemFreed / (1024.0f * 1024.0f), 
        m_nTotalMemObj, 
        m_nTotalMemObjFreed, 
        szWarning);
    szToOutput[1023] = xSTREND;

    OutputMemoryDebugInfo( szToOutput );
}

#endif
