#ifndef XProp_h__
#define XProp_h__

#include "XString.h"
#include "XEnum.h"
#include "XStringHelper.h"

/** @brief ����qt,�ӵ�����ʶ�� **/
enum ePropertyType
{
    eType_Bool,
    eType_Int,
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
	template<> inline ePropertyType getType<GString>()
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
class CXPropEntity: public CXProp
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
    CXPropEnum ( int* var, const CXEnumStructList& arr, bool managedMemory = true )
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
    const CXEnumStructList& getStructList() const;
protected:
    const CXEnumStructList& mStringList;
};

#endif // XProp_h__