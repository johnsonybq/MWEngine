#pragma once
#include <assert.h>
#include "MemoryChunk.h"
#include "MemoryHelper.h"



// ���ڴ���б����
class				MemoryChunkList
{
public:

	
	MemoryChunkList();


	~MemoryChunkList();


public:


	// �������һ����С���ڴ�����
	void*						Allocation(size_t nSize, const char* pFile, int nLine );



	// �����ͷ�ĳһ���ڴ�����
	void						Retrieve( void* pVoid );


private:


	// �����ڴ����ݵ�ַ�����ڴ���ַ
	MemoryChunk*				GetChunk( void* pVoid );


	// Ϊ�ڴ�����ָ����С���ڴ�����
	MemoryChunk*				AllocaChunk( size_t nSize, const char* pFile, int nLine );


	// �ͷ��ڴ�������ݲ����ڴ������ڴ滺����
	bool						RetrieveChunk( MemoryChunk* pChunk );


	// ����ڴ���Ƿ����Խ��
	void						CheckFlowOver( MemoryChunk* pChunk );


	// ����ڴ���ڴ�й©
	void						CheckLeak( MemoryChunk* pChunk );


	// ���
	void						Clear();


private:


	MemoryChunk*				m_pChunkHead;		// ��ǰʹ�õĴ��ڴ���б��ͷ

};

