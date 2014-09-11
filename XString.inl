#include <crtdefs.h>
#include <stdarg.h>
//--------------------------------------------------------------------------------------------------
MyType ( const MyChar* s )
{
    clear();
    assign ( s );
}

MyType ( MyChar* s )
{
    clear();
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
    v = ( int ) atoi ( c_str() );
}
void ToValue ( float& v )
{
    v = ( float ) atof ( c_str() );
}
void ToValue ( double& v )
{
    v = ( double ) atof ( c_str() );
}
MyType operator+ ( MyChar* v )
{
    MyType tmp = this;
    tmp.append ( v );
    return tmp;
}
int Find ( const MyChar* s )
{
    return FindString ( stdString ( c_str() ), s );
}
bool Exist ( const MyChar* s )
{
    return Find ( s ) != npos;
}
bool isEmpty() const
{
    return empty();
}
bool operator == ( const MyChar* s ) const
{
    return !compare ( s );
}
bool operator == ( const MyType& rhs ) const
{
    return 0 == compare ( rhs.c_str() );
}
inline void Splite ( const MyChar ch, CXDynaArray<MyType>& out )
{
    String ele;
    for ( size_t i = 0; i < length(); ++i )
    {
        if ( at ( i ) == ch )
        {
            out.push_back ( ele );
            ele.clear();
        }
        else
        {
            ele.appendChar ( at ( i ) );
        }
    }
}
inline MyType& appendChar ( MyChar ch )
{
    append ( 1, ch );
    return *this;
}