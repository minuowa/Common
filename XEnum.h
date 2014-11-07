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

typedef CXDynaArray<CXEnumStruct*> CXEnumStructList;
template<typename T>
class CXEnumStructHelper
{
protected:
	static CXEnumStructList* mStructList;
	static void regist();
public:
	static CXEnumStructList& getStructList();

	~CXEnumStructHelper();
	CXEnumStructHelper();
};

template<typename T>
CXEnumStructHelper<T>::CXEnumStructHelper()
{
	if ( getStructList().empty() )
		regist();
}

template<typename T>
CXEnumStructHelper<T>::~CXEnumStructHelper()
{
	dSafeDeleteVector ( *mStructList );
	dSafeDelete ( mStructList );
}

template<typename T>
CXEnumStructList& CXEnumStructHelper<T>::getStructList()
{
	if ( mStructList == nullptr )
	{
		mStructList = new CXEnumStructList;
	}
	return *mStructList;
}
template<typename T>
CXDefineOnce CXEnumStructList* CXEnumStructHelper<T>::mStructList = nullptr;

