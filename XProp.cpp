#include "base.h"
#include "XProp.h"

#include "XIndex.h"
//CXProp::CXProp(void)
//{
//}


CXProp::~CXProp ( void )
{
}



ePropertyType CXPropEnum::getType()
{
    return eType_Enum;
}

const CXEnumStructList& CXPropEnum::getStructList() const
{
    return mStringList;
}


void CXPropEnum::toString ( std::string& dst )
{

}

void CXPropEnum::setValue ( const char* val )
{

}

u32 CXPropEnum::getIndex ( int var ) const
{
    for ( u32 i = 0; i <  mStringList.size(); ++i )
    {
        const CXEnumStruct* est = mStringList[i];
        if ( var == est->mValue )
        {
            return i;
        }
    }
    CXASSERT ( 0 );
    return 0;
}

u32 CXPropEnum::getIndex ( const char* name ) const
{
    for ( u32 i = 0; i <  mStringList.size(); ++i )
    {
        const CXEnumStruct* est = mStringList[i];
        if ( !strcmp ( name, est->mName ) )
        {
            return i;
        }
    }
    CXASSERT ( 0 );
    return 0;
}

u32 CXPropEnum::getIndex() const
{
    int v = 0;
    dCast ( v, mVar );
    return getIndex ( v );
}

int CXPropEnum::getValue ( int idx ) const
{
    return mStringList[idx]->mValue;
}

int CXPropEnum::getValue() const
{
    int v = 0;
    dCast ( v, mVar );
    return v;
}

const char* CXPropEnum::getTheName() const
{
    int idx = getIndex ( getValue() );
    return mStringList[idx]->mName;
}
