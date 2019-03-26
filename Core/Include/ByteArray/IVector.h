#pragma once
#ifndef IVector_h__
#define IVector_h__

#include <vector>

namespace Core
{
	template<class T>

	class IVector
	{
	public:
		IVector(bool bReadOnly = false)
		: m_bReadOnly(bReadOnly)
		{

		}
		virtual ~IVector(){}

	public:
		bool isReadOnly() const { return m_bReadOnly; }
		void setReadOnly(bool bReadOnly) { m_bReadOnly = bReadOnly; }
		std::vector<T> m_DataVector;

	private:
		bool m_bReadOnly;
		
	};
}
#endif // IVector_h__