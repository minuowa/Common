#include <crtdefs.h>
#include <stdarg.h>
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
    return FindString ( *this, s );
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
