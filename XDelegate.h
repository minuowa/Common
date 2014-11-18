#pragma once
#include "XDynaArray.h"
#include "base.h"
class CXDelegate;
class CXCallBack
{
public:
    virtual ~CXCallBack()
    {
    }
    virtual void onCallBack ( const CXDelegate&  )
    {
    }
};

class CXDelegate: public CXDynaArray<CXCallBack*>
{
public:
    typedef CXDynaArray<CXCallBack*> SuperType;
    virtual ~CXDelegate ( void );

    CXDelegate& operator+= ( CXCallBack* callback )
    {
        CXASSERT ( !this->Find ( callback ) );
        this->push_back ( callback );
        return *this;
    }
    CXDelegate& operator-= ( CXCallBack* callback )
    {
        iterator iter = std::find ( this->begin(), this->end(), callback );
        if ( iter != this->end() )
            this->erase ( iter );
        return *this;
    }
    void trigger()
    {
for ( auto callback: ( *this ) )
        {
            callback->onCallBack ( *this );
        }
    }
};
inline bool operator== ( const CXDelegate& lhs, const CXDelegate& rhs )
{
    return &lhs == &rhs;
}
