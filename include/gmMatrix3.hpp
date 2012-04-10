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
/*------ constructors ------*/
template <class TypeReal>
Matrix3<TypeReal>::Matrix3()
{}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal>::Matrix3(
    TypeReal xx, TypeReal xy, TypeReal xz,
    TypeReal yx, TypeReal yy, TypeReal yz,
    TypeReal zx, TypeReal zy, TypeReal zz)
{
    set(xx, xy, xz, yx, yy, yz, zx, zy, zz);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal>::Matrix3(const Matrix3<TypeReal> & other)
{
    memcpy(data, other.data, 9*sizeof(TypeReal));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal>::Matrix3(
        const Vector3<TypeReal> &axisX,
        const Vector3<TypeReal> &axisY,
        const Vector3<TypeReal> &axisZ)
{
    memcpy(&data[0], axisX.ptr(), 3*sizeof(TypeReal));
    memcpy(&data[3], axisY.ptr(), 3*sizeof(TypeReal));
    memcpy(&data[6], axisZ.ptr(), 3*sizeof(TypeReal));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal>::Matrix3(const TypeReal* list)
{
    memcpy(data, list, 9*sizeof(TypeReal));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal* Matrix3<TypeReal>::ptr()
{
    return &data[0];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
const TypeReal* Matrix3<TypeReal>::ptr() const
{
    return &data[0];
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Coordinates access ------*/
template <class TypeReal>
TypeReal Matrix3<TypeReal>::operator[] (int i) const
{
    if (i>=0 && i<9)
    {
        return this->data[i];
    }
    else {
        throw out_of_range("gmath::Matrix3: index out of range");
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal& Matrix3<TypeReal>::operator[] (int i)
{
    if (i>=0 && i<9)
    {
        return this->data[i];
    }
    else {
        throw out_of_range("gmath::Vector4: index out of range");
    }
}
/*------ Arithmetic operations ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::operator + (TypeReal value) const
{
    Matrix3<TypeReal> retMatrix(
        data[0]+value, data[1]+value, data[2]+value,
        data[3]+value, data[4]+value, data[5]+value,
        data[6]+value, data[7]+value, data[8]+value
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::operator + (const Matrix3<TypeReal> &other) const
{
    
    const TypeReal* b = other.ptr();
    Matrix3<TypeReal> retMatrix(
        data[0]+b[0], data[1]+b[1], data[2]+b[2],
        data[3]+b[3], data[4]+b[4], data[5]+b[5],
        data[6]+b[6], data[7]+b[7], data[8]+b[8]
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::operator - (TypeReal value) const
{
    Matrix3<TypeReal> retMatrix(
        data[0]-value, data[1]-value, data[2]-value,
        data[3]-value, data[4]-value, data[5]-value,
        data[6]-value, data[7]-value, data[8]-value
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::operator - (const Matrix3<TypeReal> &other) const
{
    
    const TypeReal* b = other.ptr();
    Matrix3<TypeReal> retMatrix(
        data[0]-b[0], data[1]-b[1], data[2]-b[2],
        data[3]-b[3], data[4]-b[4], data[5]-b[5],
        data[6]-b[6], data[7]-b[7], data[8]-b[8]
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::operator / (TypeReal value) const
{
    Matrix3<TypeReal> retMatrix(
        data[0]/value, data[1]/value, data[2]/value,
        data[3]/value, data[4]/value, data[5]/value,
        data[6]/value, data[7]/value, data[8]/value
        );

    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::operator * (TypeReal value) const
{
    Matrix3<TypeReal> retMatrix(
        data[0]*value, data[1]*value, data[2]*value,
        data[3]*value, data[4]*value, data[5]*value,
        data[6]*value, data[7]*value, data[8]*value
        );

    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::operator * (const Matrix3<TypeReal> &other) const
{
    const TypeReal* b = other.ptr();
    Matrix3<TypeReal> retMatrix(
        data[0]*b[0] + data[1]*b[3] + data[2]*b[6],
        data[0]*b[1] + data[1]*b[4] + data[2]*b[7],
        data[0]*b[2] + data[1]*b[5] + data[2]*b[8],

        data[3]*b[0] + data[4]*b[3] + data[5]*b[6],
        data[3]*b[1] + data[4]*b[4] + data[5]*b[7],
        data[3]*b[2] + data[4]*b[5] + data[5]*b[8],

        data[6]*b[0] + data[7]*b[3] + data[8]*b[6],
        data[6]*b[1] + data[7]*b[4] + data[8]*b[7],
        data[6]*b[2] + data[7]*b[5] + data[8]*b[8]
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal> Matrix3<TypeReal>::operator * (const Vector3<TypeReal> &vector) const
{
    Vector3<TypeReal> retVec(
        data[0]*vector.x + data[1]*vector.y + data[2]*vector.z,
        data[3]*vector.x + data[4]*vector.y + data[5]*vector.z,
        data[6]*vector.x + data[7]*vector.y + data[8]*vector.z
        );
    return retVec;
}
/*------ Arithmetic updates ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::operator += (TypeReal value)
{
    data[0]+=value; data[1]+=value; data[2]+=value;
    data[3]+=value; data[4]+=value; data[5]+=value;
    data[6]+=value; data[7]+=value; data[8]+=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::operator += (const Matrix3<TypeReal> &other)
{
    TypeReal* a = ptr();
    const TypeReal* b = other.ptr();
    data[0]+=b[0]; data[1]+=b[1]; data[2]+=b[2];
    data[3]+=b[3]; data[4]+=b[4]; data[5]+=b[5];
    data[6]+=b[6]; data[7]+=b[7]; data[8]+=b[8];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::operator -= (TypeReal value)
{
    data[0]-=value; data[1]-=value; data[2]-=value;
    data[3]-=value; data[4]-=value; data[5]-=value;
    data[6]-=value; data[7]-=value; data[8]-=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::operator -= (const Matrix3<TypeReal> &other)
{
    TypeReal* a = ptr();
    const TypeReal* b = other.ptr();

    data[0]-=b[0]; data[1]-=b[1]; data[2]-=b[2];
    data[3]-=b[3]; data[4]-=b[4]; data[5]-=b[5];
    data[6]-=b[6]; data[7]-=b[7]; data[8]-=b[8];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::operator /= (TypeReal value)
{
    data[0]/=value; data[1]/=value; data[2]/=value;
    data[3]/=value; data[4]/=value; data[5]/=value;
    data[6]/=value; data[7]/=value; data[8]/=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::operator *= (TypeReal value)
{
    data[0]*=value; data[1]*=value; data[2]*=value;
    data[3]*=value; data[4]*=value; data[5]*=value;
    data[6]*=value; data[7]*=value; data[8]*=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::operator *= (const Matrix3<TypeReal> &other)
{
    const TypeReal* a = &data[0];
    const TypeReal* b = &other.data[0];
    TypeReal c[9];

    c[0] = data[0]*b[0] + data[1]*b[3] + data[2]*b[6];
    c[1] = data[0]*b[1] + data[1]*b[4] + data[2]*b[7];
    c[2] = data[0]*b[2] + data[1]*b[5] + data[2]*b[8];
    c[3] = data[3]*b[0] + data[4]*b[3] + data[5]*b[6];
    c[4] = data[3]*b[1] + data[4]*b[4] + data[5]*b[7];
    c[5] = data[3]*b[2] + data[4]*b[5] + data[5]*b[8];
    c[6] = data[6]*b[0] + data[7]*b[3] + data[8]*b[6];
    c[7] = data[6]*b[1] + data[7]*b[4] + data[8]*b[7];
    c[8] = data[6]*b[2] + data[7]*b[5] + data[8]*b[8];

    memcpy(data, c, 9*sizeof(TypeReal));
}
/*------ Comparisons ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
bool Matrix3<TypeReal>::operator == (const Matrix3<TypeReal> &other) const
{
    const TypeReal* b = &other.data[0];
    TypeReal e = Math<TypeReal>::EPSILON;
    return (fabs(data[0]-b[0])<e && fabs(data[1]-b[1])<e && fabs(data[2]-b[2])<e &&
            fabs(data[3]-b[3])<e && fabs(data[4]-b[4])<e && fabs(data[5]-b[5])<e &&
            fabs(data[6]-b[6])<e && fabs(data[7]-b[7])<e && fabs(data[8]-b[8])<e);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
bool Matrix3<TypeReal>::operator != (const Matrix3<TypeReal> &other) const
{
    const TypeReal* b = &other.data[0];
    TypeReal e = Math<TypeReal>::EPSILON;
    return (fabs(data[0]-b[0])>e || fabs(data[1]-b[1])>e || fabs(data[2]-b[3])>e ||
            fabs(data[3]-b[3])>e || fabs(data[0]-b[0])>e || fabs(data[0]-b[0])>e ||
            fabs(data[0]-b[0])>e || fabs(data[0]-b[0])>e || fabs(data[0]-b[0])>e);
}
/*------ Assignment ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::operator = (const Matrix3<TypeReal> &other)
{
    memcpy(data, other.data, 9*sizeof(TypeReal));
}
/*------ methods ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::setToIdentity()
{
    memcpy(data, Matrix3<TypeReal>::IDENTITY.data, 9*sizeof(TypeReal));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::set(
    TypeReal xx, TypeReal xy, TypeReal xz,
    TypeReal yx, TypeReal yy, TypeReal yz,
    TypeReal zx, TypeReal zy, TypeReal zz)
{
    data[0]=xx; data[1]=xy; data[2]=xz;
    data[3]=yx; data[4]=yy; data[5]=yz;
    data[6]=zx; data[7]=zy; data[8]=zz;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::transpose() const
{
    return Matrix3<TypeReal>(
            data[0], data[3], data[6],
            data[1], data[4], data[7],
            data[2], data[5], data[8] );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::transposeInPlace()
{
    TypeReal newData[9] = {
            data[0], data[3], data[6],
            data[1], data[4], data[7],
            data[2], data[5], data[8] };
    memcpy(data, newData, 9*sizeof(TypeReal));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
TypeReal Matrix3<TypeReal>::determinant() const
{
    TypeReal det;
    det = data[0] * ( data[4]*data[8] - data[7]*data[5] )
        - data[1] * ( data[3]*data[8] - data[6]*data[5] )
        + data[2] * ( data[3]*data[7] - data[6]*data[4] );
    return det;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::inverse() const
{
    Matrix3<TypeReal> retMatrix;
    TypeReal invDet = (TypeReal)1/determinant();

    if ( invDet < Math<TypeReal>::EPSILON )
    {
        retMatrix = *this;
        retMatrix.setToIdentity();
    }
    else
    {
        retMatrix.data[0] =   data[4]*data[8] - data[5]*data[7]  / invDet;
        retMatrix.data[1] = -(data[1]*data[8] - data[7]*data[2]) / invDet;
        retMatrix.data[2] =   data[1]*data[5] - data[4]*data[2]  / invDet;

        retMatrix.data[3] = -(data[3]*data[8] - data[5]*data[6]) / invDet;
        retMatrix.data[4] =   data[0]*data[8] - data[6]*data[2]  / invDet;
        retMatrix.data[5] = -(data[0]*data[5] - data[3]*data[2]) / invDet;

        retMatrix.data[6] =   data[3]*data[7] - data[6]*data[4]  / invDet;
        retMatrix.data[7] = -(data[0]*data[7] - data[6]*data[1]) / invDet;
        retMatrix.data[8] =   data[0]*data[4] - data[1]*data[3]  / invDet;
    }

    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::inverseInPlace()
{
    TypeReal m[9];
    TypeReal invDet = (TypeReal)1/determinant();

    if ( invDet < Math<TypeReal>::EPSILON )
    {
        this->setToIdentity();
    }
    else
    {
        m[0] =   data[4]*data[8] - data[5]*data[7]  / invDet;
        m[1] = -(data[1]*data[8] - data[7]*data[2]) / invDet;
        m[2] =   data[1]*data[5] - data[4]*data[2]  / invDet;

        m[3] = -(data[3]*data[8] - data[5]*data[6]) / invDet;
        m[4] =   data[0]*data[8] - data[6]*data[2]  / invDet;
        m[5] = -(data[0]*data[5] - data[3]*data[2]) / invDet;

        m[6] =   data[3]*data[7] - data[6]*data[4]  / invDet;
        m[7] = -(data[0]*data[7] - data[6]*data[1]) / invDet;
        m[8] =   data[0]*data[4] - data[1]*data[3]  / invDet;

        memcpy(data, m, 9*sizeof(TypeReal));
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::orthogonal() const
{
    Matrix3<TypeReal> m;
    m.orthogonalInPlace();
    return m;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::orthogonalInPlace() //primaryAxis, secondaryAxis)
{
    // Code take it from WildMagig 5  -  www.geometrictools.com  -  here the matrix is transpose
    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.



    // Compute q0. length xAxis
    TypeReal invLength = (TypeReal)1 / sqrt(data[0]*data[0] +
        data[1]*data[1] + data[2]*data[2]);

    data[0] *= invLength;
    data[1] *= invLength;
    data[2] *= invLength;

    // Compute q1.
    TypeReal dot0 = data[0]*data[3] + data[1]*data[4] +
        data[2]*data[5];

    data[3] -= dot0*data[0];
    data[4] -= dot0*data[1];
    data[5] -= dot0*data[2];

    invLength = (TypeReal)1 / sqrt(data[3]*data[3] +
        data[4]*data[4] + data[5]*data[5]);

    data[3] *= invLength;
    data[4] *= invLength;
    data[5] *= invLength;

    // compute q2
    TypeReal dot1 = data[3]*data[6] + data[4]*data[7] +
        data[5]*data[8];

    dot0 = data[0]*data[6] + data[1]*data[7] +
        data[2]*data[8];

    data[6] -= dot0*data[0] + dot1*data[3];
    data[7] -= dot0*data[1] + dot1*data[4];
    data[8] -= dot0*data[2] + dot1*data[5];

    invLength = (TypeReal)1 / sqrt(data[6]*data[6] +
        data[7]*data[7] + data[8]*data[8]);

    data[6] *= invLength;
    data[7] *= invLength;
    data[8] *= invLength;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Vector3<TypeReal> Matrix3<TypeReal>::getScale() const
{
    Vector3<TypeReal> x(data[0], data[1], data[2]);
    Vector3<TypeReal> y(data[3], data[4], data[5]);
    Vector3<TypeReal> z(data[6], data[7], data[8]);

    return Vector3<TypeReal>(x.length(), y.length(), z.length());
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::addScale(const Vector3<TypeReal> &scale)
{
    Matrix3<TypeReal> mat(
        data[0]+scale.x, data[1]+scale.x, data[2]+scale.x,
        data[3]+scale.y, data[4]+scale.y, data[5]+scale.y,
        data[6]+scale.z, data[7]+scale.z, data[8]+scale.z
        );
    return mat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::addScale(TypeReal sX, TypeReal sY, TypeReal sZ)
{
    Matrix3<TypeReal> mat(
        data[0]+sX, data[1]+sX, data[2]+sX,
        data[3]+sY, data[4]+sY, data[5]+sY,
        data[6]+sZ, data[7]+sZ, data[8]+sZ
        );
    return mat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::addScaleInPlace(const Vector3<TypeReal> &scale)
{
    data[0]+=scale.x; data[1]+=scale.x; data[2]+=scale.x;
    data[3]+=scale.y; data[4]+=scale.y; data[5]+=scale.y;
    data[6]+=scale.z; data[7]+=scale.z; data[8]+=scale.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::addScaleInPlace(TypeReal sX, TypeReal sY, TypeReal sZ)
{
    data[0]+=sX; data[1]+=sX; data[2]+=sX;
    data[3]+=sY; data[4]+=sY; data[5]+=sY;
    data[6]+=sZ; data[7]+=sZ; data[8]+=sZ;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::setScale(const Vector3<TypeReal> &scale)
{
    Vector3<TypeReal> x(data[0], data[1], data[2]);
    Vector3<TypeReal> y(data[3], data[4], data[5]);
    Vector3<TypeReal> z(data[6], data[7], data[8]);
    x.normalizeInPlace();
    y.normalizeInPlace();
    z.normalizeInPlace();
    x *= scale.x;
    y *= scale.y;
    z *= scale.z;

    return Matrix3<TypeReal>(
            x.x, x.y, x.z,
            y.x, y.y, y.z,
            z.x, z.y, z.z );
}
/*-----------------------------------------------------------------------------------------------------------------*//*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::setScale(TypeReal sX, TypeReal sY, TypeReal sZ)
{
    Vector3<TypeReal> x(data[0], data[1], data[2]);
    Vector3<TypeReal> y(data[3], data[4], data[5]);
    Vector3<TypeReal> z(data[6], data[7], data[8]);
    x.normalizeInPlace();
    y.normalizeInPlace();
    z.normalizeInPlace();
    x *= sX;
    y *= sY;
    z *= sZ;

    return Matrix3<TypeReal>(
            x.x, x.y, x.z,
            y.x, y.y, y.z,
            z.x, z.y, z.z );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::setScaleInPlace(const Vector3<TypeReal> &scale)
{
    Vector3<TypeReal> x(data[0], data[1], data[2]);
    Vector3<TypeReal> y(data[3], data[4], data[5]);
    Vector3<TypeReal> z(data[6], data[7], data[8]);
    x.normalizeInPlace();
    y.normalizeInPlace();
    z.normalizeInPlace();
    x *= scale.x;
    y *= scale.y;
    z *= scale.z;

    data[0]=x.x; data[1]=x.y; data[2]=x.z;
    data[3]=y.x; data[4]=y.y; data[5]=y.z;
    data[6]=z.x; data[7]=z.y; data[8]=z.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::setScaleInPlace(TypeReal sX, TypeReal sY, TypeReal sZ)
{
    Vector3<TypeReal> x(data[0], data[1], data[2]);
    Vector3<TypeReal> y(data[3], data[4], data[5]);
    Vector3<TypeReal> z(data[6], data[7], data[8]);
    x.normalizeInPlace();
    y.normalizeInPlace();
    z.normalizeInPlace();
    x *= sX;
    y *= sY;
    z *= sZ;

    data[0]=x.x; data[1]=x.y; data[2]=x.z;
    data[3]=y.x; data[4]=y.y; data[5]=y.z;
    data[6]=z.x; data[7]=z.y; data[8]=z.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::createScale(const Vector3<TypeReal> &scale)
{
    return Matrix3<TypeReal>(scale.x, (TypeReal)0.0, (TypeReal)0.0,
                         (TypeReal)0.0, scale.y, (TypeReal)0.0,
                         (TypeReal)0.0, (TypeReal)0.0, scale.z);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::createScale(TypeReal sX, TypeReal sY, TypeReal sZ)
{
    return Matrix3<TypeReal>(sX, (TypeReal)0.0, (TypeReal)0.0,
                         (TypeReal)0.0, sY, (TypeReal)0.0,
                         (TypeReal)0.0, (TypeReal)0.0, sZ);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::setFromEuler(const TypeReal& angleX, const TypeReal& angleY, const TypeReal& angleZ, RotationOrder order)
{
    TypeReal cx, sx, cy, sy, cz, sz;

    cx = cos(angleX);
    sx = sin(angleX);
    cy = cos(angleY);
    sy = sin(angleY);
    cz = cos(angleZ);
    sz = sin(angleZ);


    Matrix3<TypeReal> XMat(
        1.0, 0.0, 0.0,
        0.0,  cx,  sx,
        0.0, -sx,  cx);

    Matrix3<TypeReal> YMat(
         cy, 0.0, -sy,
        0.0, 1.0, 0.0,
         sy, 0.0,  cy);

    Matrix3<TypeReal> ZMat(
         cz,  sz, 0.0,
        -sz,  cz, 0.0,
        0.0, 0.0, 1.0);

    switch (order)
    {
    case XYZ :
        *this = XMat*(YMat*ZMat);
        break;
    case XZY :
        *this = XMat*(ZMat*YMat);
        break;
    case YXZ :
        *this = YMat*(XMat*ZMat);
        break;
    case YZX :
        *this = YMat*(ZMat*XMat);
        break;
    case ZXY :
        *this = ZMat*(XMat*YMat);
        break;
    case ZYX :
        *this = ZMat*(YMat*XMat);
        break;
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
void Matrix3<TypeReal>::setFromEuler(const Euler<TypeReal> &rotation, RotationOrder order)
{
    setFromEuler(rotation.x, rotation.y, rotation.z, order);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::createFromEuler(const Euler<TypeReal> &rotation, RotationOrder order)
{
    Matrix3<TypeReal> newMat;
    newMat.setFromEuler(rotation.x, rotation.y, rotation.z, order);
    return newMat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::createFromEuler(const TypeReal& angleX, const TypeReal& angleY, const TypeReal& angleZ, RotationOrder order)
{
    Matrix3<TypeReal> newMat;
    newMat.setFromEuler(angleX, angleY, angleZ, order);
    return newMat;
}
/*-----------------------------------------------------------------------------------------------------------------*//*-----------------------------------------------------------------------------------------------------------------*/
template<class TypeReal>
Euler<TypeReal> Matrix3<TypeReal>::toEuler(RotationOrder order)
{
    Euler<TypeReal> retAngles;
    toEuler(retAngles, order);
    return retAngles;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<class TypeReal>
bool Matrix3<TypeReal>::toEuler(Euler<TypeReal>& euler, RotationOrder order)
{
    TypeReal C;
    switch (order)
    {
    case XYZ :
        euler.y = Math<TypeReal>::asin(-data[2]);
        C = (TypeReal)cos((double)euler.y);
        if ( C<(TypeReal)1 || C>(TypeReal)-1)
        {
            euler.x = atan2(data[5], data[8]);
            euler.z = atan2(data[1], data[0]);
            return true;
        }
        else
        {
            euler.z = (TypeReal)0;
            euler.x = atan2(-data[5], data[8]);
            return false;
        }

    case XZY :
        euler.z = Math<TypeReal>::asin(data[1]);
        C = (TypeReal)cos((double)euler.z);
        if ( C<(TypeReal)1 || C>(TypeReal)-1)
        {
            euler.x = atan2(-data[7], data[4]);
            euler.y = atan2(-data[2], data[0]);
            return true;
        }
        else
        {
            // WARNING.  The solution is not unique.  Choosing y_angle = 0.
            euler.x = atan2(data[6] ,data[8]);
            euler.y = (TypeReal)0;
            return false;
        }

    case YXZ :
        euler.x = Math<TypeReal>::asin(data[5]);
        C = (TypeReal)cos((double)euler.x);
        if ( C<(TypeReal)1 || C>(TypeReal)-1)
        {
            euler.y = atan2(-data[2], data[8]);
            euler.z = atan2(-data[3], data[4]);
            return true;
        }
        else
        {
            // WARNING.  The solution is not unique.  Choosing z_angle = 0.
            euler.y = atan2(data[1], data[0]);
            euler.z = (TypeReal)0;
            return false;
        }

    case YZX :
        euler.z = Math<TypeReal>::asin(-data[3]);
        C = (TypeReal)cos((double)euler.z);
        if ( C<(TypeReal)1 || C>(TypeReal)-1)
        {
            euler.y = atan2(data[6], data[0]);
            euler.x = atan2(data[5], data[4]);
            return true;
        }
        else
        {
            // WARNING.  The solution is not unique.  Choosing x_angle = 0.
            euler.y = atan2(data[7], data[8]);
            euler.x = (TypeReal)0;
            return false;
        }

    case ZXY :
        euler.x = Math<TypeReal>::asin(-data[7]);
        C = (TypeReal)cos((double)euler.x);
        if ( C<(TypeReal)1 || C>(TypeReal)-1)
        {
            euler.z = atan2(data[1], data[4]);
            euler.y = atan2(data[6], data[8]);
            return true;
        }
        else
        {
            // WARNING.  The solution is not unique.  Choosing y_angle = 0.
            euler.z = atan2(data[2], data[0]);
            euler.y = (TypeReal)0;
            return false;
        }

    case ZYX :
        euler.y = Math<TypeReal>::asin(data[6]);
        C = (TypeReal)cos((double)euler.y);
        if ( C<(TypeReal)1 || C>(TypeReal)-1)
        {
            euler.z = atan2(-data[3], data[0]);
            euler.x = atan2(-data[7], data[8]);
            return true;
        }
        else
        {
            // WARNING.  The solution is not unique.  Choosing x_angle = 0.
            euler.z = atan2(-data[1], data[2]);
            euler.x = (TypeReal)0;
            return false;
        }
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<class TypeReal>
void Matrix3<TypeReal>::setFromVectorToVector(const Vector3<TypeReal> &fromVec, const Vector3<TypeReal> &toVec)
{
    Vector3<TypeReal> x, u, v;
    TypeReal e = fromVec.dot(toVec);
    TypeReal f = fabs(e);

    if (f > 1.0-Math<TypeReal>::EPSILON) // "from" and "to" vectors parallel or almost parallel
    {
        TypeReal fx = fabs(fromVec.x);
        TypeReal fy = fabs(fromVec.y);
        TypeReal fz = fabs(fromVec.z);

        if (fx<fy)
        {
            if (fx<fz) {
                x.set((TypeReal)1.0, (TypeReal)0.0, (TypeReal)0.0);
            }
            else {
                x.set((TypeReal)0.0, (TypeReal)0.0, (TypeReal)1.0);
            }
        }
        else
        {
            if (fy<fz) {
                x.set((TypeReal)0.0, (TypeReal)1.0, (TypeReal)0.0);
            }
            else {
                x.set((TypeReal)0.0, (TypeReal)0.0, (TypeReal)1.0);
            }
        }

        u = x - fromVec;
        v = x - toVec;

        TypeReal c1 = (TypeReal)2.0/(u.dot(u));
        TypeReal c2 = (TypeReal)2.0/(v.dot(v));
        TypeReal c3 = v.dot(u*(c1*c2));

        TypeReal uvals[3];
        TypeReal vvals[3];
        uvals[0]=u.x; uvals[1]=u.y; uvals[2]=u.z;
        vvals[0]=v.x; vvals[1]=v.y; vvals[2]=v.z;
        for (unsigned int i=0; i<3; i++)
        {
            for (unsigned int j=0; j<3; j++)
            {
                this->data[i*3+j] =  - c1*uvals[i]*uvals[j] - c2*vvals[i]*vvals[j] + c3*vvals[i]*uvals[j];
            }
            this->data[i*4] += (TypeReal)1.0;
        }
    }
    else  // the most common case, unless "from"="to", or "from"=-"to"
    {
        v = fromVec.cross(toVec);
        TypeReal h = (TypeReal)1.0/((TypeReal)1.0 + e);    // optimization by Gottfried Chen
        TypeReal hvx = h*v.x;
        TypeReal hvz = h*v.z;
        TypeReal hvxy = hvx*v.y;
        TypeReal hvxz = hvx*v.z;
        TypeReal hvyz = hvz*v.y;


        this->data[0] = e + hvx*v.x;
        this->data[1] = hvxy - v.z;
        this->data[2] = hvxz + v.y;

        this->data[3] = hvxy + v.z;
        this->data[4] = e + h*v.y*v.y;
        this->data[5] = hvyz - v.x;

        this->data[6] = hvxz - v.y;
        this->data[7] = hvyz + v.x;
        this->data[8] = e + hvz*v.z;
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::createFromVectorToVector(const Vector3<TypeReal> &fromVec, const Vector3<TypeReal> &toVec)
{
    Matrix3<TypeReal> retMat;
    retMat.setFromVectorToVector(fromVec, toVec);
    return retMat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<class TypeReal>
void Matrix3<TypeReal>::lookAt(const Vector3<TypeReal> &pointAt, const Vector3<TypeReal> &normal, Axis primaryAxis, Axis secondaryAxis)
{
    TypeReal f = fabs( pointAt.dot(normal) );
    if (f > 1.0-Math<TypeReal>::EPSILON)
        throw GMathError("gmath::Matrix3:\n\ttarget vector and up vector are perpendicular, impossible to create a matrix out of them.");

    TypeReal pMult = (TypeReal)1.0;
    TypeReal sMult = (TypeReal)1.0;
    if ((int)primaryAxis<0) {
        pMult *= (TypeReal)-1.0;
    }
    if ((int)secondaryAxis<0) {
        sMult = (TypeReal)-1.0;
    }

    Vector3<TypeReal> xVec, yVec, zVec;

    if (primaryAxis == POSX || primaryAxis == NEGX)
    {
        if (secondaryAxis == POSY || secondaryAxis == NEGY)
        {
            xVec = pointAt * pMult;
            yVec = normal * pMult;
            zVec = xVec.cross(yVec);
            zVec.normalizeInPlace();
            yVec = zVec.cross(xVec);
        }
        else if (secondaryAxis == POSZ || secondaryAxis == NEGZ)
        {
            xVec = pointAt * pMult;
            zVec = normal * sMult;
            yVec = zVec.cross(xVec);
            yVec.normalizeInPlace();
            zVec = xVec.cross(yVec);
            //zVec.normalizeInPlace();
        }
    }
    else if (primaryAxis == POSY || primaryAxis == NEGY)
    {
        if (secondaryAxis == POSX || primaryAxis == NEGX)
        {
            yVec = pointAt * pMult;
            xVec = normal * sMult;
            zVec = xVec.cross(yVec);
            zVec.normalizeInPlace();
            xVec = yVec.cross(zVec);
            //xVec.normalizeInPlace()
        }
        else if (secondaryAxis == POSZ || secondaryAxis == NEGX)
        {
            yVec = pointAt * pMult;
            zVec = normal * sMult;
            xVec = yVec.cross(zVec);
            xVec.normalizeInPlace();
            zVec = xVec.cross(yVec);
            //zVec.normalizeInPlace()
        }
    }
    else if (primaryAxis == POSZ || primaryAxis == NEGZ)
    {
        if (secondaryAxis == POSX || secondaryAxis == NEGX)
        {
            zVec = pointAt * pMult;
            xVec = normal * sMult;
            yVec = zVec.cross(xVec);
            yVec.normalizeInPlace();
            xVec = yVec.cross(zVec);
            //xVec.normalizeInPlace();
        }
        else if (secondaryAxis == POSY || secondaryAxis == NEGY)
        {
            zVec = pointAt * pMult;
            yVec = normal * sMult;
            xVec = yVec.cross(zVec);
            xVec.normalizeInPlace();
            yVec = zVec.cross(xVec);
            //yVec.normalizeInPlace();
        }
    }

    data[0]=xVec.x; data[1]=xVec.y; data[2]=xVec.z;
    data[3]=yVec.x; data[4]=yVec.y; data[5]=yVec.z;
    data[6]=zVec.x; data[7]=zVec.y; data[8]=zVec.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::createLookAt(const Vector3<TypeReal> &pointAt, const Vector3<TypeReal> &normal, Axis primaryAxis, Axis secondaryAxis)
{
    Matrix3<TypeReal> mat;
    mat.lookAt(pointAt, normal, primaryAxis, secondaryAxis);
    return mat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<class TypeReal>
void Matrix3<TypeReal>::setFromAxisAngle(const Vector3<TypeReal> &axis, TypeReal angle)
{
    TypeReal sqr_a = axis.x*axis.x;
    TypeReal sqr_b = axis.y*axis.y;
    TypeReal sqr_c = axis.z*axis.z;
    TypeReal len2  = sqr_a+sqr_b+sqr_c;

    TypeReal k2    = cos(angle);
    TypeReal k1    = (1.0-k2)/len2;
    TypeReal k3    = sin(angle)/sqrt(len2);
    TypeReal k1ab  = k1*axis.x*axis.y;
    TypeReal k1ac  = k1*axis.x*axis.z;
    TypeReal k1bc  = k1*axis.y*axis.z;
    TypeReal k3a   = k3*axis.x;
    TypeReal k3b   = k3*axis.y;
    TypeReal k3c   = k3*axis.z;

    data[0] = k1*sqr_a+k2; data[1] = k1ab+k3c;    data[2] = k1ac-k3b;
    data[3] = k1ab-k3c;    data[4] = k1*sqr_b+k2; data[5] = k1bc+k3a;
    data[6] = k1ac+k3b;    data[7] = k1bc-k3a;    data[8] = k1*sqr_c+k2;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<class TypeReal>
Matrix3<TypeReal> Matrix3<TypeReal>::createFromAxisAngle(const Vector3<TypeReal> &axis, TypeReal angle)
{
    Matrix3<TypeReal> mat;
    mat.setFromAxisAngle(axis, angle);
    return mat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <class TypeReal>
std::string Matrix3<TypeReal>::toString() const
{
    char buffer[200];
    sprintf( buffer, "gmath::Matrix3(%f, %f, %f,\n               %f, %f, %f,\n               %f, %f, %f);",
                    data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8] );
    std::string str(buffer);
    return str;
}
/*-----------------------------------------------------------------------------------------------------------------*/