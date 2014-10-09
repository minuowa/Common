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
    void trigger()
    {
        for ( size_t i = 0; i < this->size(); ++i )
        {
            CXCallBack* callback = ( *this ) [i];
            callback->onCallBack ( *this );
        }
    }
};
inline bool operator== ( const CXDelegate& lhs, const CXDelegate& rhs )
{
    return &lhs == &rhs;
}
