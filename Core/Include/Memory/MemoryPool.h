#pragma once
#include "MemoryNode.h"
#include "MemoryArray.h"
#include "MemoryHelper.h"




class			MemoryPool
{
public:


	MemoryPool();


	MemoryPool( unsigned short nPoolID, unsigned short nDataSize );


	~MemoryPool();


public:


	// ��ʼ���ڴ滺��
	void							InitMemoryPool( void* pPool, unsigned short nDataSize, unsigned short nCount );



	// ���ڴ���з����ڴ�
	MemoryNode*						Allocation( unsigned short nSize, const char* pFile, int nLine );



	
	// �ͷ��ڴ浽�ڴ滺����
	void							Retrieve( MemoryNode* pNode );



	// �������Ƿ�ľ�
	bool							IsEmpty();



	// ����ڴ滺����
	void							Clear();



	// ���ظ�ֵ�����
	MemoryPool&						operator = ( const MemoryPool& _other );


private:


	// ��ȡ��һ���ڴ����ݿ�ڵ�
	MemoryNode*						GetNextNode( MemoryNode* pNode );


	// ����ڴ����Խ��
	void							CheckFlowOver( MemoryNode* pNode );


	// ����ڴ�й©
	void							CheckLeak( MemoryNode* pNode );


private:


	unsigned short					m_nDataSize;			// ÿ�����ݿ���Ч���ִ�С
	unsigned short					m_nTotalSize;			// ���������ڴ�����
	MemoryNode*						m_pPoolHead;			// �ڴ滺�����׵�ַ
	MemoryArray<MemoryNode*>		m_AllocList;			// �ɴ˻����������ȥ���ڴ��

};


