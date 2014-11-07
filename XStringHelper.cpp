#include "base.h"
#include "XStringHelper.h"
#pragma warning(push)
#pragma warning(disable:4996)
void CXStringHelper::toString ( std::string& dst, GString* var )
{
	CXASSERT ( var );
	dst = var->c_str();
}

void CXStringHelper::toString ( std::string& dst, int* var )
{
	CXASSERT ( var );
	GString str;
	str.Format ( "%d", *var );
	dst = str.c_str();
}

void CXStringHelper::toString ( std::string& dst, float* var )
{
	CXASSERT ( var );
	GString str;
	str.Format ( "%f", *var );
	dst = str.c_str();
}

void CXStringHelper::toString ( std::string& dst, bool* var )
{
	dst = ( *var ) ? "True" : "False";
}

void CXStringHelper::toString( std::string& dst, unsigned int* var )
{
	CXASSERT ( var );
	GString str;
	str.Format ( "%u", *var );
	dst = str.c_str();
}

void CXStringHelper::setValue ( const char* val, GString* var )
{
	CXASSERT ( val );
	*var = val;
}

void CXStringHelper::setValue ( const char* val, int* var )
{
	CXASSERT ( val );
	sscanf_s ( val, "%d", var );
}

void CXStringHelper::setValue ( const char* val, float* var )
{
	CXASSERT ( val );
	sscanf_s ( val, "%f", var );
}

void CXStringHelper::setValue ( const char* val, bool* var )
{
	*var = !strcmp ( "True", val ) || !strcmp ( "true", val );
}

void CXStringHelper::setValue( const char* val, unsigned int* var )
{
	CXASSERT ( val );
	sscanf_s ( val, "%d", var );
}

#pragma warning(pop)