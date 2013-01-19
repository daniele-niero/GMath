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
/*------ constructors ------*/
template <typename real>
Matrix3<real>::Matrix3()
{}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real>::Matrix3(
    real xx, real xy, real xz,
    real yx, real yy, real yz,
    real zx, real zy, real zz)
{
    data[0]=xx; data[1]=xy; data[2]=xz;
    data[3]=yx; data[4]=yy; data[5]=yz;
    data[6]=zx; data[7]=zy; data[8]=zz;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real>::Matrix3(const Matrix3<real> & other)
{
    memcpy(data, other.data, 9*sizeof(real));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real>::Matrix3(
        const Vector3<real> &axisX,
        const Vector3<real> &axisY,
        const Vector3<real> &axisZ)
{
    memcpy(&data[0], axisX.ptr(), 3*sizeof(real));
    memcpy(&data[3], axisY.ptr(), 3*sizeof(real));
    memcpy(&data[6], axisZ.ptr(), 3*sizeof(real));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real>::Matrix3(const real* list)
{
    memcpy(data, list, 9*sizeof(real));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real* Matrix3<real>::ptr()
{
    return &data[0];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
const real* Matrix3<real>::ptr() const
{
    return &data[0];
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Coordinates access ------*/
template <typename real>
real Matrix3<real>::operator[] (int i) const
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
template <typename real>
real& Matrix3<real>::operator[] (int i)
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
template <typename real>
real Matrix3<real>::operator() (int row, int col) const
{
    if (row>=0 && row<3 && col>=0 && col<3)
    {
        return this->data[row*3+col];
    }
    else
    {
        throw out_of_range("gmath::Matrix3: row or column index out of range");
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real &Matrix3<real>::operator() (int row, int col)
{
    if (row>=0 && row<3 && col>=0 && col<3)
    {
        return this->data[row*3+col];
    }
    else
    {
        throw out_of_range("gmath::Matrix3: row or column index out of range");
    }
}
/*------ Arithmetic operations ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Matrix3<real>::operator + (real value) const
{
    Matrix3<real> retMatrix(
        data[0]+value, data[1]+value, data[2]+value,
        data[3]+value, data[4]+value, data[5]+value,
        data[6]+value, data[7]+value, data[8]+value
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Matrix3<real>::operator + (const Matrix3<real> &other) const
{
    
    const real* b = other.ptr();
    Matrix3<real> retMatrix(
        data[0]+b[0], data[1]+b[1], data[2]+b[2],
        data[3]+b[3], data[4]+b[4], data[5]+b[5],
        data[6]+b[6], data[7]+b[7], data[8]+b[8]
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Matrix3<real>::operator - (real value) const
{
    Matrix3<real> retMatrix(
        data[0]-value, data[1]-value, data[2]-value,
        data[3]-value, data[4]-value, data[5]-value,
        data[6]-value, data[7]-value, data[8]-value
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Matrix3<real>::operator - (const Matrix3<real> &other) const
{
    
    const real* b = other.ptr();
    Matrix3<real> retMatrix(
        data[0]-b[0], data[1]-b[1], data[2]-b[2],
        data[3]-b[3], data[4]-b[4], data[5]-b[5],
        data[6]-b[6], data[7]-b[7], data[8]-b[8]
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Matrix3<real>::operator / (real value) const
{
    Matrix3<real> retMatrix(
        data[0]/value, data[1]/value, data[2]/value,
        data[3]/value, data[4]/value, data[5]/value,
        data[6]/value, data[7]/value, data[8]/value
        );

    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Matrix3<real>::operator * (real value) const
{
    Matrix3<real> retMatrix(
        data[0]*value, data[1]*value, data[2]*value,
        data[3]*value, data[4]*value, data[5]*value,
        data[6]*value, data[7]*value, data[8]*value
        );

    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Matrix3<real>::operator * (const Matrix3<real> &other) const
{
    const real* b = other.ptr();
    Matrix3<real> retMatrix(
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
/*------ Arithmetic updates ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::operator += (real value)
{
    data[0]+=value; data[1]+=value; data[2]+=value;
    data[3]+=value; data[4]+=value; data[5]+=value;
    data[6]+=value; data[7]+=value; data[8]+=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::operator += (const Matrix3<real> &other)
{
    real* a = ptr();
    const real* b = other.ptr();
    data[0]+=b[0]; data[1]+=b[1]; data[2]+=b[2];
    data[3]+=b[3]; data[4]+=b[4]; data[5]+=b[5];
    data[6]+=b[6]; data[7]+=b[7]; data[8]+=b[8];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::operator -= (real value)
{
    data[0]-=value; data[1]-=value; data[2]-=value;
    data[3]-=value; data[4]-=value; data[5]-=value;
    data[6]-=value; data[7]-=value; data[8]-=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::operator -= (const Matrix3<real> &other)
{
    real* a = ptr();
    const real* b = other.ptr();

    data[0]-=b[0]; data[1]-=b[1]; data[2]-=b[2];
    data[3]-=b[3]; data[4]-=b[4]; data[5]-=b[5];
    data[6]-=b[6]; data[7]-=b[7]; data[8]-=b[8];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::operator /= (real value)
{
    data[0]/=value; data[1]/=value; data[2]/=value;
    data[3]/=value; data[4]/=value; data[5]/=value;
    data[6]/=value; data[7]/=value; data[8]/=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::operator *= (real value)
{
    data[0]*=value; data[1]*=value; data[2]*=value;
    data[3]*=value; data[4]*=value; data[5]*=value;
    data[6]*=value; data[7]*=value; data[8]*=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::operator *= (const Matrix3<real> &other)
{
    const real* a = &data[0];
    const real* b = &other.data[0];
    real c[9];

    c[0] = data[0]*b[0] + data[1]*b[3] + data[2]*b[6];
    c[1] = data[0]*b[1] + data[1]*b[4] + data[2]*b[7];
    c[2] = data[0]*b[2] + data[1]*b[5] + data[2]*b[8];
    c[3] = data[3]*b[0] + data[4]*b[3] + data[5]*b[6];
    c[4] = data[3]*b[1] + data[4]*b[4] + data[5]*b[7];
    c[5] = data[3]*b[2] + data[4]*b[5] + data[5]*b[8];
    c[6] = data[6]*b[0] + data[7]*b[3] + data[8]*b[6];
    c[7] = data[6]*b[1] + data[7]*b[4] + data[8]*b[7];
    c[8] = data[6]*b[2] + data[7]*b[5] + data[8]*b[8];

    memcpy(data, c, 9*sizeof(real));
}
/*------ Comparisons ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
bool Matrix3<real>::operator == (const Matrix3<real> &other) const
{
    const real* b = &other.data[0];
    real e = Math<real>::EPSILON;
    return (fabs(data[0]-b[0])<e && fabs(data[1]-b[1])<e && fabs(data[2]-b[2])<e &&
            fabs(data[3]-b[3])<e && fabs(data[4]-b[4])<e && fabs(data[5]-b[5])<e &&
            fabs(data[6]-b[6])<e && fabs(data[7]-b[7])<e && fabs(data[8]-b[8])<e);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
bool Matrix3<real>::operator != (const Matrix3<real> &other) const
{
    const real* b = &other.data[0];
    real e = Math<real>::EPSILON;
    return (fabs(data[0]-b[0])>e || fabs(data[1]-b[1])>e || fabs(data[2]-b[3])>e ||
            fabs(data[3]-b[3])>e || fabs(data[0]-b[0])>e || fabs(data[0]-b[0])>e ||
            fabs(data[0]-b[0])>e || fabs(data[0]-b[0])>e || fabs(data[0]-b[0])>e);
}
/*------ Assignment ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::operator = (const Matrix3<real> &other)
{
    memcpy(data, other.data, 9*sizeof(real));
}
/*------ methods ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::setToIdentity()
{
    memcpy(data, Matrix3<real>::IDENTITY.data, 9*sizeof(real));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::set(
    real xx, real xy, real xz,
    real yx, real yy, real yz,
    real zx, real zy, real zz)
{
    data[0]=xx; data[1]=xy; data[2]=xz;
    data[3]=yx; data[4]=yy; data[5]=yz;
    data[6]=zx; data[7]=zy; data[8]=zz;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Matrix3<real>::getRow(unsigned int i) const
{
    if (i>2)
    {
        throw out_of_range("gmath::Matrix3: index out of range");
    }
    return Vector3<real>( data[i*3], data[i*3+1], data[i*3+2] );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::setRow(unsigned int i, const Vector3<real> &vec)
{
    if (i>2)
    {
        throw out_of_range("gmath::Matrix3: index out of range");
    }
    data[i*3]   = vec.x;
    data[i*3+1] = vec.y;
    data[i*3+2] = vec.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Matrix3<real>::getAxisX() const
{
	return getRow(0);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Matrix3<real>::getAxisY() const
{
	return getRow(1);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Matrix3<real>::getAxisZ() const
{
	return getRow(2);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::setAxisX(const Vector3<real>& vec)
{
	setRow(0, vec);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::setAxisY(const Vector3<real>& vec)
{
	setRow(1, vec);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::setAxisZ(const Vector3<real>& vec)
{
	setRow(2, vec);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Matrix3<real>::transpose() const
{
    return Matrix3<real>(
            data[0], data[3], data[6],
            data[1], data[4], data[7],
            data[2], data[5], data[8] );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::transposeInPlace()
{
    this->set(
        data[0], data[3], data[6],
        data[1], data[4], data[7],
        data[2], data[5], data[8] );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Matrix3<real>::determinant() const
{
    real det;
    det = data[0] * ( data[4]*data[8] - data[7]*data[5] )
        - data[1] * ( data[3]*data[8] - data[6]*data[5] )
        + data[2] * ( data[3]*data[7] - data[6]*data[4] );
    return det;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Matrix3<real>::inverse() const
{
    Matrix3<real> retMatrix;
    real invDet = (real)1/determinant();

    if ( invDet < Math<real>::EPSILON )
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
template <typename real>
void Matrix3<real>::inverseInPlace()
{
    real m[9];
    real invDet = (real)1/determinant();

    if ( invDet < Math<real>::EPSILON )
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

        memcpy(data, m, 9*sizeof(real));
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Matrix3<real>::orthogonal() const
{
    Matrix3<real> m(*this);
    m.orthogonalInPlace();
    return m;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::orthogonalInPlace() //primaryAxis, secondaryAxis)
{
    // Code take it from WildMagic 5  -  www.geometrictools.com  -  here the matrix is transpose
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
    real invLength = (real)(1.0 / sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]));

    data[0] *= invLength;
    data[1] *= invLength;
    data[2] *= invLength;

    // Compute q1.
    real dot0 = data[0]*data[3] + data[1]*data[4] +
        data[2]*data[5];

    data[3] -= dot0*data[0];
    data[4] -= dot0*data[1];
    data[5] -= dot0*data[2];

    invLength = (real)(1.0 / sqrt(data[3]*data[3] + data[4]*data[4] + data[5]*data[5]));

    data[3] *= invLength;
    data[4] *= invLength;
    data[5] *= invLength;

    // compute q2
    real dot1 = data[3]*data[6] + data[4]*data[7] +
        data[5]*data[8];

    dot0 = data[0]*data[6] + data[1]*data[7] +
        data[2]*data[8];

    data[6] -= dot0*data[0] + dot1*data[3];
    data[7] -= dot0*data[1] + dot1*data[4];
    data[8] -= dot0*data[2] + dot1*data[5];

    invLength = (real)(1.0 / sqrt(data[6]*data[6] + data[7]*data[7] + data[8]*data[8]));

    data[6] *= invLength;
    data[7] *= invLength;
    data[8] *= invLength;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Matrix3<real>::getScale() const
{
    Vector3<real> x(data[0], data[1], data[2]);
    Vector3<real> y(data[3], data[4], data[5]);
    Vector3<real> z(data[6], data[7], data[8]);

    return Vector3<real>(x.length(), y.length(), z.length());
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::addScale(const Vector3<real> &scale)
{
    data[0]+=scale.x; data[1]+=scale.x; data[2]+=scale.x;
    data[3]+=scale.y; data[4]+=scale.y; data[5]+=scale.y;
    data[6]+=scale.z; data[7]+=scale.z; data[8]+=scale.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::addScale(real sX, real sY, real sZ)
{
    data[0]+=sX; data[1]+=sX; data[2]+sX;
    data[3]+=sY; data[4]+=sY; data[5]+sY;
    data[6]+=sZ; data[7]+=sZ; data[8]+sZ;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::setScale(const Vector3<real> &scale)
{
    Vector3<real> x(data[0], data[1], data[2]);
    Vector3<real> y(data[3], data[4], data[5]);
    Vector3<real> z(data[6], data[7], data[8]);
    x.normalizeInPlace();
    y.normalizeInPlace();
    z.normalizeInPlace();
    x *= scale.x;
    y *= scale.y;
    z *= scale.z;

    this->set(
        x.x, x.y, x.z,
        y.x, y.y, y.z,
        z.x, z.y, z.z );
}
/*-----------------------------------------------------------------------------------------------------------------*//*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::setScale(real sX, real sY, real sZ)
{
    Vector3<real> x(data[0], data[1], data[2]);
    Vector3<real> y(data[3], data[4], data[5]);
    Vector3<real> z(data[6], data[7], data[8]);
    x.normalizeInPlace();
    y.normalizeInPlace();
    z.normalizeInPlace();
    x *= sX;
    y *= sY;
    z *= sZ;

    this->set(
        x.x, x.y, x.z,
        y.x, y.y, y.z,
        z.x, z.y, z.z );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix3<real>::setFromEuler(const real& angleX, const real& angleY, const real& angleZ, RotationOrder order)
{
    real cx, sx, cy, sy, cz, sz;

    cx = cos(angleX);
    sx = sin(angleX);
    cy = cos(angleY);
    sy = sin(angleY);
    cz = cos(angleZ);
    sz = sin(angleZ);


    Matrix3<real> XMat(
        1.0, 0.0, 0.0,
        0.0,  cx,  sx,
        0.0, -sx,  cx);

    Matrix3<real> YMat(
         cy, 0.0, -sy,
        0.0, 1.0, 0.0,
         sy, 0.0,  cy);

    Matrix3<real> ZMat(
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
template <typename real>
void Matrix3<real>::setFromEuler(const Euler<real> &rotation, RotationOrder order)
{
    setFromEuler(rotation.x, rotation.y, rotation.z, order);
}
/*-----------------------------------------------------------------------------------------------------------------*//*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
Euler<real> Matrix3<real>::toEuler(RotationOrder order)
{
    Euler<real> retAngles;
    toEuler(retAngles, order);
    return retAngles;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
bool Matrix3<real>::toEuler(Euler<real>& euler, RotationOrder order)
{
    real C;
    switch (order)
    {
    case XYZ :
        euler.y = Math<real>::asin(-data[2]);
        C = (real)cos((double)euler.y);
        if ( C<(real)1 || C>(real)-1)
        {
            euler.x = atan2(data[5], data[8]);
            euler.z = atan2(data[1], data[0]);
            return true;
        }
        else
        {
            euler.z = (real)0;
            euler.x = atan2(-data[5], data[8]);
            return false;
        }

    case XZY :
        euler.z = Math<real>::asin(data[1]);
        C = (real)cos((double)euler.z);
        if ( C<(real)1 || C>(real)-1)
        {
            euler.x = atan2(-data[7], data[4]);
            euler.y = atan2(-data[2], data[0]);
            return true;
        }
        else
        {
            // WARNING.  The solution is not unique.  Choosing y_angle = 0.
            euler.x = atan2(data[6] ,data[8]);
            euler.y = (real)0;
            return false;
        }

    case YXZ :
        euler.x = Math<real>::asin(data[5]);
        C = (real)cos((double)euler.x);
        if ( C<(real)1 || C>(real)-1)
        {
            euler.y = atan2(-data[2], data[8]);
            euler.z = atan2(-data[3], data[4]);
            return true;
        }
        else
        {
            // WARNING.  The solution is not unique.  Choosing z_angle = 0.
            euler.y = atan2(data[1], data[0]);
            euler.z = (real)0;
            return false;
        }

    case YZX :
        euler.z = Math<real>::asin(-data[3]);
        C = (real)cos((double)euler.z);
        if ( C<(real)1 || C>(real)-1)
        {
            euler.y = atan2(data[6], data[0]);
            euler.x = atan2(data[5], data[4]);
            return true;
        }
        else
        {
            // WARNING.  The solution is not unique.  Choosing x_angle = 0.
            euler.y = atan2(data[7], data[8]);
            euler.x = (real)0;
            return false;
        }

    case ZXY :
        euler.x = Math<real>::asin(-data[7]);
        C = (real)cos((double)euler.x);
        if ( C<(real)1 || C>(real)-1)
        {
            euler.z = atan2(data[1], data[4]);
            euler.y = atan2(data[6], data[8]);
            return true;
        }
        else
        {
            // WARNING.  The solution is not unique.  Choosing y_angle = 0.
            euler.z = atan2(data[2], data[0]);
            euler.y = (real)0;
            return false;
        }

    case ZYX :
        euler.y = Math<real>::asin(data[6]);
        C = (real)cos((double)euler.y);
        if ( C<(real)1 || C>(real)-1)
        {
            euler.z = atan2(-data[3], data[0]);
            euler.x = atan2(-data[7], data[8]);
            return true;
        }
        else
        {
            // WARNING.  The solution is not unique.  Choosing x_angle = 0.
            euler.z = atan2(-data[1], data[2]);
            euler.x = (real)0;
            return false;
        }
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix3<real>::setFromVectorToVector(const Vector3<real> &fromVec, const Vector3<real> &toVec)
{
    Vector3<real> x, u, v;
    real e = fromVec.dot(toVec);
    real f = fabs(e);

    if (f > 1.0-Math<real>::EPSILON) // "from" and "to" vectors parallel or almost parallel
    {
        real fx = fabs(fromVec.x);
        real fy = fabs(fromVec.y);
        real fz = fabs(fromVec.z);

        if (fx<fy)
        {
            if (fx<fz) {
                x.set((real)1.0, (real)0.0, (real)0.0);
            }
            else {
                x.set((real)0.0, (real)0.0, (real)1.0);
            }
        }
        else
        {
            if (fy<fz) {
                x.set((real)0.0, (real)1.0, (real)0.0);
            }
            else {
                x.set((real)0.0, (real)0.0, (real)1.0);
            }
        }

        u = x - fromVec;
        v = x - toVec;

        real c1 = (real)2.0/(u.dot(u));
        real c2 = (real)2.0/(v.dot(v));
        real c3 = v.dot(u*(c1*c2));

        real uvals[3];
        real vvals[3];
        uvals[0]=u.x; uvals[1]=u.y; uvals[2]=u.z;
        vvals[0]=v.x; vvals[1]=v.y; vvals[2]=v.z;
        for (unsigned int i=0; i<3; i++)
        {
            for (unsigned int j=0; j<3; j++)
            {
                this->data[i*3+j] =  - c1*uvals[i]*uvals[j] - c2*vvals[i]*vvals[j] + c3*vvals[i]*uvals[j];
            }
            // this->data[i*4] += (real)1.0;
        }
    }
    else  // the most common case, unless "from"="to", or "from"=-"to"
    {
        v = fromVec.cross(toVec);
        real h = (real)1.0/((real)1.0 + e);    // optimization by Gottfried Chen
        real hvx = h*v.x;
        real hvz = h*v.z;
        real hvxy = hvx*v.y;
        real hvxz = hvx*v.z;
        real hvyz = hvz*v.y;


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
template<typename real>
void Matrix3<real>::lookAt(const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis, Axis secondaryAxis)
{
    Vector3<real> primary, secondary, terziary;
    
	primary = pointAt;
    secondary = normal;
	primary.normalizeInPlace();
	secondary.normalizeInPlace();

	/*
    real f = fabs( primary.dot(secondary) );
    if (f > 1.0-Math<real>::EPSILON)
        throw GMathError("gmath::Matrix4:\n\ttarget vector and up vector are perpendicular, impossible to create a matrix out of them.");
	*/
    
	terziary = primary.cross(secondary);
    secondary = terziary.cross(primary);

	if ( ((int)primaryAxis<0) && ((int)secondaryAxis>0) ) 
	{
        primary  *= (real)-1.0;
		terziary *= (real)-1.0;
    }
    else if ( ((int)primaryAxis>0) && ((int)secondaryAxis<0) ) 
	{
        secondary *= (real)-1.0;
		terziary  *= (real)-1.0;
    }
	else if ( ((int)primaryAxis<0) && ((int)secondaryAxis<0) )
	{
		primary   *= (real)-1.0;
		secondary *= (real)-1.0;
	} 

    if (primaryAxis == POSX || primaryAxis == NEGX)
    {
        if (secondaryAxis == POSY || secondaryAxis == NEGY)
        {
			this->setAxisX(primary);
			this->setAxisY(secondary);
			this->setAxisZ(terziary);
        }
        else if (secondaryAxis == POSZ || secondaryAxis == NEGZ)
        {
            this->setAxisX(primary);
			this->setAxisY(terziary);
			this->setAxisZ(secondary);
        }
    }
    else if (primaryAxis == POSY || primaryAxis == NEGY)
    {
        if (secondaryAxis == POSX || primaryAxis == NEGX)
        {
            this->setAxisX(secondary);
			this->setAxisY(primary);
			this->setAxisZ(terziary);
        }
        else if (secondaryAxis == POSZ || secondaryAxis == NEGX)
        {
            this->setAxisX(terziary);
			this->setAxisY(primary);
			this->setAxisZ(secondary);
        }
    }
    else if (primaryAxis == POSZ || primaryAxis == NEGZ)
    {
        if (secondaryAxis == POSX || secondaryAxis == NEGX)
        {
            this->setAxisX(terziary);
			this->setAxisY(secondary);
			this->setAxisZ(primary);
        }
        else if (secondaryAxis == POSY || secondaryAxis == NEGY)
        {
            this->setAxisX(terziary);
			this->setAxisY(secondary);
			this->setAxisZ(primary);
        }
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
Matrix3<real> Matrix3<real>::createLookAt(const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis, Axis secondaryAxis)
{
    Matrix3<real> mat;
    mat.lookAt(pointAt, normal, primaryAxis, secondaryAxis);
    return mat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix3<real>::setFromAxisAngle(const Vector3<real> &axis, real angle)
{
    real sqr_a = axis.x*axis.x;
    real sqr_b = axis.y*axis.y;
    real sqr_c = axis.z*axis.z;
    real len2  = sqr_a+sqr_b+sqr_c;

    real k2    = cos(angle);
    real k1    = (1.0-k2)/len2;
    real k3    = sin(angle)/sqrt(len2);
    real k1ab  = k1*axis.x*axis.y;
    real k1ac  = k1*axis.x*axis.z;
    real k1bc  = k1*axis.y*axis.z;
    real k3a   = k3*axis.x;
    real k3b   = k3*axis.y;
    real k3c   = k3*axis.z;

    data[0] = k1*sqr_a+k2; data[1] = k1ab+k3c;    data[2] = k1ac-k3b;
    data[3] = k1ab-k3c;    data[4] = k1*sqr_b+k2; data[5] = k1bc+k3a;
    data[6] = k1ac+k3b;    data[7] = k1bc-k3a;    data[8] = k1*sqr_c+k2;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
std::string Matrix3<real>::toString() const
{
    std::stringstream oss;
    oss << "gmath::Matrix3(" << data[0] << ", " << data[1] << ", " << data[2] << std::endl;
    oss << "               " << data[3] << ", " << data[4] << ", " << data[5] << std::endl;
    oss << "               " << data[6] << ", " << data[7] << ", " << data[8] << ");";

    return oss.str();
}
/*-----------------------------------------------------------------------------------------------------------------*/
