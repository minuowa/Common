#pragma once
#include "XString.h"
namespace CXPropHelper
{
	void toString(std::string& dst,String* var);
	void toString(std::string& dst,int* var);
	void toString(std::string& dst,float* var);

	void setValue(const char* val,String* var);
	void setValue(const char* val,int* var);
	void setValue(const char* val,float* var);
}
class CXProp
{
public:
	CXProp(void);
	virtual ~CXProp(void);
	virtual void toString(std::string& dst)
	{
	}
	virtual void setValue(const char* val)
	{
	}
};
template<typename T>
class CXPropEntity:public CXProp
{
public:
	CXPropEntity(T* val,bool managedMemory=true);
	~CXPropEntity();
	virtual void toString(std::string& dst);
		//virtual void toString(String& dst);
	virtual void setValue(const char* val);
private:
	T* mVar;
	bool mManagedMemory;
};

template<typename T>
void CXPropEntity<T>::toString( std::string& dst )
{
	CXPropHelper::toString(dst,mVar);
}

template<typename T>
void CXPropEntity<T>::setValue( const char* val )
{
	CXPropHelper::setValue(val,mVar);
}


template<typename T>
CXPropEntity<T>::~CXPropEntity()
{
	if (mManagedMemory)
	{
		delete mVar;
		mVar=0;
	}
}

template<typename T>
CXPropEntity<T>::CXPropEntity( T* val,bool managedMemory/*=true*/ )
	:mVar(val),mManagedMemory(managedMemory)
{

}

