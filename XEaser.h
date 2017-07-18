#pragma once
class CXEaser {
  public:
    float getEase(float start, float end, float elapsedTime, float totalTime);
};

inline float CXEaser::getEase(float start, float end, float elapsedTime, float totalTime) {
    return start + (end - start) * sinf(elapsedTime / totalTime * 3.1415926535 * 0.5);
}
extern CXEaser gEaser;
CXDefineOnce CXEaser gEaser;


