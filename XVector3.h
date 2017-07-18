#pragma once

//A class for representing a 3d vector or point in space
//written by Kyle Marchev
class CXVector3 {
  public:
    CXVector3();
    CXVector3(float x, float y, float z);

    float X() const;
    float Y() const;
    float Z() const;

    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

    float Length();
    float LengthSquared();

    float Distance(CXVector3 other);
    float DistanceSquared(CXVector3 other);

    float Dot(CXVector3 other);
    CXVector3 Cross(CXVector3 other);

    void Normalize();
    CXVector3 Normalized();

    CXVector3 operator+(const CXVector3 &rhs);
    CXVector3& operator+=(const CXVector3 &rhs);
    CXVector3 operator-(const CXVector3 &rhs);
    CXVector3& operator-=(const CXVector3 &rhs);
    CXVector3 operator*(const float &rhs);
    CXVector3& operator*=(const float &rhs);
    CXVector3 operator/(const float &rhs);
    CXVector3& operator/=(const float &rhs);

    float operator [](int i) const {
        switch (i) {
        case 0:
            return mX;
            break;

        case 1:
            return mY;
            break;

        default:
            return mZ;
            break;
        }
    }

    float & operator [](int i) {
        switch (i) {
        case 0:
            return mX;
            break;

        case 1:
            return mY;
            break;

        default:
            return mZ;
            break;
        }
    }

  private:

    float mX;
    float mY;
    float mZ;
};

inline CXVector3::CXVector3() {
    mX = 0;
    mY = 0;
    mZ = 0;
}

inline CXVector3::CXVector3(float x, float y, float z) {
    mX = x;
    mY = y;
    mZ = z;
}


inline float CXVector3::X() const {
    return mX;
}

inline float CXVector3::Y() const {
    return mY;
}

inline float CXVector3::Z() const {
    return mZ;
}


inline void CXVector3::SetX(float x) {
    mX = x;
}

inline void CXVector3::SetY(float y) {
    mY = y;
}

inline void CXVector3::SetZ(float z) {
    mZ = z;
}


inline float CXVector3::Length() {
    return sqrt(pow(mX, 2) + pow(mY, 2) + pow(mZ, 2));
}

inline float CXVector3::LengthSquared() {
    return pow(mX, 2) + pow(mY, 2) + pow(mZ, 2);
}


inline float CXVector3::Distance(CXVector3 other) {
    return sqrt(pow(other.X() - mX, 2) + pow(other.Y() - mY, 2) + pow(other.Z() - mZ, 2));
}

inline float CXVector3::DistanceSquared(CXVector3 other) {
    return pow(other.X() - mX, 2) + pow(other.Y() - mY, 2) + pow(other.Z() - mZ, 2);
}


inline float CXVector3::Dot(CXVector3 other) {
    return (mX * other.X()) + (mY * other.Y()) + (mZ * other.Z());
}

inline CXVector3 CXVector3::Cross(CXVector3 other) {
    CXVector3 result;

    result.SetX((mY * other.Z()) - (other.Y() * mZ));
    result.SetY((mZ * other.X()) - (other.Z() * mX));
    result.SetZ((mX * other.Y()) - (other.X() * mY));

    return result;
}


inline void CXVector3::Normalize() {
    float length = Length();

    mX = mX / length;
    mY = mY / length;
    mZ = mZ / length;
}

inline CXVector3 CXVector3::Normalized() {
    CXVector3 result;
    float length = Length();

    result.SetX(mX / length);
    result.SetY(mY / length);
    result.SetZ(mZ / length);

    return result;
}

inline CXVector3 CXVector3::operator+(const CXVector3 &rhs) {
    CXVector3 vector = *this;
    vector += rhs;
    return vector;
}

inline CXVector3& CXVector3::operator+=(const CXVector3 &rhs) {
    mX += rhs.mX;
    mY += rhs.mY;
    mZ += rhs.mZ;
    return *this;
}

inline CXVector3 CXVector3::operator-(const CXVector3 &rhs) {
    CXVector3 vector = *this;
    vector -= rhs;
    return vector;
}

inline CXVector3& CXVector3::operator-=(const CXVector3 &rhs) {
    mX -= rhs.mX;
    mY -= rhs.mY;
    mZ -= rhs.mZ;
    return *this;
}

inline CXVector3 CXVector3::operator*(const float &rhs) {
    CXVector3 vector = *this;
    vector *= rhs;
    return vector;
}

inline CXVector3& CXVector3::operator*=(const float &rhs) {
    mX *= rhs;
    mY *= rhs;
    mZ *= rhs;
    return *this;
}

inline CXVector3 CXVector3::operator/(const float &rhs) {
    CXVector3 vector = *this;
    vector /= rhs;
    return vector;
}

inline CXVector3& CXVector3::operator/=(const float &rhs) {
    mX /= rhs;
    mY /= rhs;
    mZ /= rhs;
    return *this;
}
