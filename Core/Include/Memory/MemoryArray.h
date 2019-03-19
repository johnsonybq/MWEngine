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


	// ���������������
	void					Add(T tValue);


	// ��ȡ��ǰ�����С
	unsigned int			GetSize();


	// ���������Ƴ�
	void					Remove(unsigned short nIndex);


	// ��ȡ����
	T&						Get(unsigned short nIndex);


	// ���������
	T&						operator [](unsigned short nIndex);


	// ���
	void					Clear();


private:


	// ���ݳ�ʼ��
	void					Init();


	// �����С���·���
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



// �����������Ԫ��
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


// ��ȡ��������
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



// ��ȡ�����С
template<class T>
unsigned int			MemoryArray<T>::GetSize()
{
	return nCurSize;
}



// ����[]�����
template<class T>
T&						MemoryArray<T>::operator[](unsigned short nIndex)
{
	return Get(nIndex);
}


// ɾ������������
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



// �������
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



// �����ʼ��
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


// �����С���·���
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