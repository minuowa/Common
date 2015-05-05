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
// TODO: 在此处引用程序需要的其他头文件
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned char uchar;

#pragma comment(lib,"lua.lib")

#pragma warning(disable:4244)
#pragma warning(disable:4251)//需要有 dll 接口由 class“GRectNode”的客户端使用
#pragma warning(disable:4275)
#pragma warning(disable:4305)
#pragma warning(disable:4800)

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#define CXASSERT(exp)				if(!(exp)){assert(0);}
#define CXASSERT_RETURN(exp)		if(!(exp)){assert(0);return;}
#define CXASSERT_RETURN_FALSE(exp)	if(!(exp)){assert(0);return false;}

#define CXCheck(exp) assert(exp)

#define CXASSERT_RESULT(exp)		if(FAILED(exp)){__debugbreak();return;}
#define CXASSERT_RESULT_FALSE(exp)	if(FAILED((exp))) {__debugbreak();return false;}

#define BIT(n) (1<<n)

#define IS2SQUARE(n) (0==(n&(n-1)))

#define CXUnuse(v) (void)v;

#include <xstring>
#include <string>
#include <vector>
#include <algorithm>

#include <iostream>
#include <fstream>

typedef std::string					stdString;
typedef std::vector<stdString>		stdStringArr;
//--------------------------------------------------------------------------------------------------
#define STRING_NO_RESULT stdString::npos
//--------------------------------------------------------------------------------------------------
#include <string>
#include <assert.h>

typedef std::string StdString;
typedef std::wstring StdWString;

#define CXDefineOnce __declspec(selectany)

#define WIDE_CHAR_FLAG 0X80
#define IS_WIDE_CHAR(c) (WIDE_CHAR_FLAG & (c))
#ifdef UNICODE
typedef std::wstring CXString;
#else
typedef std::string CXString;
#endif

typedef unsigned int XUI32;
typedef int	XI32;
typedef short s16;
typedef float f32;

#define ISIN(x,min,max) ( x>=min && x<=max )

#ifdef _LIB
#define CX_LIB	__declspec(dllexport)
#else
#define CX_LIB  __declspec(dllimport)
#endif


#define CXNew new
#define CXDelete delete

#define dSafeDelete(x) {if(x){ delete x;x=nullptr;}}
#define dSequare(x) (x)*(x)
#define dSumOfSequare(x,y) (dSequare(x)+dSequare(y))
#define dMin(x,y) ((x)<(y)?(x):(y))
#define dMax(x,y) ((x)>(y)?(x):(y))

#define dSafeRelease(v) if(v){v->Release();v=nullptr;}

inline void dDebugOutWithFile ( const char* file, int line, const char* fmt, ... )
{
	//va_list arglist;
	//va_start ( arglist, fmt );
	//int nLen = XGetLength ( fmt, arglist ) /* + 1*/;
	//char* buffer = new char[nLen + 1];
	//XSPrintf ( buffer, nLen + 1, fmt, 0, arglist );
	//va_end ( arglist );
	//uString str, str2;
//#ifdef WIN32
//	str2.format( "%s(%d):", file, line );
//	str.append ( str2 );
//#endif
//	str.append ( buffer );
//	str.append ( "\n" );
#ifdef WIN32
	//OutputDebugStringA ( str.c_str() );
#else
	std::cout << str.c_str();
#endif
	//delete[] buffer;
}

#define dDebugOut(fmt,...) dDebugOutWithFile(__FILE__,__LINE__,fmt,__VA_ARGS__)

template<typename T>
void dConstruct ( void* ptr )
{
    ::new ( ptr ) T;
}
template<typename T, typename E>
void dRemoveChild ( T& v, E* e )
{
    typename T::iterator i = std::find ( v.begin(), v.end(), e );
    if ( i != v.end() )
        v.erase ( i );
}
template<typename T>
void dSafeDeleteVector ( T& v )
{
    if ( v.size() > 0 )
    {
        typename T::iterator it = v.begin();
        typename T::iterator end = v.end();
        for ( ; it != end; ++it )
        {
            dSafeDelete ( *it );
        }
        v.clear();
    }
}
template<typename T, XI32 N>
void dSafeDeleteArray ( T * ( &arr ) [N] )
{
for ( auto & i: arr )
        dSafeDelete ( i );
}
template<typename T>
void dSafeDeleteMap2 ( T& v )
{
    typename T::iterator it = v.begin();
    typename T::iterator end = v.end();
    for ( ; it != end; ++it )
    {
        dSafeDelete ( it->second );
    }
    v.clear();
}
inline void dMemoryZero ( void* p, XI32 len )
{
    CXASSERT ( p );
    memset ( p, 0, len );
}
#define dMemoryZeroStruct(p) memset(p,0,sizeof(*p))
#define dToggle(b) (b=!b)

inline void dMemoryCopy ( void* dst, void* src, XI32 len )
{
    CXASSERT ( dst && src );
    memcpy ( dst, src, len );
}
template<typename T, XI32 N>
void dMemoryZeroArray ( T ( &arr ) [N] )
{
    dMemoryZero ( &arr, sizeof ( T ) *N );
}
inline bool dStrEqual ( const char* s1, const char* s2 )
{
    return 0 == strcmp ( s1, s2 );
}
inline u32 dStrLen ( const wchar_t* s )
{
    CXASSERT ( s != 0 );
    return wcslen ( s );
}
inline u32 dStrLen ( const char* s )
{
    CXASSERT ( s != 0 );
    return strlen ( s );
}

template<typename T, XI32 N>
const XI32 dArrayCount ( T ( &arr ) [N] )
{
    return N;
}

template<typename T1, typename T2>
void dCast ( T1& dst, T2* src )
{
    dst = * ( ( T1* ) src );
}
template<typename T1, typename T2>
void dCast ( T1* dst, T2 src )
{
    * ( ( T2* ) dst ) = src;
}

#define dMemberOffset(ClassName,memberName)\
	((int)&((ClassName*)0)->memberName)


#define GCat(a,b)		a##b
#define GCatF(a,b)		GCat(a,b)
#define GCatCount(a)	GCatF(a,__COUNTER__)

#define FLOAT_MAX (3.40E+38)
#define FLOAT_MIN (-FLOAT_MAX)

#define DOUBLE_MAX (1.79E+308)
#define DOUBLE_MIN (-DOUBLE_MAX)