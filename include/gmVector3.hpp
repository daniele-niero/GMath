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
template <typename real>
Vector3<real>::Vector3()
{ }
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
Vector3<real> Vector3<real>::operator * (const Matrix3<real> &mat) const
{
    Vector3<real> retVec(
        mat.data[0] * this->x + mat.data[1] * this->y + mat.data[2] * this->z,
        mat.data[3] * this->x + mat.data[4] * this->y + mat.data[5] * this->z,
        mat.data[6] * this->x + mat.data[7] * this->y + mat.data[8] * this->z
        );
    return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::operator * (const Matrix4<real> &mat) const
{
    Vector3<real> retVec(
        mat.data[0] * this->x + mat.data[1] * this->y + mat.data[2]  * this->z + mat.data[12],
        mat.data[4] * this->x + mat.data[5] * this->y + mat.data[6]  * this->z + mat.data[13],
        mat.data[8] * this->x + mat.data[9] * this->y + mat.data[10] * this->z + mat.data[14]
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
        newVector3.x = NAN; //Math<real>::MIN;
        newVector3.y = NAN; //Math<real>::MIN;
        newVector3.z = NAN; //Math<real>::MIN;
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
        x = NAN; //Math<real>::MIN;
        y = NAN; //Math<real>::MIN;
        z = NAN; //Math<real>::MIN;
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
    float newx = y*other.z - z*other.y;
    float newy = z*other.x - x*other.z;
    float newz = x*other.y - y*other.x;
    x = newx;
    y = newy;
    z = newz;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Vector3<real>::crossNormalized(const Vector3<real> & other) const
{
    Vector3<real> retVec(y*other.z - z*other.y,
                         z*other.x - x*other.z,
                         x*other.y - y*other.x);
    retVec.normalizeInPlace();
    return retVec;
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
real Vector3<real>::distance(const Vector3<real> & other) const
{
    Vector3<real> distVec(operator - (other));
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
    Vector3<real> thisNorm( this->normalize() );
    Vector3<real> otherNorm( other.normalize() );
    return (real)acos((double)(thisNorm.dot(otherNorm)) / (thisNorm.length()*thisNorm.length()));
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
std::string Vector3<real>::toString() const
{
    std::stringstream oss;
    oss << "gmath::Vector3(" << x << ", " << y << ", " << z << ");" << std::endl;

    return oss.str();
}
/*-----------------------------------------------------------------------------------------------------------------*/