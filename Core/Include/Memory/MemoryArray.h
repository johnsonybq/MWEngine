#pragma once 
#include "MWCore.h"

#define				INITIALMEMORYSIZE	256


template<class T>
class	DLL_EXPORTS	MemoryArray
{
public:

	MemoryArray();

	MemoryArray( unsigned int nArrSize );

	~MemoryArray();


public:

	
	// ���������������
	void					Add( T tValue );


	// ��ȡ��ǰ�����С
	unsigned int			GetSize();


	// ���������Ƴ�
	void					Remove( unsigned short nIndex );


	// ��ȡ����
	T&						Get( unsigned short nIndex );


	// ���������
	T&						operator []( unsigned short nIndex );


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

