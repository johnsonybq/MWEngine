#pragma once 
#include <assert.h>

#define				INITIALMEMORYSIZE	256


template<class T>
class		MemoryArray
{
public:

	MemoryArray();

	MemoryArray(unsigned int nArrSize);

	~MemoryArray();


public:


	// 向数组中添加数据
	void					Add(T tValue);


	// 获取当前数组大小
	unsigned int			GetSize();


	// 从数组中移除
	void					Remove(unsigned short nIndex);


	// 获取数据
	T&						Get(unsigned short nIndex);


	// 重载运算符
	T&						operator [](unsigned short nIndex);


	// 清空
	void					Clear();


private:


	// 数据初始化
	void					Init();


	// 数组大小重新分配
	void					ResizeArray();


private:


	unsigned int			nSize;
	unsigned int			nCurSize;
	T*						pArrayHead;

};




template<class	T>
MemoryArray<T>::MemoryArray()
	:nSize(INITIALMEMORYSIZE), nCurSize(0), pArrayHead(0)
{
	pArrayHead = reinterpret_cast<T*>(::malloc(nSize * sizeof(T)));
	memset(pArrayHead, 0, nSize * sizeof(T));
}


template<class T>
MemoryArray<T>::MemoryArray(unsigned int nArrSize)
	:nSize(nArrSize), nCurSize(0), pArrayHead(0)
{
	pArrayHead = reinterpret_cast<T*>(::malloc(nSize * sizeof(T)));
}


template<class T>
MemoryArray<T>::~MemoryArray()
{
	Clear();
}



// 向数组中添加元素
template<class T>
void			MemoryArray<T>::Add(T tValue)
{
	if (0 == pArrayHead)
	{
		Init();
	}

	if (nCurSize < nSize)
	{
		pArrayHead[nCurSize] = tValue;
	}
	else
	{
		ResizeArray();
		pArrayHead[nCurSize] = tValue;
	}

	++nCurSize;
}


// 获取数组数据
template<class T>
T&				MemoryArray<T>::Get(unsigned short nIndex)
{
	assert(nIndex < nSize || "MemoryArray Overlow!");
	assert(pArrayHead || "MemoryArray is Empty!");

	if (nIndex < nSize)
	{
		T* p = (T*)((char*)(pArrayHead)+nIndex * sizeof(T));
		T pp = *p;
		return pArrayHead[nIndex];
	}

	return pArrayHead[0];
}



// 获取数组大小
template<class T>
unsigned int			MemoryArray<T>::GetSize()
{
	return nCurSize;
}



// 重载[]运算符
template<class T>
T&						MemoryArray<T>::operator[](unsigned short nIndex)
{
	return Get(nIndex);
}


// 删除数组中数据
template<class T>
void					MemoryArray<T>::Remove(unsigned short nIndex)
{
	assert(nIndex < nSize || "MemoryArray Overlow!");
	assert(pArrayHead || "MemoryArray is Empty!");

	if ((nIndex < nSize) && (0 != pArrayHead))
	{
		--nCurSize;

		if (nIndex == 0)
		{
			pArrayHead = pArrayHead + 1;
		}
		else
		{
			memmove(pArrayHead + nIndex, pArrayHead + nIndex + 1, (nCurSize - nIndex) * sizeof(T));
		}
	}
}



// 清空数组
template<class T>
void				MemoryArray<T>::Clear()
{
	if (pArrayHead)
	{
		::free(pArrayHead);
	}

	nCurSize = nSize = 0;
	pArrayHead = 0;
}



// 数组初始化
template<class T>
void				MemoryArray<T>::Init()
{
	if (0 == pArrayHead)
	{
		nSize = INITIALMEMORYSIZE;
		nCurSize = 0;
		pArrayHead = reinterpret_cast<T*>(::malloc(INITIALMEMORYSIZE * sizeof(T)));
		memset(pArrayHead, 0, INITIALMEMORYSIZE * sizeof(T));
	}
}


// 数组大小重新分配
template<class T>
void				MemoryArray<T>::ResizeArray()
{
	if (0 == pArrayHead)
	{
		Init();
	}
	else
	{
		size_t nNewSize = (nSize * 3);
		T* pNewHead = reinterpret_cast<T*>(::malloc(nNewSize * sizeof(T)));
		memcpy(pNewHead, pArrayHead, nSize * sizeof(T));
		::free(pArrayHead);
		pArrayHead = pNewHead;
		nSize = nNewSize;
	}
}