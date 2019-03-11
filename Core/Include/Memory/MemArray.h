//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	MemArray.h
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#pragma once

#include "MemBase.h"

template <class _T, class _A> class XSimplArray
{
public:

    inline              XSimplArray();
    inline             ~XSimplArray();

public:

    inline unsigned int GetSize() const;
    inline int          GetUpperBound() const;

    inline const _T&    GetAt(unsigned int i) const;
    inline _T&          GetAt(unsigned int i);
    inline void         SetAt(unsigned int i, const _T& element);

    inline const _T&    operator[](unsigned int i) const;
    inline _T&          operator[](unsigned int i);

    inline void         RemoveAll();
    inline void         Add(const _T& element);

    void         SetSize(unsigned int nNewSize);

    inline void         InsertBefore(unsigned int i, const _T& element);
    inline void         InsertAfter(unsigned int i, const _T& element);
    inline void         RemoveAt(unsigned int i, unsigned int size = -1);

private:
    _T*                 m_pData;
    unsigned int        m_nSize;
    unsigned int        m_nMaxSize;
};

// ----------------------------------------------------------------------------
// implementation of my simple array
// ----------------------------------------------------------------------------
template <class _T, class _A> inline XSimplArray<_T, _A>::XSimplArray()
{
    m_pData     = NULL;
    m_nSize     = 0;
    m_nMaxSize  = 0;
}
template <class _T, class _A> inline XSimplArray<_T, _A>::~XSimplArray()
{
    RemoveAll();
}


template <class _T, class _A> inline unsigned int 
XSimplArray<_T, _A>::GetSize() const
{
    return m_nSize;
}
template <class _T, class _A> inline int 
XSimplArray<_T, _A>::GetUpperBound() const
{
    return (int)(m_nSize - 1);
}

// ----------------------------------------------------------------------------
// member access functions
// ----------------------------------------------------------------------------
template <class _T, class _A> inline const _T& 
XSimplArray<_T, _A>::GetAt(unsigned int i) const
{
    xAssert(i < m_nSize);
    return m_pData[i];
}
template <class _T, class _A> inline _T& 
XSimplArray<_T, _A>::GetAt(unsigned int i)
{
    xAssert(i < m_nSize);
    return m_pData[i];
}
template <class _T, class _A> inline void 
XSimplArray<_T, _A>::SetAt(unsigned int i, const _T& element)
{
    xAssert(i < m_nSize);
    m_pData[nIndex] = element;
}
template <class _T, class _A> inline const _T& 
XSimplArray<_T, _A>::operator[](unsigned int i) const
{
    return GetAt(i);
}
template <class _T, class _A> inline _T& 
XSimplArray<_T, _A>::operator[](unsigned int i)
{
    return GetAt(i);
}

// ----------------------------------------------------------------------------
// operations of insert, append, delete, etc.
// ----------------------------------------------------------------------------
template <class _T, class _A> inline void 
XSimplArray<_T, _A>::RemoveAll()
{
    if (m_pData != NULL)
    {
        _A().free(m_pData);
        m_pData = NULL;
    }
    m_nSize = m_nMaxSize = 0;
}
template <class _T, class _A> inline void 
XSimplArray<_T, _A>::Add(const _T& element)
{
    SetSize(m_nSize + 1);
    m_pData[m_nSize - 1] = element;
}
template <class _T, class _A> void 
XSimplArray<_T, _A>::SetSize(unsigned int nNewSize)
{
    if (nNewSize <= m_nSize || nNewSize <= m_nMaxSize)
    {
        m_nSize = nNewSize;
    }
    else
    {
        unsigned int nGrowBy = nNewSize / 3;
        nGrowBy = (nGrowBy < 8) ? 8 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
        m_nMaxSize = nNewSize + nGrowBy;

        _T* pNewData = (_T*)(_A().allocate(sizeof(_T) * m_nMaxSize));
        memcpy(pNewData, m_pData, m_nSize * sizeof(_T));

        if (m_pData != NULL)
        {
            _A().free(m_pData);
            m_pData = NULL;
        }
        m_pData = pNewData;
        m_nSize = nNewSize;
    }
}
template <class _T, class _A> inline void 
XSimplArray<_T, _A>::InsertBefore(unsigned int nIndex, const _T& element)
{
    xAssert(nIndex < m_nSize);
    SetSize(m_nSize + 1);
    memmove(
        m_pData + nIndex + 1, 
        m_pData + nIndex, 
        (m_nSize - nIndex - 1) * sizeof(_T));
    m_pData[nIndex] = element;
}
template <class _T, class _A> inline void 
XSimplArray<_T, _A>::InsertAfter(unsigned int nIndex, const _T& element)
{
    xAssert(nIndex < m_nSize);
    SetSize(m_nSize + 1);
    memmove(
        m_pData + nIndex + 2, 
        m_pData + nIndex + 1, 
        (m_nSize - nIndex - 2) * sizeof(_T));
    m_pData[nIndex + 1] = element;
}
template <class _T, class _A> inline void 
XSimplArray<_T, _A>::RemoveAt(unsigned int nIndex, unsigned int size)
{
    xAssert(nIndex < m_nSize);
    memmove(
        m_pData + nIndex, 
        m_pData + nIndex + 1, 
        (m_nSize - nIndex - 1) * sizeof(_T));
    --m_nSize;
}