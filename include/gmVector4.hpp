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

/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Constructors ------*/
template <typename real>
Vector4<real>::Vector4()
{
    x=(real)0.0;
    y=(real)0.0;
    z=(real)0.0;
    w=(real)0.0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector4<real>::Vector4(real inX, real inY, real inZ, real inW)
{
    x = inX;
    y = inY;
    z = inZ;
    w = inW;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector4<real>::Vector4(const Vector4<real> & other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector4<real>::Vector4(const real* list)
{
    x = list[0];
    y = list[1];
    z = list[2];
    w = list[3];
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Coordinates access ------*/
template <typename real>
real Vector4<real>::operator[] (int i) const
{
    if (i>3){
        throw out_of_range("gmath::Vector4: index out of range");
    }
    return *(&x+i);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real& Vector4<real>::operator[] (int i)
{
    if (i==0){
        throw out_of_range("gmath::Vector4: index out of range");
    }
    return *(&x+i);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real* Vector4<real>::ptr()
{
	return &x;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
const real* Vector4<real>::ptr() const
{
	return &x;
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Arithmetic operations ------*/
template <typename real>
Vector4<real> Vector4<real>::operator + (const Vector4<real> & other) const
{
    Vector4<real> newVector4(x+other.x, y+other.y, z+other.z, w+other.w);

    return newVector4;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector4<real> Vector4<real>::operator - (const Vector4<real> & other) const
{
    Vector4<real> newVector4(x-other.x, y-other.y, z-other.z, w-other.w);
    return newVector4;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector4<real> Vector4<real>::operator - () const
{
    Vector4<real> newVector4(-x, -y, -z, -w);
    return newVector4;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector4<real> Vector4<real>::operator * (real scalar) const
{
    Vector4<real> newVector4(x*scalar, y*scalar, z*scalar, w*scalar);

    return newVector4;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector4<real> Vector4<real>::operator / (real scalar) const
{
    Vector4<real> newVector4;
    if (scalar == (real)0.0)
    {
        newVector4.x = NAN;
        newVector4.y = NAN;
        newVector4.z = NAN;
        newVector4.w = NAN;
    }
    else
    {
        newVector4.x = x/scalar;
        newVector4.y = y/scalar;
        newVector4.z = z/scalar;
        newVector4.w = w/scalar;
    }

    return newVector4;
}
/*------ Arithmetic updates ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector4<real>::operator += (const Vector4<real> & other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector4<real>::operator -= (const Vector4<real> & other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector4<real>::operator *= (real scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector4<real>::operator /= (real scalar)
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
bool Vector4<real>::operator == (const Vector4<real> & other) const
{
    return (fabs(x-other.x) < Math<real>::EPSILON && 
            fabs(y-other.y) < Math<real>::EPSILON && 
            fabs(z-other.z) < Math<real>::EPSILON &&
            fabs(w-other.w) < Math<real>::EPSILON);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
bool Vector4<real>::operator != (const Vector4<real> & other) const
{
    return (fabs(x-other.x) > Math<real>::EPSILON || 
            fabs(y-other.y) > Math<real>::EPSILON || 
            fabs(z-other.z) > Math<real>::EPSILON ||
            fabs(w-other.w) < Math<real>::EPSILON);
}
/*------ Assignments ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector4<real>::operator = (const Vector4<real> & other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.z;
}
/*------ Methods ------*/
template <typename real>
void Vector4<real>::set(real inX, real inY, real inZ, real inW)
{
    x = inX;
    y = inY;
    z = inZ;
    w = inW;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Vector4<real>::dot(const Vector4<real> & other) const
{
    return x*other.x + y*other.y + z*other.z + w*other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Vector4<real>::length() const
{
    real dot = x*x + y*y + z*z + w*w;
    return (real)sqrt( (double)dot );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Vector4<real>::squaredLength() const
{
    return x*x + y*y + z*z + w*w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector4<real> Vector4<real>::normalize() const
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

    return Vector4<real>(x*nlen, y*nlen, z*nlen, w*nlen);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Vector4<real>::normalizeInPlace()
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

    x *= nlen;
    y *= nlen;
    z *= nlen;
    w *= nlen;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
std::string Vector4<real>::toString() const
{
    std::stringstream oss;
    oss << "gmath::Vector4(" << x << ", " << y << ", " << z << ", " << w << ");";

    return oss.str();
}
/*-----------------------------------------------------------------------------------------------------------------*/

