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


// ��ʼ���ڴ����Ϣ
void					MemoryNode::Init()
{
	stPad.InitPadding();
	memset(sFile, 0, MAX_FILE_PATH);
	nLine = nSize = 0;
	pNext = 0;
	bUsed = false;
	bGuarded = false;
}



// ��ǰ�ڴ���Ƿ����Խ��
bool					MemoryNode::Invalid()
{
	return stPad.InvalidPtr();
}