/*
A math library for 3D graphic.
Copyright (C) 2010 Daniele Niero

Author contact: nieroinfo@gmail.com

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
template <class TypeReal>
Vector4<TypeReal>::Vector4()
{}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector4<TypeReal>::Vector4(TypeReal inX, TypeReal inY, TypeReal inZ, TypeReal inW)
{
    x = inX;
    y = inY;
    z = inZ;
    w = inW;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector4<TypeReal>::Vector4(const Vector4<TypeReal> & other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector4<TypeReal>::Vector4(const TypeReal* list)
{
    x = list[0];
    y = list[1];
    z = list[2];
    w = list[3];
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Coordinates access ------*/
template <class TypeReal>
TypeReal Vector4<TypeReal>::operator[] (int i) const
{
    if      (i==0) { return x; }
    else if (i==1) { return y; }
    else if (i==2) { return z; }
    else if (i==3) { return w; }
    else {
        throw out_of_range("gmath::Vector4: index out of range");
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal& Vector4<TypeReal>::operator[] (int i)
{
    if      (i==0) { return x; }
    else if (i==1) { return y; }
    else if (i==2) { return z; }
    else if (i==3) { return w; }
    else {
        throw out_of_range("gmath::Vector4: index out of range");
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal* Vector4<TypeReal>::ptr()
{
	return &x;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
const TypeReal* Vector4<TypeReal>::ptr() const
{
	return &x;
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Arithmetic operations ------*/
template <class TypeReal>
Vector4<TypeReal> Vector4<TypeReal>::operator + (const Vector4<TypeReal> & other) const
{
    Vector4<TypeReal> newVector4(x+other.x, y+other.y, z+other.z, w+other.w);

    return newVector4;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector4<TypeReal> Vector4<TypeReal>::operator - (const Vector4<TypeReal> & other) const
{
    Vector4<TypeReal> newVector4(x-other.x, y-other.y, z-other.z, w-other.w);
    return newVector4;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector4<TypeReal> Vector4<TypeReal>::operator * (TypeReal scalar) const
{
    Vector4<TypeReal> newVector4(x*scalar, y*scalar, z*scalar, w*scalar);

    return newVector4;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector4<TypeReal> Vector4<TypeReal>::operator / (TypeReal scalar) const
{
    Vector4<TypeReal> newVector4;
    if (scalar == (TypeReal)0.0)
    {
        newVector4.x = Math<TypeReal>::MIN;
        newVector4.y = Math<TypeReal>::MIN;
        newVector4.z = Math<TypeReal>::MIN;
        newVector4.w = Math<TypeReal>::MIN;
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
template <class TypeReal>
void Vector4<TypeReal>::operator += (const Vector4<TypeReal> & other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector4<TypeReal>::operator -= (const Vector4<TypeReal> & other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector4<TypeReal>::operator *= (TypeReal scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector4<TypeReal>::operator /= (TypeReal scalar)
{
    if (scalar == (TypeReal)0.0)
    {
        x = NAN; //Math<TypeReal>::MIN;
        y = NAN; //Math<TypeReal>::MIN;
        z = NAN; //Math<TypeReal>::MIN;
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
template <class TypeReal>
bool Vector4<TypeReal>::operator == (const Vector4<TypeReal> & other) const
{
    return (fabs(x-other.x) < Math<TypeReal>::EPSILON && 
            fabs(y-other.y) < Math<TypeReal>::EPSILON && 
            fabs(z-other.z) < Math<TypeReal>::EPSILON &&
            fabs(w-other.w) < Math<TypeReal>::EPSILON);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
bool Vector4<TypeReal>::operator != (const Vector4<TypeReal> & other) const
{
    return (fabs(x-other.x) > Math<TypeReal>::EPSILON || 
            fabs(y-other.y) > Math<TypeReal>::EPSILON || 
            fabs(z-other.z) > Math<TypeReal>::EPSILON ||
            fabs(w-other.w) < Math<TypeReal>::EPSILON);
}
/*------ Assignments ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector4<TypeReal>::operator = (const Vector4<TypeReal> & other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.z;
}
/*------ Methods ------*/
template <class TypeReal>
void Vector4<TypeReal>::set(TypeReal inX, TypeReal inY, TypeReal inZ, TypeReal inW)
{
    x = inX;
    y = inY;
    z = inZ;
    w = inW;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector4<TypeReal> Vector4<TypeReal>::duplicate() const
{
    Vector4<TypeReal> retVec(x, y, z, w);
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal Vector4<TypeReal>::dot(const Vector4<TypeReal> & other) const
{
    return x*other.x + y*other.y + z*other.z + w*other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal Vector4<TypeReal>::length() const
{
    TypeReal dot = x*x + y*y + z*z + w*w;
    return (TypeReal)sqrt( (double)dot );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal Vector4<TypeReal>::squaredLength() const
{
    return x*x + y*y + z*z + w*w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector4<TypeReal> Vector4<TypeReal>::normalize() const
{
    TypeReal len = length();

    TypeReal nlen;
    if (len < Math<TypeReal>::EPSILON)
    {
        nlen = 1.0;
    }
    else
    {
        nlen = 1.0/len;
    }

    return Vector4<TypeReal>(x*nlen, y*nlen, z*nlen, w*nlen);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector4<TypeReal>::normalizeInPlace()
{
    TypeReal len = length();
    
    TypeReal nlen;
    if (len < Math<TypeReal>::EPSILON)
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
template <class TypeReal>
std::string Vector4<TypeReal>::toString() const
{
    char buffer[200];
    sprintf( buffer, "gmath::Vector4(%f, %f, %f, %f);", x, y, z, w );
    std::string str(buffer);
    return str;
}
/*-----------------------------------------------------------------------------------------------------------------*/

