#include "base.h"
#include "XBuffer.h"


CXBuffer::CXBuffer ( void )
{
    mData = 0;
    mCount = 0;
}


CXBuffer::~CXBuffer ( void )
{
    dSafeDelete ( mData );
}

void CXBuffer::reAllocate ( XUI32 count )
{
    dSafeDelete ( mData );
    mCount = count;
    mData = new char[count];
    dMemoryZero ( mData, mCount * mElementSize );
}




