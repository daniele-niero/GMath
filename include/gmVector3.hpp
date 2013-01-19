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


/*------ Constructors ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real>::Vector3()
{
    x=(real)0.0; 
    y=(real)0.0;
    z=(real)0.0; 
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real>::Vector3(real inX, real inY, real inZ)
{
    x = inX;
    y = inY;
    z = inZ;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real>::Vector3(const Vector3<real> & other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real>::Vector3(const real* list)
{
    x = list[0];
    y = list[1];
    z = list[2];
}
/*------ Coordinate access ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Vector3<real>::operator[] (int i) const
{
    if (i>2) {
        throw out_of_range("gmath::Vector3:\n\t index out of range");
    }
    return *(&x+i);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real& Vector3<real>::operator[] (int i)
{
    if (i>2) {
        throw out_of_range("gmath::Vector3:\n\t index out of range");
    }
    return *(&x+i);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real* Vector3<real>::ptr()
{
    return &x;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
const real* Vector3<real>::ptr() const
{
    return &x;
}
/*------ Arithmetic operations ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::operator + (const Vector3<real> & other) const
{
    Vector3<real> newVector3(x+other.x, y+other.y, z+other.z);

    return newVector3;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::operator - () const
{
    Vector3<real> newVector3(-x, -y, -z);
    return newVector3;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::operator - (const Vector3<real> & other) const
{
    Vector3<real> newVector3(x-other.x, y-other.y, z-other.z);
    return newVector3;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::operator * (real scalar) const
{
    Vector3<real> newVector3(x*scalar, y*scalar, z*scalar);

    return newVector3;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::operator * (const Vector3<real> & other) const
{
    Vector3<real> newVector3(x*other.x, y*other.y, z*other.z);

    return newVector3;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::operator * (const Matrix3<real> &mat) const
{
    Vector3<real> retVec(
        mat.data[0] * this->x + mat.data[3] * this->y + mat.data[6] * this->z,
        mat.data[1] * this->x + mat.data[4] * this->y + mat.data[7] * this->z,
        mat.data[2] * this->x + mat.data[5] * this->y + mat.data[8] * this->z
        );
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::operator * (const Matrix4<real> &mat) const
{
    Vector3<real> retVec(
        mat.data[0] * this->x + mat.data[4] * this->y + mat.data[8]  * this->z + mat.data[12],
        mat.data[1] * this->x + mat.data[5] * this->y + mat.data[9]  * this->z + mat.data[13],
        mat.data[2] * this->x + mat.data[6] * this->y + mat.data[10] * this->z + mat.data[14]
        );
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::operator / (real scalar) const
{
    Vector3<real> newVector3;
    if (scalar == (real)0.0)
    {
        newVector3.x = NAN;
        newVector3.y = NAN;
        newVector3.z = NAN;
    }
    else
    {
        newVector3.x = x/scalar;
        newVector3.y = y/scalar;
        newVector3.z = z/scalar;
    }

    return newVector3;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::operator / (const Vector3<real> & other) const
{
    Vector3<real> newVector;

    if (other.x == (real)0.0)
        newVector.x = NAN;
	else
		newVector.x = x/other.x;

	if (other.y == (real)0.0)
        newVector.y = NAN;
	else
		newVector.y = y/other.y;

	if (other.z == (real)0.0)
        newVector.z = NAN;
	else
		newVector.z = z/other.z;
        
    return newVector;
}
/*------ Arithmetic updates ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::operator += (const Vector3<real> & other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::operator -= (const Vector3<real> & other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::operator *= (real scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::operator *= (const Vector3<real> & other)
{
    x*=other.x; 
	y*=other.y; 
	z*=other.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::operator *= (const Matrix3<real> &mat)
{
    this->set(
        mat.data[0] * this->x + mat.data[1] * this->y + mat.data[2] * this->z,
        mat.data[3] * this->x + mat.data[4] * this->y + mat.data[5] * this->z,
        mat.data[6] * this->x + mat.data[7] * this->y + mat.data[8] * this->z
        );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::operator *= (const Matrix4<real> &mat)
{
    this->set(
        mat.data[0] * this->x + mat.data[1] * this->y + mat.data[2]  * this->z + mat.data[12],
        mat.data[4] * this->x + mat.data[5] * this->y + mat.data[6]  * this->z + mat.data[13],
        mat.data[8] * this->x + mat.data[9] * this->y + mat.data[10] * this->z + mat.data[14]
        );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::operator /= (real scalar)
{
    if (scalar == (real)0.0)
    {
        x = NAN;
        y = NAN;
        z = NAN;
    }
    else
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::operator /= (const Vector3<real> &other)
{
    if (other.x == (real)0.0)
        x = NAN;
    else
        x /= other.x;

	if (other.y == (real)0.0)
        y = NAN;
    else
        y /= other.y;

	if (other.z == (real)0.0)
        z = NAN;
    else
        z /= other.z;
}
/*------ Comparisons ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
bool Vector3<real>::operator == (const Vector3<real> & other) const
{
    return (fabs(x-other.x) < Math<real>::EPSILON && 
            fabs(y-other.y) < Math<real>::EPSILON && 
            fabs(z-other.z) < Math<real>::EPSILON);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
bool Vector3<real>::operator != (const Vector3<real> & other) const
{
    return (fabs(x-other.x) > Math<real>::EPSILON || 
            fabs(y-other.y) > Math<real>::EPSILON || 
            fabs(z-other.z) > Math<real>::EPSILON);
}
/*------ Assignments ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::operator = (const Vector3<real> & other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}
/*------ Methods ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::set(real inX, real inY, real inZ)
{
    x = inX;
    y = inY;
    z = inZ;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::duplicate() const
{
    Vector3<real> retVec(x, y, z);
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::cross(const Vector3<real> & other) const
{
    Vector3<real> retVec(
            y*other.z - z*other.y,
            z*other.x - x*other.z,
            x*other.y - y*other.x);
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::crossInPlace(const Vector3<real> & other)
{
    real newx = y*other.z - z*other.y;
    real newy = z*other.x - x*other.z;
    real newz = x*other.y - y*other.x;
    x = newx;
    y = newy;
    z = newz;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::crossNormalize(const Vector3<real> & other) const
{
    Vector3<real> retVec(y*other.z - z*other.y,
                         z*other.x - x*other.z,
                         x*other.y - y*other.x);
    retVec.normalizeInPlace();
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::crossNormalizeInPlace(const Vector3<real> & other)
{
    crossInPlace(other);
    normalizeInPlace();
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Vector3<real>::dot(const Vector3<real> & other) const
{
    return x*other.x + y*other.y + z*other.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Vector3<real>::length() const
{
    real dot = x*x + y*y + z*z;
    return (real)sqrt( (double)dot );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Vector3<real>::squaredLength() const
{
    return x*x + y*y + z*z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Vector3<real>::squaredDistance(const Vector3<real> & other) const
{
    Vector3<real> distVec( (*this)-(other) );
    return distVec.squaredLength();
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Vector3<real>::distance(const Vector3<real> & other) const
{
    Vector3<real> distVec( (*this)-(other) );
    return distVec.length();
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::normalize() const
{
    real len = length();
    real nlen;
    if (len < Math<real>::EPSILON)
    {
        nlen = 1.0;
    }
    else
    {
        nlen = 1.0/len;
    }

    return Vector3<real>(x*nlen, y*nlen, z*nlen);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::normalizeInPlace()
{
    real len = length();

    real nlen;
    if (len < Math<real>::EPSILON)
    {
        nlen = 1.0;
    }
    else
    {
        nlen = 1.0/len;
    }

    x*=nlen;
    y*=nlen;
    z*=nlen;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Vector3<real>::angle(const Vector3<real> & other) const
{
	real ang = Math<real>::acos((double)(dot(other))); 
    return ang;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::reflect(const Vector3<real> & normal) const
{
    real dot = this->dot(normal);
    return ( normal * (2.0*dot) ) - *this;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::reflectInPlace(const Vector3<real> & normal)
{
    real dot = this->dot(normal);
    *this = ( normal * (2.0*dot) ) - *this;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::refract(const Vector3<real> & normal, real eta) const
{
    real dot = this->dot(normal);
    real k = 1.0 - eta*eta*(1.0 - dot*dot);

    Vector3<real> retVec;
    if (k >= Math<real>::EPSILON)
    {
        retVec = *this * eta;
        retVec -= normal * (eta*dot + sqrt(k));
    }
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::refractInPlace(const Vector3<real> & normal, real eta)
{
    real dot = this->dot(normal);
    real k = 1.0 - eta*eta*(1.0 - dot*dot);

    if (k >= Math<real>::EPSILON)
    {
        *this *= eta;
        *this -= normal * (eta*dot + sqrt(k));
    }
    else
    {
        this->set(real(0.0), real(0.0), real(0.0));
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::linearInterpolate(const Vector3<real> & other, real weight) const
{
	return Vector3<real>((other.x - x) * weight + x,
						 (other.y - y) * weight + y,
						 (other.z - z) * weight + z);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector3<real>::linearInterpolateInPlace(const Vector3<real> & other, real weight)
{
	x = (other.x - x) * weight + x;
	y = (other.y - y) * weight + y;
	z = (other.z - z) * weight + z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
std::string Vector3<real>::toString() const
{
    std::stringstream oss;
    oss << "gmath::Vector3(" << x << ", " << y << ", " << z << ");";

    return oss.str();
}
/*-----------------------------------------------------------------------------------------------------------------*/
