#pragma once

//A class for representing a 3d vector or point in space
//written by Kyle Marchev
class CXVector3
{
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

	float operator [](int i) const
	{
		switch(i)
		{
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

	float & operator [](int i) 
	{
		switch(i)
		{
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
