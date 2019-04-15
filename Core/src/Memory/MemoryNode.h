#pragma once
#include <string>
#include <stdarg.h>
#include "PaddingCode.h"

namespace Core
{
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


		MemoryNode()
			:nLine(0), nSize(0), pNext(0), bUsed(false), bGuarded(false)
		{
			stPad.InitPadding();
			memset(sFile, 0, MAX_FILE_PATH);
		}


		~MemoryNode()
		{

		}


		// ��ʼ���ڴ����Ϣ
		void					Init()
		{
			stPad.InitPadding();
			memset(sFile, 0, MAX_FILE_PATH);
			nLine = nSize = 0;
			pNext = 0;
			bUsed = false;
			bGuarded = false;
		}



		// ��ǰ�ڴ���Ƿ����Խ��
		bool					Invalid()
		{
			return stPad.InvalidPtr();
		}

	};
}
