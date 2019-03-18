#pragma once
#include <string>
#include <stdarg.h>
#include "PaddingCode.h"



#define			MAX_FILE_PATH	64



// ��¼ÿ�����������ڴ���е��ڴ���Ϣ

struct MemoryNode 
{
	PaddingCode				stPad;					// �ڴ���������ڼ���ڴ�Խ��
	char					sFile[MAX_FILE_PATH];	// �����ڴ���ļ�·��
	bool					bUsed;					// ��ǰ�ڴ���Ƿ��ⲿʹ��
	bool					bGuarded;				// ��ǰ�ڴ���Ƿ񱻼��
	unsigned int			nLine;					// �����ڴ���������ļ�����

	MemoryNode*				pNext;					// ָ����һ��δʹ�õ��ڴ���ַ
	unsigned int			nSize;					// �����ڴ��С


	MemoryNode();


	~MemoryNode();


	// ��ʼ���ڴ����Ϣ
	void					Init();



	// ��ǰ�ڴ���Ƿ����Խ��
	bool					Invalid();
};