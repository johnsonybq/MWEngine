#pragma  once
#include <string>
#include <stdarg.h>
#include "PaddingCode.h"


#define			MAX_FILE_PATH	64



// ���ڱ������ڴ�������Ϣ
struct		MemoryChunk
{
	PaddingCode			stPad;					// �ڴ���������ڼ���ڴ�Խ��
	char				sFile[MAX_FILE_PATH];	// �����ڴ���ļ�
	unsigned int		nLine;					// �����ڴ��ļ�����

	MemoryChunk*		pNext;					// ָ����һ���ڴ���ַ
	MemoryChunk*		pPer;					// ָ����һ���ڴ���ַ
	unsigned int		nSize;					// �����ڴ��С



	MemoryChunk();

	~MemoryChunk();



	// ��ʼ���ڴ����Ϣ
	void				Init();


	// �жϵ�ǰ�ڴ���Ƿ����Խ��
	bool				Invalid();


};