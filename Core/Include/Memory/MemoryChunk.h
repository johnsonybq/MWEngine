#pragma  once
#include <string>
#include <stdarg.h>
#include "PaddingCode.h"


#define			MAX_FILE_PATH	64



// 用于保存大块内存区域信息
struct		MemoryChunk
{
	PaddingCode			stPad;					// 内存填充码用于检测内存越界
	char				sFile[MAX_FILE_PATH];	// 创建内存的文件
	unsigned int		nLine;					// 创建内存文件行数

	MemoryChunk*		pNext;					// 指向下一个内存块地址
	MemoryChunk*		pPer;					// 指向上一个内存块地址
	unsigned int		nSize;					// 创建内存大小



	MemoryChunk();

	~MemoryChunk();



	// 初始化内存块信息
	void				Init();


	// 判断当前内存块是否访问越界
	bool				Invalid();


};