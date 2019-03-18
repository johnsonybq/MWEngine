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


	// 初始化内存缓冲
	void							InitMemoryPool( void* pPool, unsigned short nDataSize, unsigned short nCount );



	// 从内存池中分配内存
	MemoryNode*						Allocation( unsigned short nSize, const char* pFile, int nLine );



	
	// 释放内存到内存缓冲区
	void							Retrieve( MemoryNode* pNode );



	// 缓冲区是否耗尽
	bool							IsEmpty();



	// 清空内存缓冲区
	void							Clear();



	// 重载赋值运算符
	MemoryPool&						operator = ( const MemoryPool& _other );


private:


	// 获取下一个内存数据块节点
	MemoryNode*						GetNextNode( MemoryNode* pNode );


	// 检测内存访问越界
	void							CheckFlowOver( MemoryNode* pNode );


	// 检测内存泄漏
	void							CheckLeak( MemoryNode* pNode );


private:


	unsigned short					m_nDataSize;			// 每个数据块有效部分大小
	unsigned short					m_nTotalSize;			// 缓冲区中内存块个数
	MemoryNode*						m_pPoolHead;			// 内存缓冲区首地址
	MemoryArray<MemoryNode*>		m_AllocList;			// 由此缓冲区分配出去的内存块

};


