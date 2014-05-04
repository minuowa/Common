#include "base.h"
//#include "XMath.h"
//
//CXMath::CXMath(void)
//{
//}
//
//CXMath::~CXMath(void)
//{
//}
//
//void MatrixToQuaternion( const D3DXMATRIX& m, D3DXQUATERNION& q )
//{
//	float s;
//	float tq[4];
//	int    i, j;
//
//	// Use tq to store the largest trace
//	tq[0] = 1 + m._11+m._22+m._33;
//	tq[1] = 1 + m._11-m._22-m._33;
//	tq[2] = 1 - m._11+m._22-m._33;
//	tq[3] = 1 - m._11-m._22+m._33;
//
//	// Find the maximum (could also use stacked if's later)
//	j = 0;
//	for(i=1;i<4;i++) j = (tq[i]>tq[j])? i : j;
//
//	// check the diagonal
//	if (j==0)
//	{
//		/* perform instant calculation */
//		QW = tq[0];
//		QX = m._23-m._32;
//		QY = m._31-m._13;
//		QZ = m._12-m._21;
//	}
//	else if (j==1)
//	{
//		QW = m._23-m._32;
//		QX = tq[1];
//		QY = m._12+m._21;
//		QZ = m._31+m._13;
//	}
//	else if (j==2)
//	{
//		QW = m._31-m._13;
//		QX = m._12+m._21;
//		QY = tq[2];
//		QZ = m._23+m._32;
//	}
//	else /* if (j==3) */
//	{
//		QW = m._12-m._21;
//		QX = m._31+m._13;
//		QY = m._23+m._32;
//		QZ = tq[3];
//	}
//
//	s = sqrt(0.25f/tq[j]);
//	QW *= s;
//	QX *= s;
//	QY *= s;
//	QZ *= s;
//}
//
//void QuaternionToMatrix( const D3DXQUATERNION& q, D3DXMATRIX& m )
//{
//	float length2 = D3DXQuaternionLength(&q);
//	if (fabs(length2) <= FLOAT_MIN)
//	{
//		m._11 = 0.0; m._21 = 0.0; m._31 = 0.0;
//		m._12 = 0.0; m._22 = 0.0; m._32 = 0.0;
//		m._13 = 0.0; m._23 = 0.0; m._33 = 0.0;
//	}
//	else
//	{
//		float rlength2;
//		// normalize quat if required.
//		// We can avoid the expensive sqrt in this case since all 'coefficients' below are products of two q components.
//		// That is a square of a square root, so it is possible to avoid that
//		if (length2 != 1.0f)
//		{
//			rlength2 = 2.0f/length2;
//		}
//		else
//		{
//			rlength2 = 2.0;
//		}
//
//		// Source: Gamasutra, Rotating Objects Using Quaternions
//		//
//		//http://www.gamasutra.com/features/19980703/quaternions_01.htm
//
//		float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
//
//		// calculate coefficients
//		x2 = rlength2*QX;
//		y2 = rlength2*QY;
//		z2 = rlength2*QZ;
//
//		xx = QX * x2;
//		xy = QX * y2;
//		xz = QX * z2;
//
//		yy = QY * y2;
//		yz = QY * z2;
//		zz = QZ * z2;
//
//		wx = QW * x2;
//		wy = QW * y2;
//		wz = QW * z2;
//
//		// Note. Gamasutra gets the matrix assignments inverted, resulting
//		// in left-handed rotations, which is contrary to OpenGL and OSG's
//		// methodology. The matrix assignment has been altered in the next
//		// few lines of code to do the right thing.
//		// Don Burns - Oct 13, 2001
//		m._11 = 1.0f - (yy + zz);
//		m._21 = xy - wz;
//		m._31 = xz + wy;
//
//
//		m._12 = xy + wz;
//		m._22 = 1.0f - (xx + zz);
//		m._32 = yz - wx;
//
//		m._13 = xz - wy;
//		m._23 = yz + wx;
//		m._33 = 1.0f - (xx + yy);
//	}
//}