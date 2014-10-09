#pragma once
#include "XString.h"

/** @brief 兼容qt,加的类型识别 **/
enum ePropertyType
{
	eType_Bool,
	eType_Int,
	eType_Float,
	eType_Double,
	eType_String,
	eType_UnKnown,
};

namespace CXPropHelper
{
	void toString(std::string& dst,String* var);
	void toString(std::string& dst,int* var);
	void toString(std::string& dst,float* var);
	void toString(std::string& dst,bool* var);

	void setValue(const char* val,String* var);
	void setValue(const char* val,int* var);
	void setValue(const char* val,float* var);
	void setValue(const char* val,bool* var);

	template<typename T>
	inline ePropertyType getType()
	{
		return eType_UnKnown;
	}
	template<> inline ePropertyType getType<int>() { return eType_Int; }
	template<> inline ePropertyType getType<bool>() { return eType_Bool; }
	template<> inline ePropertyType getType<float>() { return eType_Float; }
	template<> inline ePropertyType getType<double>() { return eType_Double; }
	template<> inline ePropertyType getType<String>() { return eType_String; }
}


class CXProp
{
public:
	//CXProp(void);
	virtual ~CXProp(void);
	virtual void toString(std::string& dst)=0;
	virtual void setValue(const char* val)=0;
	virtual ePropertyType getType()
	{
		return eType_UnKnown;
	}
};
template<typename T>
class CXPropEntity:public CXProp
{
public:
	CXPropEntity(T* val,bool managedMemory=true);
	~CXPropEntity();
	virtual void toString(std::string& dst);
	virtual void setValue(const char* val);
	virtual ePropertyType getType();

	T* mVar;
private:
	bool mManagedMemory;
};

template<typename T>
ePropertyType CXPropEntity<T>::getType()
{
	return CXPropHelper::getType<T>();
}

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
