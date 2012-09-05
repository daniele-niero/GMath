/*
A math library for 3D graphic.
Copyright (C) 2010-2012 Daniele Niero

Author contact: daniele . niero @ gmail . com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

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
Vector4<real> Vector4<real>::duplicate() const
{
    Vector4<real> retVec(x, y, z, w);
    return retVec;
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

