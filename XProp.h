#ifndef XProp_h__
#define XProp_h__

#include "uString.h"
#include "XEnum.h"
#include "XStringHelper.h"

/** @brief 兼容qt,加的类型识别 **/
enum ePropertyType
{
	eType_Bool,
	eType_Int,
	eType_UInt,
	eType_Float,
	eType_Double,
	eType_String,
	eType_Enum,
	eType_UnKnown,
};
namespace CXPropHelper
{
	template<typename T>
	inline ePropertyType getType()
	{
		return eType_UnKnown;
	}
	template<> inline ePropertyType getType<int>()
	{
		return eType_Int;
	}
	template<> inline ePropertyType getType<unsigned int>()
	{
		return eType_UInt;
	}
	template<> inline ePropertyType getType<long>()
	{
		return eType_Int;
	}
	template<> inline ePropertyType getType<bool>()
	{
		return eType_Bool;
	}
	template<> inline ePropertyType getType<float>()
	{
		return eType_Float;
	}
	template<> inline ePropertyType getType<double>()
	{
		return eType_Double;
	}
	template<> inline ePropertyType getType<uString>()
	{
		return eType_String;
	}
}
class CXProp
{
public:
	//CXProp(void);
	virtual ~CXProp ( void );
	virtual void toString ( std::string& dst ) = 0;
	virtual void setValue ( const char* val ) = 0;
	virtual ePropertyType getType()
	{
		return eType_UnKnown;
	}
};
template<typename T>
class  CXPropEntity: public CXProp
{
public:
	CXPropEntity ( T* val, bool managedMemory = true );
	~CXPropEntity();
	virtual void toString ( std::string& dst );
	virtual void setValue ( const char* val );
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
void CXPropEntity<T>::toString ( std::string& dst )
{
	CXStringHelper::toString ( dst, mVar );
}

template<typename T>
void CXPropEntity<T>::setValue ( const char* val )
{
	CXStringHelper::setValue ( val, mVar );
}


template<typename T>
CXPropEntity<T>::~CXPropEntity()
{
	if ( mManagedMemory )
	{
		delete mVar;
		mVar = 0;
	}
}

template<typename T>
CXPropEntity<T>::CXPropEntity ( T* val, bool managedMemory/*=true*/ )
	: mVar ( val ), mManagedMemory ( managedMemory )
{

}
class CXPropEnum: public CXPropEntity<int>
{
public:
	CXPropEnum ( int* var, const uEnumStructList& arr, bool managedMemory = true )
		: CXPropEntity ( var, managedMemory )
		, mStringList ( arr )
	{
	}
	virtual void toString ( std::string& dst );
	virtual void setValue ( const char* val );

	virtual ePropertyType getType();
	u32 getIndex() const;
	u32 getIndex ( int var ) const;
	u32 getIndex ( const char* name ) const;
	int getValue ( int idx ) const;
	int getValue() const;
	const char* getTheName() const;
	const uEnumStructList& getStructList() const;
protected:
	const uEnumStructList& mStringList;
};
inline CXProp::~CXProp ( void )
{
}



inline ePropertyType CXPropEnum::getType()
{
	return eType_Enum;
}

inline const uEnumStructList& CXPropEnum::getStructList() const
{
	return mStringList;
}


inline void CXPropEnum::toString ( std::string& dst )
{

}

inline void CXPropEnum::setValue ( const char* val )
{

}

inline u32 CXPropEnum::getIndex ( int var ) const
{
	for ( u32 i = 0; i <  mStringList.size(); ++i )
	{
		const uEnumStruct* est = mStringList[i];
		if ( var == est->mValue )
		{
			return i;
		}
	}
	CXASSERT ( 0 );
	return 0;
}

inline u32 CXPropEnum::getIndex ( const char* name ) const
{
	for ( u32 i = 0; i <  mStringList.size(); ++i )
	{
		const uEnumStruct* est = mStringList[i];
		if ( !strcmp ( name, est->mName ) )
		{
			return i;
		}
	}
	CXASSERT ( 0 );
	return 0;
}

inline u32 CXPropEnum::getIndex() const
{
	int v = 0;
	dCast ( v, mVar );
	return getIndex ( v );
}

inline int CXPropEnum::getValue ( int idx ) const
{
	return mStringList[idx]->mValue;
}

inline int CXPropEnum::getValue() const
{
	int v = 0;
	dCast ( v, mVar );
	return v;
}

inline const char* CXPropEnum::getTheName() const
{
	int idx = getIndex ( getValue() );
	return mStringList[idx]->mName;
}

#endif // XProp_h__
