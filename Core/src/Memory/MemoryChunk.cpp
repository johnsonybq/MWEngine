#pragma  once
#include <string>
#include <stdarg.h>
#include "Memory\MemoryChunk.h"


MemoryChunk::MemoryChunk()
	:nLine(0), nSize(0), pNext(0), pPer(0)
{
	stPad.InitPadding();
	memset(sFile, 0, MAX_FILE_PATH);
}

MemoryChunk::~MemoryChunk()
{

}


// ��ʼ���ڴ����Ϣ
void				MemoryChunk::Init()
{
	stPad.InitPadding();
	memset(sFile, 0, MAX_FILE_PATH);
	nLine = nSize = 0;
	pNext = 0;
	pPer = 0;
}


// �жϵ�ǰ�ڴ���Ƿ����Խ��
bool				MemoryChunk::Invalid()
{
	return stPad.InvalidPtr();
}