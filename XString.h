#ifndef CXString_h__
#define CXString_h__
//--------------------------------------------------------------------------------------------------
#include <string>
#include <vadefs.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "XDynaArray.h"
#include "base.h"
//inline wchar_t* towchar( const char* src );

//std::string ToString( const wchar_t* ws )
//{
//	std::string res;
//	return res;
//}
//std::wstring ToString( const char* s )
//{
//	std::wstring res;
//	res.assign( ToString( s ) );
//	return res;
//}

inline size_t XGetLength ( const char * _Format, va_list arglist )
{
    return _vscprintf ( _Format, arglist );
}
inline size_t XGetLength ( const wchar_t * _Format, va_list arglist )
{
    return _vscwprintf ( _Format, arglist );
}
inline size_t XSPrintf ( char* dstBuffer, size_t size, const char* format, _locale_t _Locale, va_list args )
{
    return _vsprintf_s_l ( dstBuffer, size, format, _Locale, args );
}
inline size_t XSPrintf ( wchar_t* dstBuffer, size_t size, const wchar_t* format, _locale_t _Locale, va_list args )
{
	return _vswprintf_s_l ( dstBuffer, size, format, _Locale, args );
}
template<typename T>
class CXCharString: public std::basic_string<T>
{
public:
    enum ValueType
    {
        XieGang = '/',
        MaoHao = ':',
        Dot = '.',
    };
    enum Mode
    {
        Case = 0,         ///< Case sensitive
        NoCase = 1,       ///< Case insensitive
        Left = 0,         ///< Start at left end of string
        Right = 2,        ///< Start at right end of string
    };
public:
    typedef T MyChar;
	typedef CXCharString<MyChar> MyType;
    typedef std::basic_string<MyChar> Supper;
    CXCharString() {}
#include "XString.inl"
private:

};


inline int FindString ( stdString src, const char* s )
{
    if ( !s )
        return stdString::npos;

    if ( !strlen ( s ) )
        return 0;

    XI32 pos = 0;
    XI32 nFinPos = 0;

    while ( pos != stdString::npos )
    {
        pos = src.find ( s );

        if ( pos == stdString::npos || pos == 0 || !IS_WIDE_CHAR ( *s ) )
            return pos;

        const char* tmp = src.c_str();
        int nIndex = 0;

        while ( tmp != '\0' )
        {
            if ( IS_WIDE_CHAR ( *tmp ) )
            {
                tmp += 2;
                nIndex += 2;
            }
            else
            {
                tmp += 1;
                nIndex += 1;
            }

            if ( nIndex == pos )
            {
                return ( nFinPos + pos );
            }
            else if ( nIndex > pos )
            {
                if ( *tmp == '\0' )
                    return stdString::npos;

                src = stdString ( tmp );
                nFinPos += nIndex;
                break;
            }
        }
    }

    return -1;
}
//--------------------------------------------------------------------------------------------------
inline XI32 FindString ( stdString src, stdString sub )
{
    return FindString ( src, sub.c_str() );
}
inline bool SuccessFindStr ( stdString subStr, stdString str )
{
    if ( FindString ( str, subStr ) == stdString::npos )
        return false;

    return true;
}

//--------------------------------------------------------------------------------------------------
typedef CXCharString<char> String;
typedef CXCharString<wchar_t> StringW;
//typedef  CXDynaArray<CharString> CXStringDynaArr;


#endif // CXString_h__

