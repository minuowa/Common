#ifndef CXStringHelper_h__
#define CXStringHelper_h__
#include "XString.h"
namespace CXStringHelper
{
	void toString ( std::string& dst, GString* var );
	void toString ( std::string& dst, int* var );
	void toString ( std::string& dst, float* var );
	void toString ( std::string& dst, bool* var );

	void setValue ( const char* val, GString* var );
	void setValue ( const char* val, int* var );
	void setValue ( const char* val, float* var );
	void setValue ( const char* val, bool* var );
}

#endif // CXStringHelper_h__
