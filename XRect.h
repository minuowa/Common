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

