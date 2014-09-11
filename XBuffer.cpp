#include "base.h"
#include "XBuffer.h"

CXBuffer::CXBuffer( void )
    : mBuffer( 0 )
    , mSize( 0 )
{
}

CXBuffer::~CXBuffer( void )
{
    Destroy();
}

bool CXBuffer::Create( XI32 size )
{
    Destroy();

    mBuffer = new char[size];

    assert( mBuffer );

    mSize = size;
    Clear();
    return true;
}

void CXBuffer::Destroy()
{
    CXSafeDelete( mBuffer );
    mSize = 0;
}

void CXBuffer::Clear()
{
    memset( mBuffer, 0, mSize );
}


void CXBuffer::CopyStr( CChar* p )
{
    CXASSERT_RETURN( p );
    CXASSERT_RETURN( mSize >= 1 );
    Clear();
    memcpy( mBuffer, p, mSize - 1 );
}

char& CXBuffer::operator[]( XI32 idx )
{
    assert( idx >= 0 && idx < mSize );
    return mBuffer[idx];
}

void CXBuffer::CopyMem( void* p )
{

}

Char* CXBuffer::GetBufferPoint()
{
    return mBuffer;
}

XI32 CXBuffer::GetBufferSize()
{
    return mSize;
}

String CXBuffer::GetChar( int start, int wordNum )
{
    assert( start < ( int )mSize );
    char* bf = new char[mSize - start];
    memcpy( bf, &mBuffer[start], mSize - start );
    int i = 0, n = 0;

    while ( start + i < ( int )mSize && n < wordNum )
    {
        i += IS_WIDE_CHAR( mBuffer[start + i] ) ? 2 : 1;
        n++;
    }

    bf[i] = '\0';
    return String( bf );
}
