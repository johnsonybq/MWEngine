#pragma once




// ��������ڲ����ڴ�ʹ��Խ��
struct	PaddingCode 
{
	enum	PaddingSize
	{
		nCount = ( 16 / sizeof( unsigned short ) )				// ����볤��
	};			
	unsigned short m_PaddingCode[nCount];						// ��������ڼ���ڴ��Ƿ����Խ��


	// ��ʼ�������
	void			InitPadding()
	{
		for ( int nIndex = 0; nIndex < nCount; ++nIndex )
		{
			m_PaddingCode[nIndex] = 0xcdcd;
		}
	}



	// �ж�ָ���Ƿ�����Чָ��
	bool			InvalidPtr()
	{
		for ( int nIndex = 0; nIndex < nCount; ++nIndex )
		{
			if ( m_PaddingCode[nIndex] != 0xcdcd )
			{
				return true;
			}
		}

		return false;
	}



};