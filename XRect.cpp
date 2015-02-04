#include "base.h"
#include "XRect.h"



CXRect::~CXRect ( void )
{
}

bool CXRect::isOverlaps ( const CXRect& rc ) const
{
    if ( rc.contain ( this->center() ) )
    {
        return true;
    }
    if ( contain ( rc.center() ) )
    {
        return true;
    }

    return false;
}

long CXRect::right() const
{
    return mX + mW;
}

long CXRect::bottom() const
{
    return mY + mH;
}

long CXRect::area() const
{
    return mW * mH;
}

CXRect::CXRect()
{
    mX = 0;
    mY = 0;
    mW = 1;
    mH = 1;
}

bool CXRect::contain ( long x, long y ) const
{
    return x >= mX && x <= right() && y >= mY && y <= bottom();
}

bool CXRect::contain ( const CXPoint2& pt ) const
{
    return contain ( pt.mX, pt.mY );
}

bool CXRect::operator== ( const CXRect& rhs ) const
{
    return mX == rhs.mX && mY == rhs.mY && mW == rhs.mW && mH == rhs.mH;
}

bool CXRect::operator!= ( const CXRect& rhs ) const
{
    if ( mX != rhs.mX )
        return true;
    if ( mY != rhs.mY )
        return true;
    if ( mW != rhs.mW )
        return true;
    if ( mH != rhs.mH )
        return true;
    return false;
}

CXPoint2 CXRect::center() const
{
    CXPoint2 pt;
    pt.mX = mX + mW / 2;
    pt.mY = mY + mH / 2;
    return pt;
}
