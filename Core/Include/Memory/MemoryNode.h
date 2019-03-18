#pragma once
#include <string>
#include <stdarg.h>
#include "PaddingCode.h"



#define			MAX_FILE_PATH	64



// 记录每个被分配在内存池中的内存信息

struct MemoryNode 
{
	PaddingCode				stPad;					// 内存填充码用于检测内存越界
	char					sFile[MAX_FILE_PATH];	// 创建内存的文件路径
	bool					bUsed;					// 当前内存块是否被外部使用
	bool					bGuarded;				// 当前内存块是否被监控
	unsigned int			nLine;					// 创建内存代码所在文件行数

	MemoryNode*				pNext;					// 指向下一个未使用的内存块地址
	unsigned int			nSize;					// 创建内存大小


	MemoryNode();


	~MemoryNode();


	// 初始化内存块信息
	void					Init();



	// 当前内存块是否访问越界
	bool					Invalid();
};