#include "base.h"
#include "XBuffer.h"


CXBuffer::CXBuffer ( void )
{
    mData = 0;
    mCount = 0;
	mCapacity=0;
}


CXBuffer::~CXBuffer ( void )
{
    dSafeDelete ( mData );
}

void CXBuffer::reAllocate ( u32 byteSize )
{
    dSafeDelete ( mData );
    mData = new char[byteSize];
    dMemoryZero ( mData, byteSize );
}

void CXBuffer::reAllocateByElementCount ( u32 cnt )
{
    dSafeDelete ( mData );
	mCapacity=cnt;
    mData = new char[mCapacity * mElementByteCount];
    dMemoryZero ( mData, mCapacity * mElementByteCount );
}








