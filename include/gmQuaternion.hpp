/* Copyright (c) 2010-13, Daniele Niero
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this 
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */


//--------------------------------------------------------------------------
// Taken from Imath
// Don Hatch's version of sin(x)/x, which is accurate for very small x.
// Returns 1 for x == 0.
//--------------------------------------------------------------------------
template <typename real>
inline real sinx_over_x (real x)
{
    if (x * x < Math<real>::EPSILON)
        return (real)1.0;
    else
        return (real) sin (x) / x;
}


/*------ Constructors ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real>::Quaternion()
{
    x=(real)0.0; 
    y=(real)0.0;
    z=(real)0.0;
    w=(real)1.0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real>::Quaternion(real x, real y, real z, real w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real>::Quaternion(const Quaternion<real> &values)
{
    this->x = values.x;
    this->y = values.y;
    this->z = values.z;
    this->w = values.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real>::Quaternion(const real *list)
{
    this->x = list[0];
    this->y = list[1];
    this->z = list[2];
    this->w = list[3];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real>::Quaternion(const Matrix3<real>& inMat)
{
    this->fromMatrix3(inMat);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real>::Quaternion(const Matrix4<real>& inMat)
{
    this->fromMatrix4(inMat);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real>::Quaternion(const Vector3<real>& axis, real angle)
{
    this->fromAxisAngle(axis, angle);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real>::Quaternion(real angleX, real angleY, real angleZ)
{
    this->fromEuler(angleX, angleY, angleZ);
}
/*------ Coordinate access ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Quaternion<real>::operator[] (int i) const
{
    if (i>3) {
        throw out_of_range("gmath::Quaternion:\n\t index out of range");
    }
    return *(&x+i);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real& Quaternion<real>::operator[] (int i)
{
    if (i>3) {
        throw out_of_range("gmath::Quaternion:\n\t index out of range");
    }
    return *(&x+i);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real* Quaternion<real>::ptr()
{
    return &x;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
const real* Quaternion<real>::ptr() const
{
    return &x;
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Arithmetic operations ------*/
template <typename real>
Quaternion<real> Quaternion<real>::operator - () const
{
	return Quaternion(-x, -y, -z, -w);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::operator + (const Quaternion<real> &other) const
{
    Quaternion<real> newQuaternion(x+other.x, y+other.y, z+other.z, w+other.w);

    return newQuaternion;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::operator - (const Quaternion<real> &other) const
{
    Quaternion<real> newQuaternion(x-other.x, y-other.y, z-other.z, w-other.w);
    return newQuaternion;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::operator * (real scalar) const
{
    Quaternion<real> newQuaternion(x*scalar, y*scalar, z*scalar, w*scalar);

    return newQuaternion;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::operator * (const Quaternion<real> &other) const
{
    Quaternion<real> result;

    result.x = w*other.x + x*other.w + y*other.z - z*other.y;
    result.y = w*other.y + y*other.w + z*other.x - x*other.z;
    result.z = w*other.z + z*other.w + x*other.y - y*other.x;
    result.w = w*other.w - x*other.x - y*other.y - z*other.z;

    return result;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Quaternion<real>::operator * (const Vector3<real>& vec) const
{
    real tx, ty, tz;
	real rx, ry, rz;

	tx = y * vec.z - z * vec.y;
	ty = z * vec.x - x * vec.z;
	tz = x * vec.y - y * vec.x;

	rx = y * tz - z * ty;
	ry = z * tx - x * tz;
	rz = x * ty - y * tx;

	Vector3<real> v = vec;
	v.x -= (tx*w-rx)*(real)2; 
	v.y -= (ty*w-ry)*(real)2;
	v.z -= (tz*w-rz)*(real)2;
	return v;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::operator / (real scalar) const
{
    Quaternion<real> newQuaternion;
    if (scalar == (real)0.0)
    {
        newQuaternion.x = NAN;
        newQuaternion.y = NAN;
        newQuaternion.z = NAN;
        newQuaternion.w = NAN;
    }
    else
    {
        newQuaternion.x = x/scalar;
        newQuaternion.y = y/scalar;
        newQuaternion.z = z/scalar;
        newQuaternion.w = w/scalar;
    }

    return newQuaternion;
}
/*------ Arithmetic updates ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::operator += (const Quaternion<real> & other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::operator -= (const Quaternion<real> & other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::operator *= (real scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::operator *= (const Quaternion<real> &other)
{
    this->set(w*other.x + x*other.w + y*other.z - z*other.y,
              w*other.y + y*other.w + z*other.x - x*other.z,
              w*other.z + z*other.w + x*other.y - y*other.x,
              w*other.w - x*other.x - y*other.y - z*other.z);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::operator /= (real scalar)
{
    if (scalar == (real)0.0)
    {
        x = NAN;
        y = NAN;
        z = NAN;
        w = NAN;
    }
    else
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
    }
}
/*------ Comparisons ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
bool Quaternion<real>::operator == (const Quaternion<real> & other) const
{
    return (fabs(x-other.x) < Math<real>::EPSILON && 
            fabs(y-other.y) < Math<real>::EPSILON && 
            fabs(z-other.z) < Math<real>::EPSILON &&
            fabs(w-other.w) < Math<real>::EPSILON);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
bool Quaternion<real>::operator != (const Quaternion<real> & other) const
{
    return (fabs(x-other.x) > Math<real>::EPSILON || 
            fabs(y-other.y) > Math<real>::EPSILON || 
            fabs(z-other.z) > Math<real>::EPSILON ||
            fabs(w-other.w) < Math<real>::EPSILON);
}
/*------ Assignments ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::operator = (const Quaternion<real> & other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
}
/*------ Methods ------*/
template <typename real>
void Quaternion<real>::set(real inX, real inY, real inZ, real inW)
{
    x = inX;
    y = inY;
    z = inZ;
    w = inW;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::setToIdentity()
{
	x=(real)0.0; y=(real)0.0; z=(real)0.0; w=(real)1.0; 
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Quaternion<real>::getAxisX() const
{
    return (*this) * Vector3<real>::XAXIS; 
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Quaternion<real>::getAxisY() const
{
    return (*this) * Vector3<real>::YAXIS; 
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Quaternion<real>::getAxisZ() const
{
    return (*this) * Vector3<real>::ZAXIS; 
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
template <typename gmMatrixType>
void Quaternion<real>::fromMatrix(const gmMatrixType &mat)
{
    // Code from Geometric Tools www.geometrictools.com
    // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
    // article "HQuaternion Calculus and Fast Animation".

    const int next[3] = { 1, 2, 0 };

    real trace = mat(0,0) + mat(1,1) + mat(2,2);
    real root;

    if (trace > (real)0)
    {
        // |w| > 1/2, may as well choose w > 1/2
        root = sqrt(trace + (real)1.0);  // 2w
        w = (real)0.5*root;
        root = (real)0.5/root;  // 1/(4w)
        x = (mat(2,1) - mat(1,2))*root;
        y = (mat(0,2) - mat(2,0))*root;
        z = (mat(1,0) - mat(0,1))*root;
    }
    else
    {
        // |w| <= 1/2
        int i = 0;
        if (mat(1,1) > mat(0,0))
        {
            i = 1;
        }
        if (mat(2,2) > mat(i,i))
        {
            i = 2;
        }
        int j = next[i];
        int k = next[j];

        root = sqrt(mat(i,i) - mat(j,j) - mat(k,k) + (real)1.0);
        real* quat[3] = { &x, &y, &z };
        *quat[i] = (real)0.5*root;
        root = (real)0.5/root;
        this->w = (mat(k,j) - mat(j,k))*root;
        *quat[j] = (mat(j,i) + mat(i,j))*root;
        *quat[k] = (mat(k,i) + mat(i,k))*root;
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::fromMatrix3(const Matrix3<real> &mat)
{
    this->fromMatrix< Matrix3<real> >(mat);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Quaternion<real>::toMatrix3() const
{
    real xx = (real)2.0*x*x;
    real yy = (real)2.0*y*y;
    real zz = (real)2.0*z*z;
    real xy = (real)2.0*x*y;
    real zw = (real)2.0*z*w;
    real xz = (real)2.0*x*z;
    real yw = (real)2.0*y*w;
    real yz = (real)2.0*y*z;
    real xw = (real)2.0*x*w;
    return Matrix3<real>(
            (real)1.0-yy-zz, xy-zw, xz+yw,
            xy+zw, (real)1.0-xx-zz, yz-xw,
            xz-yw, yz+xw, (real)1.0-xx-yy
            );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::fromMatrix4(const Matrix4<real> &mat)
{
    this->fromMatrix< Matrix4<real> >(mat);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real> Quaternion<real>::toMatrix4() const
{
    real xx = (real)2.0*x*x;
    real yy = (real)2.0*y*y;
    real zz = (real)2.0*z*z;
    real xy = (real)2.0*x*y;
    real zw = (real)2.0*z*w;
    real xz = (real)2.0*x*z;
    real yw = (real)2.0*y*w;
    real yz = (real)2.0*y*z;
    real xw = (real)2.0*x*w;
    return Matrix4<real>(
            (real)1.0-yy-zz, xy-zw, xz+yw, (real)0.0,
            xy+zw, (real)1.0-xx-zz, yz-xw, (real)0.0,
            xz-yw, yz+xw, (real)1.0-xx-yy, (real)0.0,
            (real)0.0, (real)0.0, (real)0.0, (real)1.0
            );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::setMatrix4(Matrix4<real>& outMat) const
{
    real xx = (real)2.0*x*x;
    real yy = (real)2.0*y*y;
    real zz = (real)2.0*z*z;
    real xy = (real)2.0*x*y;
    real zw = (real)2.0*z*w;
    real xz = (real)2.0*x*z;
    real yw = (real)2.0*y*w;
    real yz = (real)2.0*y*z;
    real xw = (real)2.0*x*w;
    outMat.set(
            (real)1.0-yy-zz, xy-zw, xz+yw, (real)0.0,
            xy+zw, (real)1.0-xx-zz, yz-xw, (real)0.0,
            xz-yw, yz+xw, (real)1.0-xx-yy, (real)0.0,
            (real)0.0, (real)0.0, (real)0.0, (real)1.0
            );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::setMatrix4(Matrix4<real>& outMat, const Vector3<real>& scale, const Vector3<real>& pos) const
{
    real xx = (real)2.0*x*x;
    real yy = (real)2.0*y*y;
    real zz = (real)2.0*z*z;
    real xy = (real)2.0*x*y;
    real zw = (real)2.0*z*w;
    real xz = (real)2.0*x*z;
    real yw = (real)2.0*y*w;
    real yz = (real)2.0*y*z;
    real xw = (real)2.0*x*w;
    outMat.set(
            (real)1.0-yy-zz, xy-zw, xz+yw, (real)0.0,
            xy+zw, (real)1.0-xx-zz, yz-xw, (real)0.0,
            xz-yw, yz+xw, (real)1.0-xx-yy, (real)0.0,
            pos.x, pos.y, pos.z, (real)1.0);
	outMat.setScale(scale);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::fromAxisAngle(const Vector3<real>& axis, real angle)
{
    // assert:  axis[] is unit length
    //
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    real halfAngle = (real)0.5*angle;
    real sinAngle = (real)sin(halfAngle);
    w = (real)cos(halfAngle);
    x = sinAngle*axis.x;
    y = sinAngle*axis.y;
    z = sinAngle*axis.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::toAxisAngle (Vector3<real>& outAxis, real& outAngle) const
{
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    real sqrLength = x*x + y*y
        + z*z;

    if (sqrLength > Math<real>::EPSILON)
    {
        outAngle = ((real)2)*Math<real>::acos(w);
        real invLength;
		if (sqrLength != (real)0)
			invLength = (real)1/sqrt(sqrLength);
		else
			invLength = (real)0;
        outAxis.x = x*invLength;
        outAxis.y = y*invLength;
        outAxis.z = z*invLength;
    }
    else
    {
        // Angle is 0 (mod 2*pi), so any axis will do.
        outAngle = (real)0;
        outAxis.set((real)1, (real)0, (real)0);
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::fromEuler(real angleX, real angleY, real angleZ, RotationOrder order)
{
	Quaternion<real> XQuat(Vector3<real>::XAXIS, angleX);
    Quaternion<real> YQuat(Vector3<real>::YAXIS, angleY);
    Quaternion<real> ZQuat(Vector3<real>::ZAXIS, angleZ);

    switch (order)
    {
    case XYZ :
        (*this) = XQuat*(YQuat*ZQuat);
        break;
    case XZY :
        (*this) = XQuat*(ZQuat*YQuat);
        break;
    case YXZ :
        (*this) = YQuat*(XQuat*ZQuat);
        break;
    case YZX :
        (*this) = YQuat*(ZQuat*XQuat);
        break;
    case ZXY :
        (*this) = ZQuat*(XQuat*YQuat);
        break;
    case ZYX :
        (*this) = ZQuat*(YQuat*XQuat);
        break;
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::fromEuler(const Euler<real>& euler, RotationOrder order)
{
	this->fromEuler(euler.x, euler.y, euler.z, order);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Euler<real> Quaternion<real>::toEuler(RotationOrder order) const
{
	Matrix3<real> mat = this->toMatrix3();
	return mat.toEuler(order);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Quaternion<real>::length () const
{
	return sqrt(w*w + x*x + y*y + z*z);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Quaternion<real>::squaredLength () const
{
	return w*w + x*x + y*y + z*z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::normalizeInPlace ()
{
	real len = length();

	if (len > Math<real>::EPSILON)
	{
		real invLength = ((real)1)/len;
		w *= invLength;
		x *= invLength;
		y *= invLength;
		z *= invLength;
	}
	else
	{
		w = (real)0;
		x = (real)0;
		y = (real)0;
		z = (real)0;
	}
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::normalize () const
{
	Quaternion<real> retQuat;
	real len = length();

	if (len > Math<real>::EPSILON)
	{
		real invLength = ((real)1)/len;
		retQuat.w = w*invLength;
		retQuat.x = x*invLength;
		retQuat.y = y*invLength;
		retQuat.z = z*invLength;
	}
	else
	{
		retQuat.w = (real)0;
		retQuat.x = (real)0;
		retQuat.y = (real)0;
		retQuat.z = (real)0;
	}
    return retQuat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::inverseInPlace ()
{
	real norm = squaredLength();
	if (norm > (real)0)
	{
		real invNorm = ((real)1)/norm;
		w = w*invNorm;
		x = -x*invNorm;
		y = -y*invNorm;
		z = -z*invNorm;
	}
	else
	{
		// Return an invalid result to flag the error.
		set((real)0, (real)0, (real)0, (real)0);
	}
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::inverse () const
{
	Quaternion inv;

	real norm = squaredLength();
	if (norm > (real)0)
	{
		real invNorm = ((real)1)/norm;
		inv.w = w*invNorm;
		inv.x = -x*invNorm;
		inv.y = -y*invNorm;
		inv.z = -z*invNorm;
	}
	else
	{
		// Return an invalid result to flag the error.
		inv.set((real)0, (real)0, (real)0, (real)0);
	}

	return inv;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::conjugateInPlace ()
{
	set(-x, -y, -z, w);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::conjugate () const
{
	return Quaternion(-x, -y, -z, w);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::exp () const
{
	// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
	// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

	Quaternion result;

	real angle = (real)sqrt(x*x + y*y + z*z);

	real sn = (real)sin(angle);
	result.w = (real)cos(angle);

	if ((real)fabs(sn) >= Math<real>::EPSILON)
	{
		real coeff = sn/angle;

		result.x = coeff*this->x;
		result.y = coeff*this->y;
		result.z = coeff*this->z;
		//result.w = coeff*this->w;
	}
	else
	{
		result.x = this->x;
		result.y = this->y;
		result.z = this->z;
		//result.w = this->w;
	}

	return result;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::log () const
{
	// If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
	// sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

	Quaternion result;
	result.w = (real)0;

	if ((real)fabs(w) < (real)1)
	{
		real angle = Math<real>::acos(w);
		real sn = (real)sin(angle);
		if ((real)fabs(sn) >= Math<real>::EPSILON)
		{
			real coeff = angle/sn;
			result.x = coeff*this->x;
			result.y = coeff*this->y;
			result.z = coeff*this->z;
			//result.w = coeff*this->w;
			return result;
		}
	}

	result.x = this->x;
	result.y = this->y;
	result.z = this->z;
	result.w = this->w;
	return result;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Quaternion<real>::dot(const Quaternion<real> & other) const
{
    return x*other.x + y*other.y + z*other.z + w*other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::slerpInPlace(const Quaternion<real> &q1, const Quaternion<real> &q2, real t, bool shortestPath)
{	
	Quaternion<real> Q2 = q2;
    if (q1.dot(q2)<(real)0.0)
    {
        Q2 = -q2;
    }

    Quaternion<real> qd = q1 - Q2;
    real lengthD = (real) sqrt (qd.dot(qd));

    Quaternion<real> qs = q1 + Q2;
    real lengthS = (real) sqrt (qs.dot(qs));

    real a = (real)2.0 * (real) atan2(lengthD, lengthS);
    real s = (real)1.0 - t;

	(*this) = 
        q1 * (sinx_over_x<real>(s * a) / sinx_over_x<real>(a) * s)  +
        Q2 * (sinx_over_x<real>(t * a) / sinx_over_x<real>(a) * t) ;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::slerp(const Quaternion<real> &q2, real t, bool shortestPath) const
{	
	Quaternion<real> Q2 = q2;
    if ((*this).dot(q2)<(real)0.0)
    {
        Q2 = -q2;
    }

    Quaternion<real> qd = (*this) - Q2;
    real lengthD = (real) sqrt (qd.dot(qd));

    Quaternion<real> qs = (*this) + Q2;
    real lengthS = (real) sqrt (qs.dot(qs));

    real a = (real)2.0 * (real) atan2(lengthD, lengthS);
    real s = (real)1.0 - t;

	return
        (*this) * (sinx_over_x<real>(s * a) / sinx_over_x<real>(a) * s)  +
        Q2 * (sinx_over_x<real>(t * a) / sinx_over_x<real>(a) * t) ;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
std::string Quaternion<real>::toString() const
{
    std::stringstream oss;
    oss << "gmath::Quaternion("<< x <<", "<< y <<", "<< z <<", "<< w <<");";

    return oss.str();
}
/*-----------------------------------------------------------------------------------------------------------------*/
