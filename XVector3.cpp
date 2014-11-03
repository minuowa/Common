#include "base.h"
#include "XVector3.h"
CXVector3::CXVector3()
{
	mX = 0;
	mY = 0;
	mZ = 0;
}

CXVector3::CXVector3(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}


float CXVector3::X() const
{
	return mX;
}

float CXVector3::Y() const
{
	return mY;
}

float CXVector3::Z() const
{
	return mZ;
}


void CXVector3::SetX(float x)
{
	mX = x;
}

void CXVector3::SetY(float y)
{
	mY = y;
}

void CXVector3::SetZ(float z)
{
	mZ = z;
}


float CXVector3::Length()
{
	return sqrt(pow(mX, 2) + pow(mY, 2) + pow(mZ, 2));
}

float CXVector3::LengthSquared()
{
	return pow(mX, 2) + pow(mY, 2) + pow(mZ, 2);
}


float CXVector3::Distance(CXVector3 other)
{
	return sqrt(pow(other.X() - mX, 2) + pow(other.Y() - mY, 2) + pow(other.Z() - mZ, 2));
}

float CXVector3::DistanceSquared(CXVector3 other)
{
	return pow(other.X() - mX, 2) + pow(other.Y() - mY, 2) + pow(other.Z() - mZ, 2);
}


float CXVector3::Dot(CXVector3 other)
{
	return (mX * other.X()) + (mY * other.Y()) + (mZ * other.Z());
}

CXVector3 CXVector3::Cross(CXVector3 other)
{
	CXVector3 result;

	result.SetX((mY * other.Z()) - (other.Y() * mZ));
	result.SetY((mZ * other.X()) - (other.Z() * mX));
	result.SetZ((mX * other.Y()) - (other.X() * mY));

	return result;
}


void CXVector3::Normalize()
{
	float length = Length();

	mX = mX/length;
	mY = mY/length;
	mZ = mZ/length;
}

CXVector3 CXVector3::Normalized()
{
	CXVector3 result;
	float length = Length();

	result.SetX(mX/length);
	result.SetY(mY/length);
	result.SetZ(mZ/length);

	return result;
}

CXVector3 CXVector3::operator+(const CXVector3 &rhs)
{
	CXVector3 vector = *this;
	vector += rhs;
	return vector;
}

CXVector3& CXVector3::operator+=(const CXVector3 &rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;
	mZ += rhs.mZ;
	return *this;
}

CXVector3 CXVector3::operator-(const CXVector3 &rhs)
{
	CXVector3 vector = *this;
	vector -= rhs;
	return vector;
}

CXVector3& CXVector3::operator-=(const CXVector3 &rhs)
{
	mX -= rhs.mX;
	mY -= rhs.mY;
	mZ -= rhs.mZ;
	return *this;
}

CXVector3 CXVector3::operator*(const float &rhs)
{
	CXVector3 vector = *this;
	vector *= rhs;
	return vector;
}

CXVector3& CXVector3::operator*=(const float &rhs)
{
	mX *= rhs;
	mY *= rhs;
	mZ *= rhs;
	return *this;
}

CXVector3 CXVector3::operator/(const float &rhs)
{
	CXVector3 vector = *this;
	vector /= rhs;
	return vector;
}

CXVector3& CXVector3::operator/=(const float &rhs)
{
	mX /= rhs;
	mY /= rhs;
	mZ /= rhs;
	return *this;
}