// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include <assert.h>

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料

#define QUOTE_NONE_STRING ""

typedef char Char;
typedef const char CChar;
typedef wchar_t WChar;
typedef const wchar_t CWChar;

#define CXASSERT(exp)		if(!(exp)){__debugbreak();}
#define CXASSERT_RETURN(exp) if(!(exp)){CXASSERT(0);return;}
#define CXASSERT_RETURN_FALSE(exp) if(!(exp)){CXASSERT(0);return false;}
#define CXASSERT_RESULT_FALSE(exp) if(FAILED((exp))) {CXASSERT(0);return false;}
#define BIT(n) (1<<n)

#define CXUnuse(v) (void)v;

#include <string>
#include <vector>
#include <algorithm>
typedef std::string					stdString;
typedef std::vector<stdString>		stdStringArr;
//--------------------------------------------------------------------------------------------------
#define STRING_NO_RESULT stdString::npos
//--------------------------------------------------------------------------------------------------
#include <string>
#include <assert.h>

typedef std::string StdString;
typedef std::wstring StdWString;

#define WIDE_CHAR_FLAG 0X80
#define IS_WIDE_CHAR(c) (WIDE_CHAR_FLAG & (c))
#ifdef UNICODE
typedef std::wstring CXString;
#else
typedef std::string CXString;
#endif

typedef unsigned int XUI32;
typedef int	XI32;
typedef short XS16;
typedef float XF32;

#define CHECK(exp)					assert(exp)
#define CHECK_RETURN_BOOL(exp)		{if(!exp){ assert(0);return false;}}
#define CHECK_RETURN(exp)			{if(!exp){ assert(0);return;}}
#define CHECK_RESULT_BOOL(exp)		{if(!SUCCEEDED(exp)){ assert(0);return false;}}
#define ISIN(x,min,max) ( x>=min && x<=max )

#ifdef _LIB
#define CX_LIB	__declspec(dllexport)
#else
#define CX_LIB  __declspec(dllimport)
#endif


#define CXNew new
#define CXDelete delete

template<typename T>
void CXSafeDelete ( T*& v )
{
    if ( v )
    {
        CXDelete v;
        v = 0;
    }
}
template<typename T>
T CXMin ( const T& v1, const T& v2 )
{
    if ( v1 < v2 )
        return v1;
    return v2;
}
template<typename T>
void CXSafeRelease ( T*& v )
{
    if ( v )
    {
        v->Release();
        v = 0;
    }
}
template<typename T>
void CXSafeDeleteArray ( T& v )
{
    typename T::iterator it = v.begin();
    typename T::iterator end = v.end();
    for ( ; it != end; ++it )
    {
        CXSafeDelete ( *it );
    }
    v.clear();
}
template<typename T>
void CXSafeDeleteMap2 ( T& v )
{
    typename T::iterator it = v.begin();
    typename T::iterator end = v.end();
    for ( ; it != end; ++it )
    {
        CXSafeDelete ( it->second );
    }
    v.clear();
}
inline void CXMemoryZero ( void* p, XI32 len )
{
    CXASSERT ( p );
    memset ( p, 0, len );
}
inline void CXMemoryCopy ( void* dst, void* src, XI32 len )
{
    CXASSERT ( dst && src );
    memcpy ( dst, src, len );
}
template<typename T, XI32 N>
void CXMemoryZeroArray ( T ( &arr ) [N] )
{
    CXMemoryZero ( &arr, sizeof ( T ) *N );
}
template<typename T, XI32 N>
const XI32 CXArrayCount ( T ( &arr ) [N] )
{
    return N;
}

#define CXMemberOffset(ClassName,memberName)\
    ((int)&((ClassName*)0)->memberName)

// TODO: 在此处引用程序需要的其他头文件
typedef unsigned int U32;
typedef int S32;

#define CXDeclareSingleton(ClassName) \
	private:\
	static ClassName* mInstance;\
	public:\
	static ClassName& GetSingleton()	{ if(!mInstance) { static ClassName instance; mInstance=&instance;}	return *mInstance;}\
	static ClassName* GetSingletonPtr()	{ return &GetSingleton();}

#define CXImpleteSingleton(ClassName) \
	ClassName* ClassName::mInstance=0;
#define FLOAT_MAX (3.40E+38)
#define FLOAT_MIN (-FLOAT_MAX)

#define DOUBLE_MAX (1.79E+308)
#define DOUBLE_MIN (-DOUBLE_MAX)