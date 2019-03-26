#pragma once
#include <Windows.h>
#include <iostream>



// �ڴ������������ͳ���ڴ�ʹ���������־���

class		MemoryHelper
{
private:	

	MemoryHelper();

public:

	
	static MemoryHelper* GetInstance()
	{													
		static MemoryHelper instance;
		return &instance;									
	}


public:

	
	~MemoryHelper();


public:



	void				OnMemAlloc( unsigned int nMemSize, unsigned int nExMemSize ); 


	void				OnMemRetrieve( unsigned int nMemSize, unsigned int nExMemSize );


	void				ReportMemLeak( const char* pFile, int nLine, unsigned int nSize, int nPtrAddr );


	void				ReportMemFlowOver( const char* pFile, int nLine, int nPtrAddr );


	void				ReportMemoryInfo( const char* pInfo );


	void				ReportMemoryWarning();



private:


	unsigned int					m_nCurMemObjects;			// ��ǰ�ڴ�������
	unsigned int					m_nCurAllocMemSize;			// ��ǰ����ʹ�õ��ڴ��С

	unsigned int					m_nMaxMemObjects;			// ���������
	unsigned int					m_nMaxAllocMemSize;			// �������ڴ��С( �ⲿʹ�õ� )

	unsigned int					m_nCurMemTotalSize;			// ��ǰ��������ڴ�����( ���������ڴ���Ϣ���� )
	unsigned int					m_nMaxMemTotalSize;			// ����ڴ��������

};

