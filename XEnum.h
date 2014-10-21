#pragma once
#include "XDynaArray.h"
struct CXEnumStruct
{
	const char* mName;
	const int mValue;
	CXEnumStruct ( int var, const char* name )
		: mName ( name ), mValue ( var )
	{
	}
};

template<typename T>
struct CXEnumStructHelper 
{
	static CXDynaArray<CXEnumStruct> mStructList;
	static void regist();
};

template<typename T>
CXDynaArray<CXEnumStruct> CXEnumStructHelper<T>::mStructList;

