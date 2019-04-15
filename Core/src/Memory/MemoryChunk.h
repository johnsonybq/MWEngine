#pragma  once
#include <string>
#include <stdarg.h>
#include "PaddingCode.h"

namespace Core
{
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



		MemoryChunk()
			:nLine(0), nSize(0), pNext(0), pPer(0)
		{
			stPad.InitPadding();
			memset(sFile, 0, MAX_FILE_PATH);
		}

		~MemoryChunk()
		{

		}


		// ��ʼ���ڴ����Ϣ
		void				Init()
		{
			stPad.InitPadding();
			memset(sFile, 0, MAX_FILE_PATH);
			nLine = nSize = 0;
			pNext = 0;
			pPer = 0;
		}


		// �жϵ�ǰ�ڴ���Ƿ����Խ��
		bool				Invalid()
		{
			return stPad.InvalidPtr();
		}


	};
}
