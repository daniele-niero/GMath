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
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real>::Matrix4()
{
     data[0]=(real)1.0;  data[1]=(real)0.0;  data[2]=(real)0.0;  data[3]=(real)0.0;
     data[4]=(real)0.0;  data[5]=(real)1.0;  data[6]=(real)0.0;  data[7]=(real)0.0;
     data[8]=(real)0.0;  data[9]=(real)0.0; data[10]=(real)1.0; data[11]=(real)0.0;
    data[12]=(real)0.0; data[13]=(real)0.0; data[14]=(real)0.0; data[15]=(real)1.0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real>::Matrix4(
    real xx, real xy, real xz, real xw,
    real yx, real yy, real yz, real yw,
    real zx, real zy, real zz, real zw,
    real px, real py, real pz, real pw)
{
    data[0]=xx;  data[1]=xy;  data[2]=xz;  data[3]=xw;
    data[4]=yx;  data[5]=yy;  data[6]=yz;  data[7]=yw;
    data[8]=zx;  data[9]=zy;  data[10]=zz; data[11]=zw;
    data[12]=px; data[13]=py; data[14]=pz; data[15]=pw;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real>::Matrix4(const Matrix4<real> & other)
{
    memcpy(data, other.data, 16*sizeof(real));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real>::Matrix4(
    const Vector4<real> &row0,
    const Vector4<real> &row1,
    const Vector4<real> &row2,
    const Vector4<real> &row3)
{
    memcpy(&data[0],  row0.ptr(), 4*sizeof(real));
    memcpy(&data[4],  row1.ptr(), 4*sizeof(real));
    memcpy(&data[8],  row2.ptr(), 4*sizeof(real));
    memcpy(&data[12], row3.ptr(), 4*sizeof(real));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real>::Matrix4(
    const Vector3<real> &row0,
    const Vector3<real> &row1,
    const Vector3<real> &row2,
    const Vector3<real> &row3)
{
    memcpy(&data[0],  row0.ptr(), 3*sizeof(real));
    memcpy(&data[4],  row1.ptr(), 3*sizeof(real));
    memcpy(&data[8],  row2.ptr(), 3*sizeof(real));
    memcpy(&data[12], row3.ptr(), 3*sizeof(real));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real>::Matrix4(
    const Vector3<real> &row0,
    const Vector3<real> &row1,
    const Vector3<real> &row2)
{
    memcpy(&data[0],  row0.ptr(), 3*sizeof(real));
    memcpy(&data[4],  row1.ptr(), 3*sizeof(real));
    memcpy(&data[8],  row2.ptr(), 3*sizeof(real));
    data[12]=(real)0.0; data[13]=(real)0.0; data[14]=(real)0.0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real>::Matrix4(const Quaternion<real> &quat)
{
	quat.setMatrix4((*this));
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real>::Matrix4(const Quaternion<real> &quat, const Vector3<real> &pos)
{
	quat.setMatrix4((*this));
	this->setPosition(pos);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real>::Matrix4(const real* list)
{
    memcpy(data, list, 16*sizeof(real));
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Coordinates access ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real* Matrix4<real>::ptr()
{
    return &data[0];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
const real* Matrix4<real>::ptr() const
{
    return &data[0];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Matrix4<real>::operator[] (int i) const
{
    if (i>=0 && i<16)
    {
        return this->data[i];
    }
    else {
        throw out_of_range("gmath::Matrix3: index out of range");
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real& Matrix4<real>::operator[] (int i)
{
    if (i>=0 && i<16)
    {
        return this->data[i];
    }
    else {
        throw out_of_range("gmath::Vector4: index out of range");
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Matrix4<real>::operator() (int row, int col) const
{
    if (row>=0 && row<4 && col>=0 && col<4)
    {
        return this->data[row*4+col];
    }
    else
    {
        throw out_of_range("gmath::Matrix4: row or column index out of range");
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real &Matrix4<real>::operator() (int row, int col)
{
    if (row>=0 && row<4 && col>=0 && col<4)
    {
        return this->data[row*4+col];
    }
    else
    {
        throw out_of_range("gmath::Matrix4: row or column index out of range");
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Arithmetic operations ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real> Matrix4<real>::operator + (const real &value) const
{
    Matrix4<real> retMatrix(
        data[0]+value,  data[1]+value,  data[2]+value,  data[3]+value,
        data[4]+value,  data[5]+value,  data[6]+value,  data[7]+value,
        data[8]+value,  data[9]+value,  data[10]+value, data[11]+value,
        data[12]+value, data[13]+value, data[14]+value, data[15]+value
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real> Matrix4<real>::operator + (const Matrix4<real> &other) const
{
    const real* b = other.ptr();
    Matrix4<real> retMatrix(
        data[0]+b[0],   data[1]+b[1],   data[2]+b[2],   data[3]+b[3],
        data[4]+b[4],   data[5]+b[5],   data[6]+b[6],   data[7]+b[7],
        data[8]+b[8],   data[9]+b[9],   data[10]+b[10], data[11]+b[11],
        data[12]+b[12], data[13]+b[13], data[14]+b[14], data[15]+b[15]
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real> Matrix4<real>::operator - (const real &value) const
{
    Matrix4<real> retMatrix(
        data[0]-value,  data[1]-value,  data[2]-value,  data[3]-value,
        data[4]-value,  data[5]-value,  data[6]-value,  data[7]-value,
        data[8]-value,  data[9]-value,  data[10]-value, data[11]-value,
        data[12]-value, data[13]-value, data[14]-value, data[15]-value
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real> Matrix4<real>::operator - (const Matrix4<real> &other) const
{
    const real* b = other.ptr();
    Matrix4<real> retMatrix(
        data[0]-b[0],   data[1]-b[1],   data[2]-b[2],   data[3]-b[3],
        data[4]-b[4],   data[5]-b[5],   data[6]-b[6],   data[7]-b[7],
        data[8]-b[8],   data[9]-b[9],   data[10]-b[10], data[11]-b[11],
        data[12]-b[12], data[13]-b[13], data[14]-b[14], data[15]-b[15]
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real> Matrix4<real>::operator / (const real &value) const
{
    Matrix4<real> retMatrix(
        data[0]/value,  data[1]/value,  data[2]/value,  data[3]/value,
        data[4]/value,  data[5]/value,  data[6]/value,  data[7]/value,
        data[8]/value,  data[9]/value,  data[10]/value, data[11]/value,
        data[12]/value, data[13]/value, data[14]/value, data[15]/value
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real> Matrix4<real>::operator * (const real &value) const
{
    Matrix4<real> retMatrix(
        data[0]*value,  data[1]*value,  data[2]*value,  data[3]*value,
        data[4]*value,  data[5]*value,  data[6]*value,  data[7]*value,
        data[8]*value,  data[9]*value,  data[10]*value, data[11]*value,
        data[12]*value, data[13]*value, data[14]*value, data[15]*value
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real> Matrix4<real>::operator * (const Matrix4<real> &other) const
{
    const real* b = other.ptr();
    Matrix4<real> retMatrix(
        data[0]*b[0] + data[1]*b[4] + data[2]*b[8]  + data[3]*b[12],
        data[0]*b[1] + data[1]*b[5] + data[2]*b[9]  + data[3]*b[13],
        data[0]*b[2] + data[1]*b[6] + data[2]*b[10] + data[3]*b[14],
        data[0]*b[3] + data[1]*b[7] + data[2]*b[11] + data[3]*b[15],

        data[4]*b[0] + data[5]*b[4] + data[6]*b[8]  + data[7]*b[12],
        data[4]*b[1] + data[5]*b[5] + data[6]*b[9]  + data[7]*b[13],
        data[4]*b[2] + data[5]*b[6] + data[6]*b[10] + data[7]*b[14],
        data[4]*b[3] + data[5]*b[7] + data[6]*b[11] + data[7]*b[15],

        data[8]*b[0] + data[9]*b[4] + data[10]*b[8]  + data[11]*b[12],
        data[8]*b[1] + data[9]*b[5] + data[10]*b[9]  +  data[11]*b[13],
        data[8]*b[2] + data[9]*b[6] + data[10]*b[10] + data[11]*b[14],
        data[8]*b[3] + data[9]*b[7] + data[10]*b[11] + data[11]*b[15],

        data[12]*b[0] + data[13]*b[4] + data[14]*b[8]  + data[15]*b[12],
        data[12]*b[1] + data[13]*b[5] + data[14]*b[9]  + data[15]*b[13],
        data[12]*b[2] + data[13]*b[6] + data[14]*b[10] + data[15]*b[14],
        data[12]*b[3] + data[13]*b[7] + data[14]*b[11] + data[15]*b[15]
        );
    return retMatrix;
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Arithmetic updates ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::operator += (const real &value)
{
     data[0]+=value;  data[1]+=value;  data[2]+=value;  data[3]+=value;
     data[4]+=value;  data[5]+=value;  data[6]+=value;  data[7]+=value;
     data[8]+=value;  data[9]+=value; data[10]+=value; data[11]+=value;
    data[12]+=value; data[13]+=value; data[14]+=value; data[15]+=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::operator += (const Matrix4<real> &other)
{
    const real* b = other.ptr();

     data[0]+=b[0];   data[1]+=b[1];   data[2]+=b[2];   data[3]+=b[3];
     data[4]+=b[4];   data[5]+=b[5];   data[6]+=b[6];   data[7]+=b[7];
     data[8]+=b[8];   data[9]+=b[9];  data[10]+=b[10]; data[11]+=b[11];
    data[12]+=b[12]; data[13]+=b[13]; data[14]+=b[14]; data[15]+=b[15];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::operator -= (const real &value)
{
     data[0]-=value;  data[1]-=value;  data[2]-=value;  data[3]-=value;
     data[4]-=value;  data[5]-=value;  data[6]-=value;  data[7]-=value;
     data[8]-=value;  data[9]-=value; data[10]-=value; data[11]-=value;
    data[12]-=value; data[13]-=value; data[14]-=value; data[15]-=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::operator -= (const Matrix4<real> &other)
{
    const real* b = other.ptr();

     data[0]-=b[0];   data[1]-=b[1];   data[2]-=b[2];   data[3]-=b[3];
     data[4]-=b[4];   data[5]-=b[5];   data[6]-=b[6];   data[7]-=b[7];
     data[8]-=b[8];   data[9]-=b[9];  data[10]-=b[10]; data[11]-=b[11];
    data[12]-=b[12]; data[13]-=b[13]; data[14]-=b[14]; data[15]-=b[15];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::operator /= (const real &value)
{
     data[0]/=value;  data[1]/=value;  data[2]/=value;  data[3]/=value;
     data[4]/=value;  data[5]/=value;  data[6]/=value;  data[7]/=value;
     data[8]/=value;  data[9]/=value; data[10]/=value; data[11]/=value;
    data[12]/=value; data[13]/=value; data[14]/=value; data[15]/=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::operator *= (const real &value)
{
     data[0]*=value;  data[1]*=value;  data[2]*=value;  data[3]*=value;
     data[4]*=value;  data[5]*=value;  data[6]*=value;  data[7]*=value;
     data[8]*=value;  data[9]*=value; data[10]*=value; data[11]*=value;
    data[12]*=value; data[13]*=value; data[14]*=value; data[15]*=value;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::operator *= (const Matrix4<real> &other)
{
    const real* b = other.ptr();
    set(
        data[0]*b[0] + data[1]*b[4] + data[2]*b[8]  + data[3]*b[12],
        data[0]*b[1] + data[1]*b[5] + data[2]*b[9]  + data[3]*b[13],
        data[0]*b[2] + data[1]*b[6] + data[2]*b[10] + data[3]*b[14],
        data[0]*b[3] + data[1]*b[7] + data[2]*b[11] + data[3]*b[15],

        data[4]*b[0] + data[5]*b[4] + data[6]*b[8]  + data[7]*b[12],
        data[4]*b[1] + data[5]*b[5] + data[6]*b[9]  + data[7]*b[13],
        data[4]*b[2] + data[5]*b[6] + data[6]*b[10] + data[7]*b[14],
        data[4]*b[3] + data[5]*b[7] + data[6]*b[11] + data[7]*b[15],

        data[8]*b[0] + data[9]*b[4] + data[10]*b[8]  + data[11]*b[12],
        data[8]*b[1] + data[9]*b[5] + data[10]*b[9]  +  data[11]*b[13],
        data[8]*b[2] + data[9]*b[6] + data[10]*b[10] + data[11]*b[14],
        data[8]*b[3] + data[9]*b[7] + data[10]*b[11] + data[11]*b[15],

        data[12]*b[0] + data[13]*b[4] + data[14]*b[8]  + data[15]*b[12],
        data[12]*b[1] + data[13]*b[5] + data[14]*b[9]  + data[15]*b[13],
        data[12]*b[2] + data[13]*b[6] + data[14]*b[10] + data[15]*b[14],
        data[12]*b[3] + data[13]*b[7] + data[14]*b[11] + data[15]*b[15]
        );
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Comparisons ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
bool Matrix4<real>::operator == (const Matrix4<real> &other) const
{
    const real* b = &other.data[0];
    real e = Math<real>::EPSILON;
    return (fabs(data[0]-b[0])<e && fabs(data[1]-b[1])<e && fabs(data[2]-b[2])<e && fabs(data[3]-b[3])<e && 
            fabs(data[4]-b[4])<e && fabs(data[5]-b[5])<e && fabs(data[6]-b[6])<e && fabs(data[7]-b[7])<e && 
            fabs(data[8]-b[8])<e && fabs(data[9]-b[9])<e && fabs(data[10]-b[10])<e && fabs(data[11]-b[11])<e &&
            fabs(data[12]-b[12])<e && fabs(data[13]-b[13])<e && fabs(data[14]-b[14])<e && fabs(data[15]-b[15])<e);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
bool Matrix4<real>::operator != (const Matrix4<real> &other) const
{
    const real* b = &other.data[0];
    real e = Math<real>::EPSILON;
    return (fabs(data[0]-b[0])>e || fabs(data[1]-b[1])>e || fabs(data[2]-b[2])>e || fabs(data[3]-b[3])>e ||
            fabs(data[4]-b[4])>e || fabs(data[5]-b[5])>e || fabs(data[6]-b[6])>e || fabs(data[7]-b[7])>e || 
            fabs(data[8]-b[8])>e || fabs(data[9]-b[9])>e || fabs(data[10]-b[10])>e || fabs(data[11]-b[11])>e ||
            fabs(data[12]-b[12])>e || fabs(data[13]-b[13])>e || fabs(data[14]-b[14])>e || fabs(data[15]-b[15])>e);
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*------ Assignment ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::operator = (const Matrix4<real> &other)
{
    data[ 0] = other.data[0];
    data[ 1] = other.data[1];
    data[ 2] = other.data[2];
    data[ 3] = other.data[3];
    data[ 4] = other.data[4];
    data[ 5] = other.data[5];
    data[ 6] = other.data[6];
    data[ 7] = other.data[7];
    data[ 8] = other.data[8];
    data[ 9] = other.data[9];
    data[10] = other.data[10];
    data[11] = other.data[11];
    data[12] = other.data[12];
    data[13] = other.data[13];
    data[14] = other.data[14];
    data[15] = other.data[15];
}
/*------ Methods ------*/
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::setToIdentity()
{
    data[0] =(real)1;  data[1]=(real)0;  data[2]=(real)0;  data[3]=(real)0;
    data[4] =(real)0;  data[5]=(real)1;  data[6]=(real)0;  data[7]=(real)0;
    data[8] =(real)0;  data[9]=(real)0; data[10]=(real)1; data[11]=(real)0;
    data[12]=(real)0; data[13]=(real)0; data[14]=(real)0; data[15]=(real)1;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::set(
    real xx, real xy, real xz, real xw,
    real yx, real yy, real yz, real yw,
    real zx, real zy, real zz, real zw,
    real px, real py, real pz, real pw)
{
    data[0]=xx;  data[1]=xy;  data[2]=xz;  data[3]=xw;
    data[4]=yx;  data[5]=yy;  data[6]=yz;  data[7]=yw;
    data[8]=zx;  data[9]=zy;  data[10]=zz; data[11]=zw;
    data[12]=px; data[13]=py; data[14]=pz; data[15]=pw;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
Vector3<real> Matrix4<real>::getRow(unsigned int i) const
{
    if (i>3)
    {
        throw out_of_range("gmath::Matrix4: index out of range");
    }
    return Vector3<real>( data[i*4], data[i*4+1], data[i*4+2] );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
Vector4<real> Matrix4<real>::getRow2(unsigned int i) const
{
    if (i>3)
    {
        throw out_of_range("gmath::Matrix4: index out of range");
    }
    return Vector4<real>( data[i*4], data[i*4+1], data[i*4+2], data[i*4+3] );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix4<real>::setRow(unsigned int i, const Vector3<real> &vec)
{
    if (i>3)
    {
        throw out_of_range("gmath::Matrix4: index out of range");
    }
    data[i*4]   = vec.x;
    data[i*4+1] = vec.y;
    data[i*4+2] = vec.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix4<real>::setRow(unsigned int i, const Vector4<real> &vec)
{
    if (i>4)
    {
        throw out_of_range("gmath::Matrix4: index out of range");
    }
    data[i*4]   = vec.x;
    data[i*4+1] = vec.y;
    data[i*4+2] = vec.z;
    data[i*4+3] = vec.w;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
Vector3<real> Matrix4<real>::getAxisX() const
{
    return getRow(0);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
Vector3<real> Matrix4<real>::getAxisY() const
{
    return getRow(1);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
Vector3<real> Matrix4<real>::getAxisZ() const
{
    return getRow(2);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix4<real>::setAxisX(const Vector3<real> &vec)
{
    setRow(0, vec);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix4<real>::setAxisY(const Vector3<real> &vec)
{
    setRow(1, vec);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix4<real>::setAxisZ(const Vector3<real> &vec)
{
    setRow(2, vec);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::setPosition(const Vector3<real> &pos)
{
    data[12] = pos.x;
    data[13] = pos.y;
    data[14] = pos.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::setPosition(real inX, real inY, real inZ)
{
    data[12] = inX;
    data[13] = inY;
    data[14] = inZ;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::addPosition(const Vector3<real> &pos)
{
    data[12] += pos.x;
    data[13] += pos.y;
    data[14] += pos.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::addPosition(real inX, real inY, real inZ)
{
    data[12] += inX;
    data[13] += inY;
    data[14] += inZ;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::translate (const Vector3<real> &pos)
{
    data[12] += pos.x * data[0] + pos.y * data[4] + pos.z * data[8];
    data[13] += pos.x * data[1] + pos.y * data[5] + pos.z * data[9];
    data[14] += pos.x * data[2] + pos.y * data[6] + pos.z * data[10];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::translate(real inX, real inY, real inZ)
{
    data[12] += inX * data[0] + inY * data[4] + inZ * data[8];
    data[13] += inX * data[1] + inY * data[5] + inZ * data[9];
    data[14] += inX * data[2] + inY * data[6] + inZ * data[10];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Matrix4<real>::getPosition() const
{
    return Vector3<real>( data[12], data[13], data[14] );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::setRotation(const Matrix3<real>& rotationMatrix)
{
    const real* rot = &rotationMatrix.data[0];
    data[0]=rot[0];  data[1]=rot[1];  data[2]=rot[2];  
    data[4]=rot[3];  data[5]=rot[4];  data[6]=rot[5];
    data[8]=rot[6];  data[9]=rot[7];  data[10]=rot[8];
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::setRotation(const Quaternion<real>& rotationQuat)
{
	rotationQuat.setMatrix4( (*this) );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix4<real>::setRotation(real angleX, real angleY, real angleZ, RotationOrder order)
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
        this->setRotation( XMat*(YMat*ZMat) );
        break;
    case XZY :
        this->setRotation( XMat*(ZMat*YMat) );
        break;
    case YXZ :
        this->setRotation( YMat*(XMat*ZMat) );
        break;
    case YZX :
        this->setRotation( YMat*(ZMat*XMat) );
        break;
    case ZXY :
        this->setRotation( ZMat*(XMat*YMat) );
        break;
    case ZYX :
        this->setRotation( ZMat*(YMat*XMat) );
        break;
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix4<real>::setRotation(const Euler<real> &rotation, RotationOrder order)
{
    this->setRotation(rotation.x, rotation.y, rotation.z, order);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Matrix4<real>::getScale() const
{
    Vector3<real> x(data[0], data[1], data[2]);
    Vector3<real> y(data[4], data[5], data[6]);
    Vector3<real> z(data[8], data[9], data[10]);

    return Vector3<real>(x.length(), y.length(), z.length());
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::setScale(const Vector3<real> &scale)
{
    Vector3<real> x(data[0], data[1], data[2]);
    Vector3<real> y(data[4], data[5], data[6]);
    Vector3<real> z(data[8], data[9], data[10]);
    x.normalizeInPlace();
    y.normalizeInPlace();
    z.normalizeInPlace();
    x *= scale.x;
    y *= scale.y;
    z *= scale.z;

    data[0]=x.x; data[1]=x.y; data[2]=x.z;
    data[4]=y.x; data[5]=y.y; data[6]=y.z;
    data[8]=z.x; data[9]=z.y; data[10]=z.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::setScale(real sX, real sY, real sZ)
{
    Vector3<real> x(data[0], data[1], data[2]);
    Vector3<real> y(data[4], data[5], data[6]);
    Vector3<real> z(data[8], data[9], data[10]);
    x.normalizeInPlace();
    y.normalizeInPlace();
    z.normalizeInPlace();
    x *= sX;
    y *= sY;
    z *= sZ;

    data[0]=x.x; data[1]=x.y; data[2]=x.z;
    data[4]=y.x; data[5]=y.y; data[6]=y.z;
    data[8]=z.x; data[9]=z.y; data[10]=z.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::addScale(const Vector3<real> &scale)
{

    data[0]+=scale.x; data[1]+=scale.x; data[2]+=scale.x;
    data[4]+=scale.y; data[5]+=scale.y; data[6]+=scale.y;
    data[8]+=scale.z; data[9]+=scale.z; data[10]+=scale.z;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::addScale(real sX, real sY, real sZ)
{
    data[0]+=sX; data[1]+=sX; data[2]+=sX;
    data[4]+=sY; data[5]+=sY; data[6]+=sY;
    data[8]+=sZ; data[9]+=sZ; data[10]+=sZ;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix3<real> Matrix4<real>::toMatrix3() const
{
    Matrix3<real> rot(
        data[0],  data[1],  data[2],  
        data[4],  data[5],  data[6],
        data[8],  data[9],  data[10]);
    return rot;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Quaternion<real> Matrix4<real>::toQuaternion() const
{
	Quaternion<real> quat;
    quat.fromMatrix4( (*this) );
    return quat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
Euler<real> Matrix4<real>::toEuler(RotationOrder order) const
{
    Euler<real> retEuler;
    this->toEuler(retEuler, order);
    return retEuler;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::toMatrix3(Matrix3<real> &outMatrix3) const
{
    outMatrix3.set(
        data[0], data[1], data[2],  
        data[4], data[5], data[6],
        data[8], data[9], data[10]);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::toQuaternion(Quaternion<real> &outQuaternion) const
{
    outQuaternion.fromMatrix4( (*this) );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
bool Matrix4<real>::toEuler(Euler<real>& eulerAngles, RotationOrder order) const
{
    return this->toMatrix3().toEuler(eulerAngles);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Vector3<real> Matrix4<real>::rotateVector(const Vector3<real> &vec) const
{
	Vector3<real> retVec(
        data[0] * this->x + data[1] * this->y + data[2]  * this->z,
        data[4] * this->x + data[5] * this->y + data[6]  * this->z,
        data[8] * this->x + data[9] * this->y + data[10] * this->z
        );
	return retVec;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real> Matrix4<real>::transpose() const
{
    return Matrix4<real>(
        data[0], data[4], data[ 8], data[12],
        data[1], data[5], data[ 9], data[13],
        data[2], data[6], data[10], data[14],
        data[3], data[7], data[11], data[15] );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::transposeInPlace()
{
    set(
        data[0], data[4], data[ 8], data[12],
        data[1], data[5], data[ 9], data[13],
        data[2], data[6], data[10], data[14],
        data[3], data[7], data[11], data[15] );
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real Matrix4<real>::determinant() const
{
    cout << "determinant" << endl;
    real a0 = data[ 0]*data[ 5] - data[ 1]*data[ 4];
    real a1 = data[ 0]*data[ 6] - data[ 2]*data[ 4];
    real a2 = data[ 0]*data[ 7] - data[ 3]*data[ 4];
    real a3 = data[ 1]*data[ 6] - data[ 2]*data[ 5];
    real a4 = data[ 1]*data[ 7] - data[ 3]*data[ 5];
    real a5 = data[ 2]*data[ 7] - data[ 3]*data[ 6];
    real b0 = data[ 8]*data[13] - data[ 9]*data[12];
    real b1 = data[ 8]*data[14] - data[10]*data[12];
    real b2 = data[ 8]*data[15] - data[11]*data[12];
    real b3 = data[ 9]*data[14] - data[10]*data[13];
    real b4 = data[ 9]*data[15] - data[11]*data[13];
    real b5 = data[10]*data[15] - data[11]*data[14];
    real det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
    return det;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real> Matrix4<real>::inverse() const
{
    Matrix4<real> inverseMat;

    real a0 = data[ 0]*data[ 5] - data[ 1]*data[ 4];
    real a1 = data[ 0]*data[ 6] - data[ 2]*data[ 4];
    real a2 = data[ 0]*data[ 7] - data[ 3]*data[ 4];
    real a3 = data[ 1]*data[ 6] - data[ 2]*data[ 5];
    real a4 = data[ 1]*data[ 7] - data[ 3]*data[ 5];
    real a5 = data[ 2]*data[ 7] - data[ 3]*data[ 6];
    real b0 = data[ 8]*data[13] - data[ 9]*data[12];
    real b1 = data[ 8]*data[14] - data[10]*data[12];
    real b2 = data[ 8]*data[15] - data[11]*data[12];
    real b3 = data[ 9]*data[14] - data[10]*data[13];
    real b4 = data[ 9]*data[15] - data[11]*data[13];
    real b5 = data[10]*data[15] - data[11]*data[14];
    real det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

    if (fabs(det) > Math<real>::EPSILON)
    {
        inverseMat.data[ 0] = + data[ 5]*b5 - data[ 6]*b4 + data[ 7]*b3;
        inverseMat.data[ 4] = - data[ 4]*b5 + data[ 6]*b2 - data[ 7]*b1;
        inverseMat.data[ 8] = + data[ 4]*b4 - data[ 5]*b2 + data[ 7]*b0;
        inverseMat.data[12] = - data[ 4]*b3 + data[ 5]*b1 - data[ 6]*b0;
        inverseMat.data[ 1] = - data[ 1]*b5 + data[ 2]*b4 - data[ 3]*b3;
        inverseMat.data[ 5] = + data[ 0]*b5 - data[ 2]*b2 + data[ 3]*b1;
        inverseMat.data[ 9] = - data[ 0]*b4 + data[ 1]*b2 - data[ 3]*b0;
        inverseMat.data[13] = + data[ 0]*b3 - data[ 1]*b1 + data[ 2]*b0;
        inverseMat.data[ 2] = + data[13]*a5 - data[14]*a4 + data[15]*a3;
        inverseMat.data[ 6] = - data[12]*a5 + data[14]*a2 - data[15]*a1;
        inverseMat.data[10] = + data[12]*a4 - data[13]*a2 + data[15]*a0;
        inverseMat.data[14] = - data[12]*a3 + data[13]*a1 - data[14]*a0;
        inverseMat.data[ 3] = - data[ 9]*a5 + data[10]*a4 - data[11]*a3;
        inverseMat.data[ 7] = + data[ 8]*a5 - data[10]*a2 + data[11]*a1;
        inverseMat.data[11] = - data[ 8]*a4 + data[ 9]*a2 - data[11]*a0;
        inverseMat.data[15] = + data[ 8]*a3 - data[ 9]*a1 + data[10]*a0;

        real invDet = ((real)1)/det;
        inverseMat.data[ 0] *= invDet;
        inverseMat.data[ 1] *= invDet;
        inverseMat.data[ 2] *= invDet;
        inverseMat.data[ 3] *= invDet;
        inverseMat.data[ 4] *= invDet;
        inverseMat.data[ 5] *= invDet;
        inverseMat.data[ 6] *= invDet;
        inverseMat.data[ 7] *= invDet;
        inverseMat.data[ 8] *= invDet;
        inverseMat.data[ 9] *= invDet;
        inverseMat.data[10] *= invDet;
        inverseMat.data[11] *= invDet;
        inverseMat.data[12] *= invDet;
        inverseMat.data[13] *= invDet;
        inverseMat.data[14] *= invDet;
        inverseMat.data[15] *= invDet;
    }
    else
    {
        inverseMat.set(
                (real)0, (real)0, (real)0, (real)0,
                (real)0, (real)0, (real)0, (real)0,
                (real)0, (real)0, (real)0, (real)0,
                (real)0, (real)0, (real)0, (real)0 );
    }

    return inverseMat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
Matrix4<real> Matrix4<real>::orthogonal() const
{
    Matrix4<real> m(*this);
    m.orthogonalInPlace();
    return m;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::orthogonalInPlace() //primaryAxis, secondaryAxis)
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
    real invLength = (real)1 / sqrt(data[0]*data[0] +
        data[1]*data[1] + data[2]*data[2]);

    data[0] *= invLength;
    data[1] *= invLength;
    data[2] *= invLength;

    // Compute q1.
    real dot0 = data[0]*data[4] + data[1]*data[5] +
        data[2]*data[6];

    data[4] -= dot0*data[0];
    data[5] -= dot0*data[1];
    data[6] -= dot0*data[2];

    invLength = (real)1 / sqrt(data[4]*data[4] +
        data[5]*data[5] + data[6]*data[6]);

    data[4] *= invLength;
    data[5] *= invLength;
    data[6] *= invLength;

    // compute q2
    real dot1 = data[4]*data[8] + data[5]*data[9] +
        data[6]*data[10];

    dot0 = data[0]*data[8] + data[1]*data[9] +
        data[2]*data[10];

    data[8]  -= dot0*data[0] + dot1*data[4];
    data[9]  -= dot0*data[1] + dot1*data[5];
    data[10] -= dot0*data[2] + dot1*data[6];

    invLength = (real)1 / sqrt(data[8]*data[8] +
        data[9]*data[9] + data[10]*data[10]);

    data[8]  *= invLength;
    data[9]  *= invLength;
    data[10] *= invLength;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::inverseInPlace()
{
   real value[16];

   real a0 = data[ 0]*data[ 5] - data[ 1]*data[ 4];
   real a1 = data[ 0]*data[ 6] - data[ 2]*data[ 4];
   real a2 = data[ 0]*data[ 7] - data[ 3]*data[ 4];
   real a3 = data[ 1]*data[ 6] - data[ 2]*data[ 5];
   real a4 = data[ 1]*data[ 7] - data[ 3]*data[ 5];
   real a5 = data[ 2]*data[ 7] - data[ 3]*data[ 6];
   real b0 = data[ 8]*data[13] - data[ 9]*data[12];
   real b1 = data[ 8]*data[14] - data[10]*data[12];
   real b2 = data[ 8]*data[15] - data[11]*data[12];
   real b3 = data[ 9]*data[14] - data[10]*data[13];
   real b4 = data[ 9]*data[15] - data[11]*data[13];
   real b5 = data[10]*data[15] - data[11]*data[14];
   real det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

   if (fabs(det) > Math<real>::EPSILON)
   {
       value[ 0] = + data[ 5]*b5 - data[ 6]*b4 + data[ 7]*b3;
       value[ 4] = - data[ 4]*b5 + data[ 6]*b2 - data[ 7]*b1;
       value[ 8] = + data[ 4]*b4 - data[ 5]*b2 + data[ 7]*b0;
       value[12] = - data[ 4]*b3 + data[ 5]*b1 - data[ 6]*b0;
       value[ 1] = - data[ 1]*b5 + data[ 2]*b4 - data[ 3]*b3;
       value[ 5] = + data[ 0]*b5 - data[ 2]*b2 + data[ 3]*b1;
       value[ 9] = - data[ 0]*b4 + data[ 1]*b2 - data[ 3]*b0;
       value[13] = + data[ 0]*b3 - data[ 1]*b1 + data[ 2]*b0;
       value[ 2] = + data[13]*a5 - data[14]*a4 + data[15]*a3;
       value[ 6] = - data[12]*a5 + data[14]*a2 - data[15]*a1;
       value[10] = + data[12]*a4 - data[13]*a2 + data[15]*a0;
       value[14] = - data[12]*a3 + data[13]*a1 - data[14]*a0;
       value[ 3] = - data[ 9]*a5 + data[10]*a4 - data[11]*a3;
       value[ 7] = + data[ 8]*a5 - data[10]*a2 + data[11]*a1;
       value[11] = - data[ 8]*a4 + data[ 9]*a2 - data[11]*a0;
       value[15] = + data[ 8]*a3 - data[ 9]*a1 + data[10]*a0;

       real invDet = ((real)1)/det;
       value[ 0] *= invDet;
       value[ 1] *= invDet;
       value[ 2] *= invDet;
       value[ 3] *= invDet;
       value[ 4] *= invDet;
       value[ 5] *= invDet;
       value[ 6] *= invDet;
       value[ 7] *= invDet;
       value[ 8] *= invDet;
       value[ 9] *= invDet;
       value[10] *= invDet;
       value[11] *= invDet;
       value[12] *= invDet;
       value[13] *= invDet;
       value[14] *= invDet;
       value[15] *= invDet;

       memcpy(data, value, 16*sizeof(real));
   }
   else
   {
    set(
        (real)0, (real)0, (real)0, (real)0,
        (real)0, (real)0, (real)0, (real)0,
        (real)0, (real)0, (real)0, (real)0,
        (real)0, (real)0, (real)0, (real)0 );
   }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix4<real>::setFromVectorToVector(const Vector3<real> &fromVec, const Vector3<real> &toVec)
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
                this->data[i*4+j] =  - c1*uvals[i]*uvals[j] - c2*vvals[i]*vvals[j] + c3*vvals[i]*uvals[j];
            }
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

        this->data[4] = hvxy + v.z;
        this->data[5] = e + h*v.y*v.y;
        this->data[6] = hvyz - v.x;

        this->data[8] = hvxz - v.y;
        this->data[9] = hvyz + v.x;
        this->data[10] = e + hvz*v.z;
    }
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix4<real>::lookAt(const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis, Axis secondaryAxis)
{
	this->lookAt(this->getPosition(), pointAt, normal, primaryAxis, secondaryAxis);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
void Matrix4<real>::lookAt(const Vector3<real> &pos, const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis, Axis secondaryAxis)
{
	Vector3<real> primary, secondary, terziary;
    
	primary = pointAt - pos;
    secondary = normal - pos;
	primary.normalizeInPlace();
	secondary.normalizeInPlace();

    /*
	real f = fabs( primary.dot(secondary) );
    if (f > 1.0-Math<real>::EPSILON)
        throw GMathError("Matrix4:\n\ttarget vector and up vector are perpendicular, impossible to create a matrix out of them."); */
    
	terziary = secondary.cross(primary);
    secondary = primary.cross(terziary);

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
			this->setAxisZ(-terziary);
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
        if (secondaryAxis == POSX || secondaryAxis == NEGX)
        {
            this->setAxisX(secondary);
			this->setAxisY(primary);
			this->setAxisZ(terziary);
        }
        else if (secondaryAxis == POSZ || secondaryAxis == NEGZ)
        {
            this->setAxisX(terziary);
			this->setAxisY(primary);
			this->setAxisZ(-secondary);
        }
    }
    else if (primaryAxis == POSZ || primaryAxis == NEGZ)
    {
        if (secondaryAxis == POSX || secondaryAxis == NEGX)
        {
            this->setAxisX(secondary);
			this->setAxisY(-terziary);
			this->setAxisZ(primary);
        }
        else if (secondaryAxis == POSY || secondaryAxis == NEGY)
        {
            this->setAxisX(terziary);
			this->setAxisY(secondary);
			this->setAxisZ(primary);
        }
    }

	this->setPosition(pos);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template<typename real>
Matrix4<real> Matrix4<real>::createLookAt(const Vector3<real> &pos, const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis, Axis secondaryAxis)
{
    Matrix4<real> mat;
    mat.lookAt(pos, pointAt, normal, primaryAxis, secondaryAxis);
    return mat;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
void Matrix4<real>::setFromAxisAngle(const Vector3<real> &axis, real angle)
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
    data[4] = k1ab-k3c;    data[5] = k1*sqr_b+k2; data[6] = k1bc+k3a;
    data[8] = k1ac+k3b;    data[9] = k1bc-k3a;    data[10] = k1*sqr_c+k2;
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
std::string Matrix4<real>::toString() const
{
    std::stringstream oss;
    oss << "gmath::Matrix4(" << data[ 0] << ", " << data[ 1] << ", " << data[ 2] << ", " << data[ 3] << std::endl;
    oss << "               " << data[ 4] << ", " << data[ 5] << ", " << data[ 6] << ", " << data[ 7] << std::endl;
    oss << "               " << data[ 8] << ", " << data[ 9] << ", " << data[10] << ", " << data[11] << std::endl;
    oss << "               " << data[12] << ", " << data[13] << ", " << data[14] << ", " << data[15] << ");";

    return oss.str();
}
/*-----------------------------------------------------------------------------------------------------------------*/
