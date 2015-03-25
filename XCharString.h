#ifndef CXString_h__
#define CXString_h__
//--------------------------------------------------------------------------------------------------
#include <vadefs.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "XDynaArray.h"
#include "base.h"
#include <crtdefs.h>
#include <stdarg.h>
#include <string>
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
//}
inline int XA2I ( const char* str )
{
    return ( int ) atoi ( str );
}
inline int XA2I ( const wchar_t* str )
{
    return ( int ) _wtoi ( str );
}
inline float XA2F ( const char* str )
{
    return ( int ) atof ( str );
}
inline float XA2F ( const wchar_t* str )
{
    return ( int ) _wtof ( str );
}
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


    //--------------------------------------------------------------------------------------------------
    MyType ( const MyChar* s )
    {
        if ( s == 0 )
            this->clear();
        else
            assign ( s );
    }

    MyType ( MyChar* s )
    {
        if ( s == nullptr )
            this->clear();
        else
            assign ( s );
    }
    MyType ( const MyType& rhs )
    {
        clear();
        assign ( rhs.c_str() );
    }
    bool equal ( const MyType& rhs ) const
    {
        return operator== ( rhs );
    }
    void Format ( const MyChar * _Format, ... )
    {
        va_list arglist;
        va_start ( arglist, _Format );
        int nLen = XGetLength ( _Format, arglist ) /* + 1*/;
        assign ( nLen /*+ 1*/, 0 );
        XSPrintf ( ( MyChar* ) c_str(), nLen + 1, _Format, 0, arglist );

        va_end ( arglist );
    }

    MyType ( const Supper& s )
    {
        _Tidy();
        assign ( s.c_str() );
    }
    operator const MyChar*()
    {
        return c_str();
    }
    void ToValue ( int& v )
    {
        v = XA2I ( this->c_str() );
    }
    void ToValue ( float& v )
    {
        v = ( float ) XA2F ( this->c_str() );
    }
    void ToValue ( double& v )
    {
        v = ( double ) XA2F ( this->c_str() );
    }
    MyType operator+ ( MyChar* v )
    {
        this->append ( v );
        return *this;
    }
    MyType& operator+ ( const MyChar* v )
    {
        this->append ( v );
        return *this;
    }
    int Find ( const MyChar* s )
    {
        return this->find ( s );
    }
    bool Exist ( const MyChar* s )
    {
        return Find ( s ) != npos;
    }
    bool isEmpty() const
    {
        return empty();
    }
    operator size_t ()
    {
        return size_t ( c_str() );
    }
    bool operator == ( const MyChar* s ) const
    {
        return !compare ( s );
    }
    bool operator == ( const MyType& rhs ) const
    {
        return 0 == compare ( rhs.c_str() );
    }
    inline MyType& replace ( const MyChar* src, const MyChar* dst )
    {
        size_type cnt0 = dStrLen ( src );
        size_type pos = this->find ( src );
        while ( pos != npos )
        {
            this->assign ( Supper::replace ( pos, cnt0, dst ) ) ;
            pos = this->find ( src );
        }
        return *this;
    }
    inline void Splite ( const MyChar ch, CXDynaArray<MyType>& out )
    {
        MyType ele;
        for ( size_t i = 0; i < length(); ++i )
        {
            MyChar c = at ( i );
            if ( c == ch )
            {
                out.push_back ( ele );
                ele.clear();
            }
            else
            {
                ele.appendChar ( c );
            }
        }
        if ( !ele.empty() )
            out.push_back ( ele );
    }
    inline MyType& appendChar ( MyChar ch )
    {
        append ( 1, ch );
        return *this;
    }
private:

};
template<class _Elem>
inline size_t hash_value ( const CXCharString<_Elem>& _Str )
{
    // hash string to size_t value
    return ( _STD _Hash_seq ( ( const unsigned char * ) _Str.c_str(),
                              _Str.size() * sizeof ( _Elem ) ) );
}
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
inline XI32 FindString ( const stdString& src, const stdString& sub )
{
    return FindString ( src, sub.c_str() );
}
inline bool SuccessFindStr ( const stdString& subStr, const stdString& str )
{
    return FindString ( str, subStr ) != stdString::npos ;
}

//--------------------------------------------------------------------------------------------------
typedef CXCharString<char> GString;
typedef CXCharString<wchar_t> GStringW;
typedef CXDynaArray<GString> GStringArr;
//typedef  CXDynaArray<CharString> CXStringDynaArr;



#endif // CXString_h__

