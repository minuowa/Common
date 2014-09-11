#pragma once
#include "XDynaArray.h"
class CXDelegate;
class CXCallBack
{
public:
	virtual ~CXCallBack()
	{
	}
	virtual void onCallBack(const CXDelegate& delgate)
	{
	}
};

class CXDelegate:public CXDynaArray<CXCallBack*>
{
public:
	typedef CXDynaArray<CXCallBack*> SuperType;
	virtual ~CXDelegate(void);

	CXDelegate& operator+=(CXCallBack* callback)
	{
		CXASSERT(!this->Find(callback));
		this->push_back(callback);
		return *this;
	}
	void trigger()
	{
		SuperType::iterator iend=this->end();
		for (SuperType::iterator i=this->begin();i!=iend;++i)
		{
			CXCallBack* callback=*i;
			callback->onCallBack(*this);
		}
	}
};
inline bool operator==(const CXDelegate& lhs,const CXDelegate& rhs)
{
	return &lhs==&rhs;
}
