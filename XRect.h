#pragma once
#include "XPoint2.h"
class CXRect
{
public:
    CXRect ( void );
    ~CXRect ( void );
    CXRect ( long x, long y, long w, long h );
    bool operator== ( const CXRect& rhs ) const;
    bool operator!= ( const CXRect& rhs ) const;
    CXRect& operator= ( const CXRect& rhs );
    long mX;
    long mY;
    long mW;
    long mH;

    CXPoint2 center() const;
    bool contain ( const CXPoint2& pt ) const;
    bool contain ( long x, long y ) const;
    long right() const;
    long bottom() const;
    long area() const;
    bool isOverlaps ( const CXRect& rc ) const;
    void offset ( long x, long y );
    void correct();
    void clamp ( const CXRect& rc );
    void scaleX ( double scale, long xRef );
    void scaleY ( double scale, long yRef );
    void scale ( double scale, long xref, long yref );
};


inline CXRect::~CXRect ( void )
{
}

inline bool CXRect::isOverlaps ( const CXRect& rc ) const
{
    long x0 = dMax ( mX, rc.mX );
    long y0 = dMax ( mY, rc.mY );
    long x1 = dMin ( right(), rc.right() );
    long y1 = dMin ( bottom(), rc.bottom() );

    return x0 < x1 && y0 < y1;
}

inline long CXRect::right() const
{
    return mX + mW;
}

inline long CXRect::bottom() const
{
    return mY + mH;
}

inline long CXRect::area() const
{
    return mW * mH;
}

inline CXRect::CXRect()
{
    mX = 0;
    mY = 0;
    mW = 1;
    mH = 1;
}
inline CXRect::CXRect ( long x, long y, long w, long h )
{
    mX = x;
    mY = y;
    mW = w;
    mH = h;
}

inline bool CXRect::contain ( long x, long y ) const
{
    return x >= mX && x <= right() && y >= mY && y <= bottom();
}

inline bool CXRect::contain ( const CXPoint2& pt ) const
{
    return contain ( pt.mX, pt.mY );
}

inline bool CXRect::operator== ( const CXRect& rhs ) const
{
    return mX == rhs.mX && mY == rhs.mY && mW == rhs.mW && mH == rhs.mH;
}

inline bool CXRect::operator!= ( const CXRect& rhs ) const
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

inline CXPoint2 CXRect::center() const
{
    CXPoint2 pt;
    pt.mX = mX + mW / 2;
    pt.mY = mY + mH / 2;
    return pt;
}

inline void CXRect::offset ( long x, long y )
{
    mX += x;
    mY += y;
}

inline CXRect& CXRect::operator= ( const CXRect& rhs )
{
    mX = rhs.mX;
    mY = rhs.mY;
    mW = rhs.mW;
    mH = rhs.mH;
    return *this;
}

inline void CXRect::correct()
{
    if ( mW < 0 )
    {
        mX += mW;
        mW = -mW;
    }
    if ( mH < 0 )
    {
        mY += mH;
        mH = -mH;
    }
}

inline void CXRect::clamp ( const CXRect& rc )
{
    CXRect tmp ( rc );
    tmp.correct();
    this->correct();
    long r = right(), b = bottom();
    mX = dClamp ( mX, rc.mX, rc.right() );
    mY = dClamp ( mY, rc.mY, rc.bottom() );
    r = dClamp ( r, rc.mX, rc.right() );
    b = dClamp ( b, rc.mY, rc.bottom() );
    mW = r - mX;
    mH = b - mY;
}


inline void CXRect::scaleY ( double scale, long yRef )
{
    mY = dScale ( mY, yRef, scale );
    mH *= scale;
}

inline void CXRect::scaleX ( double scale, long xRef )
{
    mX = dScale ( mX, xRef, scale );
    mW *= scale;
}

inline void CXRect::scale ( double scale, long xref, long yref )
{
    scaleX ( scale, xref );
    scaleY ( scale, yref );
}
