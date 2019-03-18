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

	
	// 向数组中添加数据
	void					Add( T tValue );


	// 获取当前数组大小
	unsigned int			GetSize();


	// 从数组中移除
	void					Remove( unsigned short nIndex );


	// 获取数据
	T&						Get( unsigned short nIndex );


	// 重载运算符
	T&						operator []( unsigned short nIndex );


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

