#pragma once
#include "XPoint2.h"
class CXRect
{
public:
    CXRect ( void );
    ~CXRect ( void );
    bool operator== ( const CXRect& rhs ) const;
    bool operator!= ( const CXRect& rhs ) const;
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
};

inline CXRect::~CXRect ( void )
{
}

inline bool CXRect::isOverlaps ( const CXRect& rc ) const
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