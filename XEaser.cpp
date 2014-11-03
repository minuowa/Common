#include "base.h"
#include "XEaser.h"

CXEaser gEaser;

CXEaser::CXEaser ( void )
{
}


CXEaser::~CXEaser ( void )
{
}

float CXEaser::getEase ( float start, float end, float elapsedTime, float totalTime )
{
    return start + ( end - start ) * sinf ( elapsedTime / totalTime * 3.1415926535 *0.5);
}
