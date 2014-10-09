#include "base.h"
#include "XProp.h"

//CXProp::CXProp(void)
//{
//}


CXProp::~CXProp ( void )
{
}

void CXPropHelper::toString ( std::string& dst, String* var )
{
    CXASSERT ( var );
    dst = var->c_str();
}

void CXPropHelper::toString ( std::string& dst, int* var )
{
    CXASSERT ( var );
    String str;
    str.Format ( "%d", *var );
    dst = str.c_str();
}

void CXPropHelper::toString ( std::string& dst, float* var )
{
    CXASSERT ( var );
    String str;
    str.Format ( "%f", *var );
    dst = str.c_str();
}

void CXPropHelper::toString ( std::string& dst, bool* var )
{
    dst = ( *var ) ? "True" : "False";
}

void CXPropHelper::setValue ( const char* val, String* var )
{
    CXASSERT ( val );
    *var = val;
}

void CXPropHelper::setValue ( const char* val, int* var )
{
    CXASSERT ( val );
    sscanf ( val, "%d", var );
}

void CXPropHelper::setValue ( const char* val, float* var )
{
    CXASSERT ( val );
    sscanf ( val, "%f", var );
}

void CXPropHelper::setValue ( const char* val, bool* var )
{
    *var = !strcmp ( "True", val ) || !strcmp ( "true", val );
}
