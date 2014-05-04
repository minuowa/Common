#include <crtdefs.h>
#include <stdarg.h>
//--------------------------------------------------------------------------------------------------
ThisType ( const ThisType& rhs )
{
    clear();
    assign ( rhs.c_str() );
}
bool equal ( const ThisType& rhs ) const
{
    return operator== ( rhs );
}
void Format ( const ThisChar * _Format, ... )
{
    va_list arglist;
    va_start ( arglist, _Format );
    int nLen = XGetLength ( _Format, arglist ) /* + 1*/;
    assign ( nLen /*+ 1*/, 0 );
    XSPrintf ( ( ThisChar* ) c_str(), nLen + 1, _Format, 0, arglist );

    va_end ( arglist );
}
//XI32 GetByteCount()
//{
//    return length();
//}
ThisType ( Supper s )
{
    _Tidy();
    assign ( s.c_str() );
}
operator const ThisChar*()
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
ThisType operator+ ( ThisChar* v )
{
    ThisType tmp = this;
    tmp.append ( v );
    return tmp;
}
int Find ( const ThisChar* s )
{
    return FindString ( stdString ( c_str() ), s );
}
bool Exist ( const ThisChar* s )
{
    return Find ( s ) != npos;
}
bool isEmpty() const
{
    return empty();
}
bool operator == ( const ThisChar* s ) const
{
    return !compare ( s );
}
bool operator == ( const ThisType& rhs ) const
{
    return 0 == compare ( rhs.c_str() );
}