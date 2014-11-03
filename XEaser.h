#pragma once
class CXEaser
{
public:
    CXEaser ( void );
    ~CXEaser ( void );
    float getEase ( float start, float end, float elapsedTime, float totalTime );
};
extern CXEaser gEaser;


