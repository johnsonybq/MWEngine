#pragma once
#include <string>
#include <stdarg.h>
#include "Memory\MemoryNode.h"


MemoryNode::MemoryNode()
	:nLine(0), nSize(0), pNext(0), bUsed(false), bGuarded(false)
{
	stPad.InitPadding();
	memset(sFile, 0, MAX_FILE_PATH);
}


MemoryNode::~MemoryNode()
{

}


// 初始化内存块信息
void					MemoryNode::Init()
{
	stPad.InitPadding();
	memset(sFile, 0, MAX_FILE_PATH);
	nLine = nSize = 0;
	pNext = 0;
	bUsed = false;
	bGuarded = false;
}



// 当前内存块是否访问越界
bool					MemoryNode::Invalid()
{
	return stPad.InvalidPtr();
}