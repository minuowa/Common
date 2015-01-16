#pragma once
#include "XDynaArray.h"
#include "base.h"
class CXDelegate;
struct CXEventArgs
{
public:
    virtual ~CXEventArgs() 
	{
	};
};
class CXCallBack
{
public:
    virtual ~CXCallBack()
    {
    }
    virtual void onCallBack ( const CXDelegate&, CXEventArgs*  )
    {
    }
};

class CXDelegate: public CXDynaArray<CXCallBack*>
{
public:
    typedef CXDynaArray<CXCallBack*> SuperType;
    virtual ~CXDelegate ( void )
	{

	}

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
    void trigger ( CXEventArgs* event = 0 )
    {
		iterator iEnd=this->end();
		for (iterator i=this->begin();i!=iEnd;++i)
		{
			CXCallBack* callback=*i;
			callback->onCallBack ( *this, event );
		}
    }
};
inline bool operator== ( const CXDelegate& lhs, const CXDelegate& rhs )
{
    return &lhs == &rhs;
}
