#ifndef CXBase_h__
#define CXBase_h__
//--------------------------------------------------------------------------------------------------
#include "base.h"
#include "XSingleton.h"
#include "XCharString.h"
#include "XMap.h"

#ifndef CPP1999
#include "XHashMap.h"
#include "XLuaScript.h"
#include "XStrongPtr.h"
#include "XWeakPtr.h"
#include "XMultiMap.h"
#endif

#include "XList.h"
#include "XDynaArray.h"
#include "XStaticArray.h"
#include "XStack.h"
#include "XBiTree.h"
#include "XRapidxmlLoader.h"
#include "XRapidxmlWriter.h"
#include "XIDGenerator.h"
#include "XFileName.hpp"
#include "XMath.h"
#include "XDelegate.h"
#include "XProp.h"
#include "XBuffer.h"
#include "XIndex.h"
#include "XCharString.h"
#include "XRandom.h"
#include "XEaser.h"
#include "XTime.h"
#include "XVector3.h"
#include "XColor.h"
#include "XObjectPool.h"
#include "XBitArray.h"
#include "XIDObjectManager.h"
#include "XRect.h"
#include "XPoint2.h"
#include "XLexer.h"

#include "XTreeNode.h"

#define DeclareFilmObj(type)
#define DeclareFilmObjBase(type,parentType)
#define DeclareFilmTool
#define DeclareFilmToolGlobal

/** @brief 查找一个数组或vector中cur之后的第一个符合条件的元素 **/
template<typename Array, typename T, typename CondtionObj>
T* dFindNextElementInArray ( Array&  arr, T* cur, CondtionObj& funObj )
{
    bool existCur = false;
for ( auto & e: arr )
    {
        if ( existCur && funObj ( e ) )
        {
            return e;
        }
        if ( e == cur )
        {
            existCur = true;
        }
    }
    return nullptr;
}
/** @brief
查找一棵树中(中序遍历)cur之后的第一个符合条件的元素
**/
template<typename T, typename CondtionObj>
T* dFindNextElementInTree ( T*  parent, T* cur, CondtionObj& funObj )
{
    CXASSERT ( parent );
    CXASSERT ( cur );
    bool existCur = parent == cur;
    auto& children = parent->getChildren();
for ( auto & e: children )
    {
        if ( existCur && funObj ( e ) )
        {
            return e;
        }
        if ( e == cur )
        {
            existCur = true;
        }
        T* tar = dFindNextElementInTree ( e, cur, funObj );
        if ( tar != nullptr )
            return tar;
    }
    return nullptr;
}
template<typename T, typename CondtionObj>
T* dFindNextElementInTreeCycle ( T*  parent, T* cur, CondtionObj& funObj )
{
    CXDynaArray<T*> dstArray;
    bool begin = parent == cur;
    bool end = parent == cur;
    takeElementToTopFromTreeToVector ( dstArray, parent, cur, begin );
    takeElementToVectorUntil ( dstArray, parent, cur, end );
    return dFindNextElementInArray ( dstArray, cur, funObj );
}
template<typename T>
void takeElementToTopFromTreeToVector ( CXDynaArray<T*>& dstArray, T* parent, T* cur, bool& begin )
{
    if ( parent == cur )
        begin = true;
    if ( begin )
        dstArray.push_back ( parent );
    auto& children = parent->getChildren();
for ( auto & a: children )
        takeElementToTopFromTreeToVector ( dstArray, a, cur, begin );
}
template<typename T>
void takeElementToVectorUntil ( CXDynaArray<T*>& dstArray, T* parent, T* cur, bool& end )
{
    if ( parent == cur )
    {
        end = true;
        return;
    }
    if ( !end )
        dstArray.push_back ( parent );
    auto& children = parent->getChildren();
for ( auto & a: children )
        takeElementToVectorUntil ( dstArray, a, cur, end );

}

void dConvertToWString ( GStringW& dst, const char* str );
void dConvertToString ( GString& dst, const wchar_t* str );

inline void dDebugOutWithFile ( const char* file, int line, const char* fmt, ... )
{
    va_list arglist;
    va_start ( arglist, fmt );
    int nLen = XGetLength ( fmt, arglist ) /* + 1*/;
    char* buffer = new char[nLen + 1];
    XSPrintf ( buffer, nLen + 1, fmt, 0, arglist );
    va_end ( arglist );
    GString str, str2;
#ifdef WIN32
    str2.Format ( "%s(%d):", file, line );
    str.append ( str2 );
#endif
    str.append ( buffer );
    str.append ( "\n" );
#ifdef WIN32
    OutputDebugStringA ( str.c_str() );
#else
    std::cout << str.c_str();
#endif
    delete[] buffer;
}

inline void dConvertToWString ( GStringW& dst, const char* str )
{
    int len = strlen ( str );

    int iLen = ::MultiByteToWideChar ( CP_ACP, 0, str, len, NULL, 0 );

    if ( iLen > 0 )
    {
        dst.assign ( iLen, 0 );
        iLen = ::MultiByteToWideChar ( CP_ACP, 0, str, -1, ( LPWSTR ) dst.c_str(), iLen );
    }
}

inline void dConvertToString ( GString& dst, const wchar_t* str )
{
    int len = wcslen ( str );

    int iLen = ::WideCharToMultiByte ( CP_ACP, 0, str, len, 0, 0, 0, 0 );

    if ( iLen > 0 )
    {
        dst.assign ( iLen, 0 );
        iLen = ::WideCharToMultiByte ( CP_ACP, 0, str, -1, ( LPSTR ) dst.c_str(), iLen, 0, 0 );
    }
}
#include <sys\stat.h>


inline bool dIsPath ( const char* str )
{
	struct stat info;
	stat ( str, &info );
	return ( ( ( info.st_mode ) & S_IFMT ) == S_IFDIR );
}

#define dDebugOut(fmt,...) dDebugOutWithFile(__FILE__,__LINE__,fmt,__VA_ARGS__)
//--------------------------------------------------------------------------------------------------
#endif // CXBase_h__
