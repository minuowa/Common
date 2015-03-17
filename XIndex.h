#ifndef XIndex_h__
#define XIndex_h__

#pragma once
#include <string>
#include <stdio.h>
#pragma warning(push)
#pragma warning(disable:4996)
class CXIndex
{
	typedef unsigned int Type;
public:
	enum
	{
		InvalidIndex = ~0,
	};
	CXIndex ( void );
	CXIndex ( int i );
	~CXIndex ( void );
protected:
	Type mValue;
public:
	bool IsValid() const
	{
		return mValue != InvalidIndex;
	}
	Type Value() const
	{
		return mValue;
	}
	void ToString ( std::string& str )
	{
		char buffer[64] = {0};
		sprintf ( buffer, "%d", mValue );
		str = buffer;
		//_itoa(mValue,(char*)str.c_str(),10);
	}
	CXIndex& operator= ( Type v )
	{
		mValue = v;
		return *this;
	}
	operator Type()
	{
		return mValue;
	}
	CXIndex operator++ ( int )
	{
		CXIndex tmp = *this;
		++mValue;
		return tmp;
	}
	CXIndex& operator++()
	{
		++mValue;
		return *this;
	}
	CXIndex operator-- ( int )
	{
		CXIndex tmp = *this;
		--mValue;
		return tmp;
	}
	CXIndex& operator--()
	{
		--mValue;
		return *this;
	}

	bool operator== ( const CXIndex& _Right ) const
	{
		return mValue == _Right.mValue;
	}
};
inline bool operator < ( const CXIndex& lhs, const CXIndex& rhs )
{
	return lhs.Value() < rhs.Value();
}
#pragma warning(pop)
inline CXIndex::CXIndex ( int i )
	: mValue ( i )
{

}
inline CXIndex::CXIndex ( void )
{
}
inline CXIndex::~CXIndex ( void )
{
}
#endif // XIndex_h__
