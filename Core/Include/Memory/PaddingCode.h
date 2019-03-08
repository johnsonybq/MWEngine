#pragma once




// 填充码用于测试内存使用越界
struct	PaddingCode 
{
	enum	PaddingSize
	{
		nCount = ( 16 / sizeof( unsigned short ) )				// 填充码长度
	};			
	unsigned short m_PaddingCode[nCount];						// 填充码用于检测内存是否访问越界


	// 初始化填充码
	void			InitPadding()
	{
		for ( int nIndex = 0; nIndex < nCount; ++nIndex )
		{
			m_PaddingCode[nIndex] = 0xcdcd;
		}
	}



	// 判断指针是否是有效指针
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