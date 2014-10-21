#include "base.h"
#include "XRandom.h"
CXRandom gRandom;
CXRandomIniter::CXRandomIniter()
{
	CXRandom::init();
}

CXRandomIniter CXRandom::mRandomIniter;
