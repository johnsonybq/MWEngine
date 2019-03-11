//--------------------------------------------------------------------
//  版权所有:	
//  文件名称:	IMemPort.h
//  文件说明:		
//  创建日期:	2012年$月$日
//  -------------------------------------------------------------------
//  版本历史:
//               Sam(lil) 1.0  2012年$月$日 创建基本功能        
//--------------------------------------------------------------------

#pragma once

#include "IMemMan.h"

template <class Type> struct Struct_Allocate
{
    Struct_Allocate(IMemoryManager* manager) : m_manager(manager) {}

    Type* operator()(size_t count, const void* szFile = "", int nLine = 0)
    {
        if (count == 0)
        {
            count = 1;
        }
        size_t size = count * sizeof(Type) + sizeof(unsigned int);

        unsigned int* pCount;
#ifdef _DEBUG
        void* pData = m_manager->Allocate(size, (const char*)szFile, nLine);
        pCount = (unsigned int*)((ptrdiff_t)pData - sizeof(_Padding) - sizeof(unsigned int));
#else
        void* pData = m_manager->Allocate(size);
        pCount = (unsigned int*)((ptrdiff_t)pData - sizeof(unsigned int));
#endif
        if (!pData)
        {
            return 0;
        }
        *pCount = count;
        void* pToInit = pData;
        for (; count--; pToInit = (void*)(((int)pToInit)+sizeof(Type)))
        {
            new(pToInit) Type;
        }

        return (Type*)pData;
    }

    IMemoryManager* m_manager;
};

template <> struct Struct_Allocate<void>
{
    void* operator()(size_t, const void*, int)
    {
        return 0;
    }
};

template <class Type> struct Struct_Deallocate
{
    Struct_Deallocate(IMemoryManager* manager) : m_manager(manager) {}

    IMemoryManager* m_manager;

    void operator()(void* pToDel, const void* szFile = "", unsigned int nLine = 0)
    {
        if (pToDel == 0)
        {
            return;
        }

        _SmallUnit_t* pUnit = 
            reinterpret_cast<_SmallUnit_t*>(
            reinterpret_cast<unsigned int>(pToDel) - 
            sizeof(_SmallUnit_t) + 
            sizeof(_SmallUnit_t*));

        int count = pUnit->count;
        void* pToDestroy = pToDel;
        for (; count--; pToDestroy = (void*)(((int)pToDestroy)+(pUnit->size-sizeof(unsigned int))/pUnit->count))
        {
            ((Type*)pToDestroy)->~Type();
        }

        m_manager->Free(pToDel, (const char*)szFile, nLine);
    }
};


template <> struct Struct_Deallocate<void>
{
    Struct_Deallocate(IMemoryManager* manager) : m_manager(manager) {}

    IMemoryManager* m_manager;

    void operator()(void* pToDel, const void* szFile = "", unsigned int nLine = 0)
    {
        if (pToDel == 0)
        {
            return;
        }
        m_manager->Free(pToDel);
    }
};

template <class Type> struct Struct_Reallocate
{
    Struct_Reallocate(IMemoryManager* manager) : m_manager(manager) {}

    IMemoryManager* m_manager;

    Type* operator()(void* pPtr, size_t nSize, const void* pFile = "", size_t nLine = 0)
    {
        if (nSize == 0)
        {
            if (pPtr == 0)
            {
                return NULL;
            }
            _SmallUnit_t* pUnit = 
                reinterpret_cast<_SmallUnit_t*>(
                reinterpret_cast<unsigned int>(pPtr) - 
                sizeof(_SmallUnit_t) + 
                sizeof(_SmallUnit_t*));

            int count = pUnit->count;
            void* pToDestroy = pPtr;
            for (; count--; pToDestroy = (void*)(((int)pToDestroy)+(pUnit->size-sizeof(unsigned int))/pUnit->count))
            {
                ((Type*)pToDestroy)->~Type();
            }

            m_manager->Free(pPtr, (const char*)pFile, nLine);
            return NULL;
        }
        if (!pPtr)
        {
            Struct_Allocate<Type> tmp(m_manager);

            return tmp(nSize, pFile, nLine);
        }
        _SmallUnit_t* pUnit = 
            reinterpret_cast<_SmallUnit_t*>(
            reinterpret_cast<unsigned int>(pPtr) - 
            sizeof(_SmallUnit_t) + 
            sizeof(_SmallUnit_t*));
        size_t nObjSize  = (pUnit->size-sizeof(unsigned int)) / pUnit->count;
        size_t nNewCount = nSize / nObjSize;
        size_t nOldCount = pUnit->count;
        if (nNewCount == nOldCount)
        {
            return (Type*)pPtr;
        }
        else if (nNewCount > nOldCount)
        {
            // 构造
            void* pNewAddr = m_manager->Reallocate(pPtr, nSize, (const char*)pFile, nLine);
            if (!pNewAddr)
            {
                return 0;
            }
            void* pModify = (char*)pNewAddr + nOldCount;
            for (unsigned int i = 0; i < nNewCount - nOldCount; ++i)
            {
                new(pModify) Type;
                pModify = (char*)pModify + nObjSize;
            }

            unsigned int* pCount;
#ifdef _DEBUG
            pCount = (unsigned int*)((ptrdiff_t)pNewAddr - sizeof(_Padding) - sizeof(unsigned int));
#else
            pCount = (unsigned int*)((ptrdiff_t)pNewAddr - sizeof(unsigned int));
#endif
            *pCount = nNewCount;

            return (Type*)pNewAddr;
        }
        else
        {
            // 析构
            void* pDestroy = (char*)pPtr + nNewCount * nObjSize;
            for (unsigned int i = 0; i < nOldCount - nNewCount; ++i)
            {
                ((Type*)pDestroy)->~Type();
                pDestroy = (char*)pDestroy + nObjSize;
            }
            void* pNewAddr = m_manager->Reallocate(pPtr, nSize, (const char*)pFile, nLine);
            if (!pNewAddr)
            {
                return 0;
            }

            unsigned int* pCount;
#ifdef _DEBUG
            pCount = (unsigned int*)((ptrdiff_t)pNewAddr - sizeof(_Padding) - sizeof(unsigned int));
#else
            pCount = (unsigned int*)((ptrdiff_t)pNewAddr - sizeof(unsigned int));
#endif
            *pCount = nNewCount;

            return (Type*)pNewAddr;
        }
    }
};
