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
        y = NAN; //Math<real>::MIN;
        z = NAN; //Math<real>::MIN;
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
    w = other.z;
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
Quaternion<real> Quaternion<real>::inverse() const
{
    Quaternion<real> returnQuat;
    returnQuat.inverseInPlace();
    return returnQuat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Quaternion<real>::inverseInPlace()
{
    real qdot = this->dot(*this);
    w /= qdot;
    x = -x / qdot;
    y = -y / qdot;
    z = -z / qdot;
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
        float* quat[3] = { &x, &y, &z };
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
Quaternion<real> Quaternion<real>::duplicate() const
{
    Quaternion<real> retQuat(x, y, z, w);
    return retQuat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Quaternion<real>::dot(const Quaternion<real> & other) const
{
    return x*other.x + y*other.y + z*other.z + w*other.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Quaternion<real>::slerp(const Quaternion<real> &q1, const Quaternion<real> &q2, real t, bool shortestPath)
{
    if (q1.dot(q2)<(real)0.0)
    {
        q2 = q2.inverse();
    }

    Quaternion<real> qd = q1 - q2;
    real lengthD = (real) sqrt (qd.dot(qd));

    Quaternion<real> qs = q1 + q2;
    real lengthS = (real) sqrt (qs.dot(qs));

    real a = (real)2.0 * (real) atan2(lengthD, lengthS);
    real s = (real)1.0 - t;

    Quaternion<real> q = 
        sinx_over_x<real>(s * a) / sinx_over_x<real>(a) * s * q1 +
        sinx_over_x<real>(t * a) / sinx_over_x<real>(a) * t * q2 ;

    return q;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
std::string Quaternion<real>::toString() const
{
    std::stringstream oss;
    oss << "gmath::Quaternion("<< x <<", "<< y <<", "<< z <<", "<< w <<");"<< std::endl;

    return oss.str();
}
/*-----------------------------------------------------------------------------------------------------------------*/



