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
typedef unsigned int u32;
typedef int s32;
typedef unsigned char uchar;

#define CXASSERT(exp)				if(!(exp)){__debugbreak();}
#define CXASSERT_RETURN(exp)		if(!(exp)){__debugbreak();return;}
#define CXASSERT_RETURN_FALSE(exp)	if(!(exp)){__debugbreak();return false;}

#define CXASSERT_RESULT(exp)		if(FAILED(exp)){__debugbreak();return;}
#define CXASSERT_RESULT_FALSE(exp)	if(FAILED((exp))) {__debugbreak();return false;}
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
typedef short s16;
typedef float f32;

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

//template<typename T>
//void dSafeDelete ( T*& v )
//{
//	if ( v )
//	{
//		CXDelete v;
//		v = 0;
//	}
//}
#define dSafeDelete(x) if(x){ delete x;x=nullptr;}

#define dSequare(x) (x)*(x)
#define dSumOfSequare(x,y) (dSequare(x)+dSequare(y))
#define dMin(x,y) ((x)<(y)?(x):(y))
#define dMax(x,y) ((x)>(y)?(x):(y))
//template<typename T>
//T dMin ( const T& v1, const T& v2 )
//{
//	if ( v1 < v2 )
//		return v1;
//	return v2;
//}
template<typename T>
void dSafeRelease ( T*& v )
{
    if ( v )
    {
        v->Release();
        v = 0;
    }
}
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
template<typename T>
void dSafeDeleteArray ( T* v )
{
    CXDelete []v;
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
	return wcslen ( s );
}
inline u32 dStrLen ( const char* s )
{
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
//#pragma warning(push)
//#pragma warning(disable:4996)
//inline void dSSCanf(const char* format,...)
//{
//	//sscanf_s(format,);
//}
//#pragma warning(pop)

#define dMemberOffset(ClassName,memberName)\
	((int)&((ClassName*)0)->memberName)



//#define CXDeclareSingleton(ClassName) \
//	private:\
//	static ClassName* mInstance;\
//	public:\
//	static ClassName& getSingleton()	{ if(!mInstance) { mInstance=new ClassName;}	return *mInstance;}\
//	static ClassName* getInstance()	{ return &getSingleton();}\
//	static ClassName* DestorySingleton() { if(mInstance) delete mInstance; mInstance=0;}

//#define CXImpleteSingleton(ClassName) \
//	ClassName* ClassName::mInstance=0;

#define CXDefineOnce __declspec(selectany)

#define GCat(a,b)		a##b
#define GCatF(a,b)		GCat(a,b)
#define GCatCount(a)	GCatF(a,__COUNTER__)

#define FLOAT_MAX (3.40E+38)
#define FLOAT_MIN (-FLOAT_MAX)

#define DOUBLE_MAX (1.79E+308)
#define DOUBLE_MIN (-DOUBLE_MAX)