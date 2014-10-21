#include "base.h"
#include "XProp.h"
#pragma warning(push)
#pragma warning(disable:4996)
#include "XIndex.h"
//CXProp::CXProp(void)
//{
//}


CXProp::~CXProp ( void )
{
}

void CXPropHelper::toString ( std::string& dst, GString* var )
{
    CXASSERT ( var );
    dst = var->c_str();
}

void CXPropHelper::toString ( std::string& dst, int* var )
{
    CXASSERT ( var );
    GString str;
    str.Format ( "%d", *var );
    dst = str.c_str();
}

void CXPropHelper::toString ( std::string& dst, float* var )
{
    CXASSERT ( var );
    GString str;
    str.Format ( "%f", *var );
    dst = str.c_str();
}

void CXPropHelper::toString ( std::string& dst, bool* var )
{
    dst = ( *var ) ? "True" : "False";
}

void CXPropHelper::setValue ( const char* val, GString* var )
{
    CXASSERT ( val );
    *var = val;
}

void CXPropHelper::setValue ( const char* val, int* var )
{
    CXASSERT ( val );
    sscanf_s ( val, "%d", var );
}

void CXPropHelper::setValue ( const char* val, float* var )
{
    CXASSERT ( val );
    sscanf_s ( val, "%f", var );
}

void CXPropHelper::setValue ( const char* val, bool* var )
{
    *var = !strcmp ( "True", val ) || !strcmp ( "true", val );
}
#pragma warning(pop)

ePropertyType CXPropEnum::getType()
{
    return eType_Enum;
}

const CXDynaArray<CXEnumStruct>& CXPropEnum::getStringList() const
{
    return mStringList;
}


void CXPropEnum::init ( const CXDynaArray<CXEnumStruct>& arr )
{
for ( auto & v: arr  )
    {
        mStringList.push_back ( v );
    }
}

void CXPropEnum::toString ( std::string& dst )
{

}

void CXPropEnum::setValue ( const char* val )
{

}

int CXPropEnum::getIndex ( int var ) const
{
    for ( auto i = 0; i < mStringList.size(); ++i )
    {
        const CXEnumStruct& est = mStringList[i];
        if ( var == est.mValue )
        {
            return i;
        }
    }
    CXASSERT ( 0 );
    return 0;
}

int CXPropEnum::getIndex ( const char* name ) const
{
    for ( auto i = 0; i < mStringList.size(); ++i )
    {
        const CXEnumStruct& est = mStringList[i];
        if ( !strcmp ( name, est.mName ) )
        {
            return i;
        }
    }
    CXASSERT ( 0 );
    return 0;
}

int CXPropEnum::getIndex() const
{
    int v = 0;
    dCast ( v, mVar );
    return getIndex ( v );
}

int CXPropEnum::getValue( int idx ) const
{
	return mStringList[idx].mValue;
}
