#pragma once
#include <assert.h>
#include <stdarg.h>
#include "MemoryPool.h"
#include "MemoryArray.h"




#define					POOLCOUNT			64
#define					NORAMLPOOLSIZE		1024




class	PoolManager
{
public:


	PoolManager();


	~PoolManager();


public:


	
	// �����ڴ�
	void*							Allocation(unsigned int nSize, const char* pFile, int nLine );



	// �ͷ��ڴ�
	void							Retrieve( void* pPtr );


	// �ͷ����л������ڴ�
	void							Release();


private:


	MemoryArray<void*>					m_arrMemeory;			// �������з�����ڴ�
	MemoryArray<MemoryPool*>			m_arrMemPool;			// ���������ڴ滺����
	unsigned short						m_ByteAligning;			// �ֽڶ��뷽ʽ
	unsigned short						m_MaxPoolSize;			// ÿ��Ϊ�ڴ�ط����ڴ������
	unsigned short						m_MaxNodeSize;			// ���Է����ڴ���е����ڵ��С(���û������ڴ��С���ڴ���ֵʱ�������û������洢�����ڴ���б�)
	unsigned short						m_nCurPoolCount;		// ��ǰ�����Ļ���������					

};
