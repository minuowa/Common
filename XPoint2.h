#pragma once
class CXPoint2
{
public:
    CXPoint2 ( void );
    ~CXPoint2 ( void );
    CXPoint2 ( long x, long y );
    long mX;
    long mY;
};

inline CXPoint2::CXPoint2 ( void )
    : mX ( 0 )
    , mY ( 0 )
{
}
inline CXPoint2::CXPoint2 ( long x, long y )
    : mX ( x )
    , mY ( y )
{

}


inline CXPoint2::~CXPoint2 ( void )
{
}