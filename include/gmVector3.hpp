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


/*------ Constructors ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal>::Vector3()
{ }
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal>::Vector3(TypeReal inX, TypeReal inY, TypeReal inZ)
{
    x = inX;
    y = inY;
    z = inZ;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal>::Vector3(const Vector3<TypeReal> & other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal>::Vector3(const TypeReal* list)
{
    x = list[0];
    y = list[1];
    z = list[2];
}
/*------ Coordinate access ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal Vector3<TypeReal>::operator[] (int i) const
{
    if (i>2) {
        throw out_of_range("gmath::Vector3:\n\t index out of range");
    }
    return *(&x+i);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal& Vector3<TypeReal>::operator[] (int i)
{
    if (i>2) {
        throw out_of_range("gmath::Vector3:\n\t index out of range");
    }
    return *(&x+i);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal* Vector3<TypeReal>::ptr()
{
    return &x;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
const TypeReal* Vector3<TypeReal>::ptr() const
{
    return &x;
}
/*------ Arithmetic operations ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal> Vector3<TypeReal>::operator + (const Vector3<TypeReal> & other) const
{
    Vector3<TypeReal> newVector3(x+other.x, y+other.y, z+other.z);

    return newVector3;
}
/*-----------------------------------------------------------------------------------------------------------------*/

template <class TypeReal>
Vector3<TypeReal> Vector3<TypeReal>::operator - (const Vector3<TypeReal> & other) const
{
    Vector3<TypeReal> newVector3(x-other.x, y-other.y, z-other.z);
    return newVector3;
}
/*-----------------------------------------------------------------------------------------------------------------*/

template <class TypeReal>
Vector3<TypeReal> Vector3<TypeReal>::operator * (TypeReal scalar) const
{
    Vector3<TypeReal> newVector3(x*scalar, y*scalar, z*scalar);

    return newVector3;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal> Vector3<TypeReal>::operator / (TypeReal scalar) const
{
    Vector3<TypeReal> newVector3;
    if (scalar == (TypeReal)0.0)
    {
        newVector3.x = NAN; //Math<TypeReal>::MIN;
        newVector3.y = NAN; //Math<TypeReal>::MIN;
        newVector3.z = NAN; //Math<TypeReal>::MIN;
    }
    else
    {
        newVector3.x = x/scalar;
        newVector3.y = y/scalar;
        newVector3.z = z/scalar;
    }

    return newVector3;
}
/*------ Arithmetic updates ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector3<TypeReal>::operator += (const Vector3<TypeReal> & other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector3<TypeReal>::operator -= (const Vector3<TypeReal> & other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector3<TypeReal>::operator *= (TypeReal scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector3<TypeReal>::operator /= (TypeReal scalar)
{
    if (scalar == (TypeReal)0.0)
    {
        x = NAN; //Math<TypeReal>::MIN;
        y = NAN; //Math<TypeReal>::MIN;
        z = NAN; //Math<TypeReal>::MIN;
    }
    else
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }
}
/*------ Comparisons ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
bool Vector3<TypeReal>::operator == (const Vector3<TypeReal> & other) const
{
    return (fabs(x-other.x) < Math<TypeReal>::EPSILON && 
            fabs(y-other.y) < Math<TypeReal>::EPSILON && 
            fabs(z-other.z) < Math<TypeReal>::EPSILON);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
bool Vector3<TypeReal>::operator != (const Vector3<TypeReal> & other) const
{
    return (fabs(x-other.x) > Math<TypeReal>::EPSILON || 
            fabs(y-other.y) > Math<TypeReal>::EPSILON || 
            fabs(z-other.z) > Math<TypeReal>::EPSILON);
}
/*------ Assignments ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector3<TypeReal>::operator = (const Vector3<TypeReal> & other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}
/*------ Methods ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector3<TypeReal>::set(TypeReal inX, TypeReal inY, TypeReal inZ)
{
    x = inX;
    y = inY;
    z = inZ;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal> Vector3<TypeReal>::duplicate() const
{
    Vector3<TypeReal> retVec(x, y, z);
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal> Vector3<TypeReal>::cross(const Vector3<TypeReal> & other) const
{
    Vector3<TypeReal> retVec(
            y*other.z - z*other.y,
            z*other.x - x*other.z,
            x*other.y - y*other.x);
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector3<TypeReal>::crossInPlace(const Vector3<TypeReal> & other)
{
    float newx = y*other.z - z*other.y;
    float newy = z*other.x - x*other.z;
    float newz = x*other.y - y*other.x;
    x = newx;
    y = newy;
    z = newz;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal> Vector3<TypeReal>::crossNormalized(const Vector3<TypeReal> & other) const
{
    Vector3<TypeReal> retVec(y*other.z - z*other.y,
                         z*other.x - x*other.z,
                         x*other.y - y*other.x);
    retVec.normalizeInPlace();
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal Vector3<TypeReal>::dot(const Vector3<TypeReal> & other) const
{
    return x*other.x + y*other.y + z*other.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal Vector3<TypeReal>::length() const
{
    TypeReal dot = x*x + y*y + z*z;
    return (TypeReal)sqrt( (double)dot );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal Vector3<TypeReal>::squaredLength() const
{
    return x*x + y*y + z*z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal Vector3<TypeReal>::distance(const Vector3<TypeReal> & other) const
{
    Vector3<TypeReal> distVec(operator - (other));
    return distVec.length();
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal> Vector3<TypeReal>::normalize() const
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

    return Vector3<TypeReal>(x*nlen, y*nlen, z*nlen);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector3<TypeReal>::normalizeInPlace()
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

    x*=nlen;
    y*=nlen;
    z*=nlen;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal Vector3<TypeReal>::angle(const Vector3<TypeReal> & other) const
{
    Vector3<TypeReal> thisNorm( this->normalize() );
    Vector3<TypeReal> otherNorm( other.normalize() );
    return (TypeReal)acos((double)(thisNorm.dot(otherNorm)) / (thisNorm.length()*thisNorm.length()));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal> Vector3<TypeReal>::reflect(const Vector3<TypeReal> & normal) const
{
    TypeReal dot = this->dot(normal);
    return ( normal * (2.0*dot) ) - *this;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector3<TypeReal>::reflectInPlace(const Vector3<TypeReal> & normal)
{
    TypeReal dot = this->dot(normal);
    *this = ( normal * (2.0*dot) ) - *this;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal> Vector3<TypeReal>::refract(const Vector3<TypeReal> & normal, TypeReal eta) const
{
    TypeReal dot = this->dot(normal);
    TypeReal k = 1.0 - eta*eta*(1.0 - dot*dot);

    Vector3<TypeReal> retVec;
    if (k >= Math<TypeReal>::EPSILON)
    {
        retVec = *this * eta;
        retVec -= normal * (eta*dot + sqrt(k));
    }
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Vector3<TypeReal>::refractInPlace(const Vector3<TypeReal> & normal, TypeReal eta)
{
    TypeReal dot = this->dot(normal);
    TypeReal k = 1.0 - eta*eta*(1.0 - dot*dot);

    if (k >= Math<TypeReal>::EPSILON)
    {
        *this *= eta;
        *this -= normal * (eta*dot + sqrt(k));
    }
    else
    {
        this->set(TypeReal(0.0), TypeReal(0.0), TypeReal(0.0));
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
std::string Vector3<TypeReal>::toString() const
{
    std::stringstream oss;
    oss << "gmath::Vector3(" << x << ", " << y << ", " << z << ");" << std::endl;

    return oss.str();
}
/*-----------------------------------------------------------------------------------------------------------------*/