#ifndef CXStringHelper_h__
#define CXStringHelper_h__
#include "XCharString.h"
namespace CXStringHelper
{
	void toString ( std::string& dst, GString* var );
	void toString ( std::string& dst, int* var );
	void toString ( std::string& dst, float* var );
	void toString ( std::string& dst, bool* var );
	void toString ( std::string& dst, unsigned int* var );

	void setValue ( const char* val, GString* var );
	void setValue ( const char* val, int* var );
	void setValue ( const char* val, float* var );
	void setValue ( const char* val, bool* var );
	void setValue ( const char* val, unsigned int* var );
}
#pragma warning(push)
#pragma warning(disable:4996)
inline void CXStringHelper::toString ( std::string& dst, GString* var )
{
	CXASSERT ( var );
	dst = var->c_str();
}

inline void CXStringHelper::toString ( std::string& dst, int* var )
{
	CXASSERT ( var );
	GString str;
	str.Format ( "%d", *var );
	dst = str.c_str();
}

inline void CXStringHelper::toString ( std::string& dst, float* var )
{
	CXASSERT ( var );
	GString str;
	str.Format ( "%f", *var );
	dst = str.c_str();
}

inline void CXStringHelper::toString ( std::string& dst, bool* var )
{
	dst = ( *var ) ? "True" : "False";
}

inline void CXStringHelper::toString( std::string& dst, unsigned int* var )
{
	CXASSERT ( var );
	GString str;
	str.Format ( "%u", *var );
	dst = str.c_str();
}

inline void CXStringHelper::setValue ( const char* val, GString* var )
{
	CXASSERT ( val );
	*var = val;
}

inline void CXStringHelper::setValue ( const char* val, int* var )
{
	CXASSERT ( val );
	sscanf_s ( val, "%d", var );
}

inline void CXStringHelper::setValue ( const char* val, float* var )
{
	CXASSERT ( val );
	sscanf_s ( val, "%f", var );
}

inline void CXStringHelper::setValue ( const char* val, bool* var )
{
	*var = !strcmp ( "True", val ) || !strcmp ( "true", val );
}

inline void CXStringHelper::setValue( const char* val, unsigned int* var )
{
	CXASSERT ( val );
	sscanf_s ( val, "%d", var );
}

#pragma warning(pop)
#endif // CXStringHelper_h__
