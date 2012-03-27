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


/*------ constructors ------*/
template <class TypeReal>
Matrix4<TypeReal>::Matrix4()
{
	 data[0]=(TypeReal)1;  data[1]=(TypeReal)0;  data[2]=(TypeReal)0;  data[3]=(TypeReal)0;
	 data[4]=(TypeReal)0;  data[5]=(TypeReal)1;  data[6]=(TypeReal)0;  data[7]=(TypeReal)0;
	 data[8]=(TypeReal)0;  data[9]=(TypeReal)0; data[10]=(TypeReal)1; data[11]=(TypeReal)0;
	data[12]=(TypeReal)0; data[13]=(TypeReal)0; data[14]=(TypeReal)0; data[15]=(TypeReal)1;
}

template <class TypeReal>
Matrix4<TypeReal>::Matrix4(
    TypeReal xx, TypeReal xy, TypeReal xz, TypeReal xw,
	TypeReal yx, TypeReal yy, TypeReal yz, TypeReal yw,
	TypeReal zx, TypeReal zy, TypeReal zz, TypeReal zw,
	TypeReal px, TypeReal py, TypeReal pz, TypeReal pw)
{
	data[0]=xx;  data[1]=xy;  data[2]=xz;  data[3]=xw;
    data[4]=yx;  data[5]=yy;  data[6]=yz;  data[7]=yw;
    data[8]=zx;  data[9]=zy;  data[10]=zz; data[11]=zw;
    data[12]=px; data[13]=py; data[14]=pz; data[15]=pw;
}

template <class TypeReal>
Matrix4<TypeReal>::Matrix4(const Matrix4<TypeReal> & other)
{
	memcpy(data, other.data, 16*sizeof(TypeReal));
}

//template <class TypeReal>
//Matrix4<TypeReal>::Matrix4(
//	const Vector4<TypeReal> &row0,
//	const Vector4<TypeReal> &row1,
//	const Vector4<TypeReal> &row2,
//	const Vector4<TypeReal> &row3)
//{
//	memcpy(&data[0],  row0.ptr(), 4*sizeof(TypeReal));
//	memcpy(&data[4],  row1.ptr(), 4*sizeof(TypeReal));
//	memcpy(&data[8],  row2.ptr(), 4*sizeof(TypeReal));
//	memcpy(&data[12], row3.ptr(), 4*sizeof(TypeReal));
//}
//
//template <class TypeReal>
//Matrix4<TypeReal>::Matrix4(const TypeReal* list)
//{
//	memcpy(data, list, 16*sizeof(TypeReal));
//}




template <class TypeReal>
TypeReal* Matrix4<TypeReal>::ptr()
{
	return &data[0];
}

template <class TypeReal>
const TypeReal* Matrix4<TypeReal>::ptr() const
{
	return &data[0];
}



template <class TypeReal>
void Matrix4<TypeReal>::set(
    TypeReal xx, TypeReal xy, TypeReal xz, TypeReal xw,
	TypeReal yx, TypeReal yy, TypeReal yz, TypeReal yw,
	TypeReal zx, TypeReal zy, TypeReal zz, TypeReal zw,
	TypeReal px, TypeReal py, TypeReal pz, TypeReal pw)
{
    data[0]=xx;  data[1]=xy;  data[2]=xz;  data[3]=xw;
    data[4]=yx;  data[5]=yy;  data[6]=yz;  data[7]=yw;
    data[8]=zx;  data[9]=zy;  data[10]=zz; data[11]=zw;
    data[12]=px; data[13]=py; data[14]=pz; data[15]=pw;
}

template <class TypeReal>
void Matrix4<TypeReal>::setPosition(const Vector3<TypeReal> &pos)
{
	data[12] = pos.x;
	data[13] = pos.y;
	data[14] = pos.z;
}

template <class TypeReal>
void Matrix4<TypeReal>::addPosition(const Vector3<TypeReal> &pos)
{
	data[12] += pos.x;
	data[13] += pos.y;
	data[14] += pos.z;
}

template <class TypeReal>
void Matrix4<TypeReal>::translate (const Vector3<TypeReal> &pos)
{
    data[12] += pos.x * data[0] + pos.y * data[4] + pos.z * data[8];
    data[13] += pos.x * data[1] + pos.y * data[5] + pos.z * data[9];
    data[14] += pos.x * data[2] + pos.y * data[6] + pos.z * data[10];
    //data[12] += pos.x * data[3] + pos.y * data[4] + pos.z * data[8];
}

template <class TypeReal>
void Matrix4<TypeReal>::setToIdentity()
{
    data[0] =(TypeReal)1;  data[1]=(TypeReal)0;  data[2]=(TypeReal)0;  data[3]=(TypeReal)0;
    data[4] =(TypeReal)0;  data[5]=(TypeReal)1;  data[6]=(TypeReal)0;  data[7]=(TypeReal)0;
    data[8] =(TypeReal)0;  data[9]=(TypeReal)0; data[10]=(TypeReal)1; data[11]=(TypeReal)0;
    data[12]=(TypeReal)0; data[13]=(TypeReal)0; data[14]=(TypeReal)0; data[15]=(TypeReal)1;
}

template <class TypeReal>
Matrix4<TypeReal> Matrix4<TypeReal>::operator * (const Matrix4<TypeReal> &other) const
{
    const TypeReal* a = ptr();
    const TypeReal* b = other.ptr();
    Matrix4<TypeReal> retMatrix(
        a[0]*b[0] + a[1]*b[4] + a[2]*b[8]  + a[3]*b[12],
        a[0]*b[1] + a[1]*b[5] + a[2]*b[9]  + a[3]*b[13],
        a[0]*b[2] + a[1]*b[6] + a[2]*b[10] + a[3]*b[14],
        a[0]*b[3] + a[1]*b[7] + a[2]*b[11] + a[3]*b[15],

        a[4]*b[0] + a[5]*b[4] + a[6]*b[8]  + a[7]*b[12],
        a[4]*b[1] + a[5]*b[5] + a[6]*b[9]  + a[7]*b[13],
        a[4]*b[2] + a[5]*b[6] + a[6]*b[10] + a[7]*b[14],
        a[4]*b[3] + a[5]*b[7] + a[6]*b[11] + a[7]*b[15],

        a[8]*b[0] + a[9]*b[4] + a[10]*b[8]  + a[11]*b[12],
        a[8]*b[1] + a[9]*b[5] + a[10]*b[9]  +  a[11]*b[13],
        a[8]*b[2] + a[9]*b[6] + a[10]*b[10] + a[11]*b[14],
        a[8]*b[3] + a[9]*b[7] + a[10]*b[11] + a[11]*b[15],

        a[12]*b[0] + a[13]*b[4] + a[14]*b[8]  + a[15]*b[12],
        a[12]*b[1] + a[13]*b[5] + a[14]*b[9]  + a[15]*b[13],
        a[12]*b[2] + a[13]*b[6] + a[14]*b[10] + a[15]*b[14],
        a[12]*b[3] + a[13]*b[7] + a[14]*b[11] + a[15]*b[15]
        );
    return retMatrix;
}


template <class TypeReal>
void Matrix4<TypeReal>::operator *= (const Matrix4<TypeReal> &other)
{
    const TypeReal* a = &data[0];
    const TypeReal* b = &other.data[0];
    TypeReal c[16];

    c[0]  = a[0]*b[0] + a[1]*b[4] + a[2]*b[8],  a[3]*b[12];
    c[1]  = a[0]*b[1] + a[1]*b[5] + a[2]*b[9],  a[3]*b[13];
    c[2]  = a[0]*b[2] + a[1]*b[6] + a[2]*b[10], a[3]*b[14];
    c[3]  = a[0]*b[3] + a[1]*b[7] + a[2]*b[11], a[3]*b[15];

    c[4]  = a[4]*b[0] + a[5]*b[4] + a[6]*b[8],  a[7]*b[12];
    c[5]  = a[4]*b[1] + a[5]*b[5] + a[6]*b[9],  a[7]*b[13];
    c[6]  = a[4]*b[2] + a[5]*b[6] + a[6]*b[10], a[7]*b[14];
    c[7]  = a[4]*b[3] + a[5]*b[7] + a[6]*b[11], a[7]*b[15];

    c[8]  = a[8]*b[0] + a[9]*b[4] + a[10]*b[8],  a[11]*b[12];
    c[9]  = a[8]*b[1] + a[9]*b[5] + a[10]*b[9],  a[11]*b[13];
    c[10] = a[8]*b[2] + a[9]*b[6] + a[10]*b[10], a[11]*b[14];
    c[11] = a[8]*b[3] + a[9]*b[7] + a[10]*b[11], a[11]*b[15];

    c[12] = a[12]*b[0] + a[13]*b[4] + a[14]*b[8],  a[15]*b[12];
    c[13] = a[12]*b[1] + a[13]*b[5] + a[14]*b[9],  a[15]*b[13];
    c[14] = a[12]*b[2] + a[13]*b[6] + a[14]*b[10], a[15]*b[14];
    c[15] = a[12]*b[3] + a[13]*b[7] + a[14]*b[11], a[15]*b[15];

    set(c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15]);
}


/*------ Assignment ------*/
template <class TypeReal>
void Matrix4<TypeReal>::operator = (const Matrix4<TypeReal> &other)
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


//template <class TypeReal>
//TypeReal Matrix4<TypeReal>::determinant() const
//{
//	cout << "determinant" << endl;
//	TypeReal a0 = data[ 0]*data[ 5] - data[ 1]*data[ 4];
//    TypeReal a1 = data[ 0]*data[ 6] - data[ 2]*data[ 4];
//    TypeReal a2 = data[ 0]*data[ 7] - data[ 3]*data[ 4];
//    TypeReal a3 = data[ 1]*data[ 6] - data[ 2]*data[ 5];
//    TypeReal a4 = data[ 1]*data[ 7] - data[ 3]*data[ 5];
//    TypeReal a5 = data[ 2]*data[ 7] - data[ 3]*data[ 6];
//    TypeReal b0 = data[ 8]*data[13] - data[ 9]*data[12];
//    TypeReal b1 = data[ 8]*data[14] - data[10]*data[12];
//    TypeReal b2 = data[ 8]*data[15] - data[11]*data[12];
//    TypeReal b3 = data[ 9]*data[14] - data[10]*data[13];
//    TypeReal b4 = data[ 9]*data[15] - data[11]*data[13];
//    TypeReal b5 = data[10]*data[15] - data[11]*data[14];
//    TypeReal det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
//    return det;
//}


template <class TypeReal>
Matrix4<TypeReal> Matrix4<TypeReal>::inverse() const
{
	Matrix4<TypeReal> inverseMat;

    TypeReal a0 = data[ 0]*data[ 5] - data[ 1]*data[ 4];
    TypeReal a1 = data[ 0]*data[ 6] - data[ 2]*data[ 4];
    TypeReal a2 = data[ 0]*data[ 7] - data[ 3]*data[ 4];
    TypeReal a3 = data[ 1]*data[ 6] - data[ 2]*data[ 5];
    TypeReal a4 = data[ 1]*data[ 7] - data[ 3]*data[ 5];
    TypeReal a5 = data[ 2]*data[ 7] - data[ 3]*data[ 6];
    TypeReal b0 = data[ 8]*data[13] - data[ 9]*data[12];
    TypeReal b1 = data[ 8]*data[14] - data[10]*data[12];
    TypeReal b2 = data[ 8]*data[15] - data[11]*data[12];
    TypeReal b3 = data[ 9]*data[14] - data[10]*data[13];
    TypeReal b4 = data[ 9]*data[15] - data[11]*data[13];
    TypeReal b5 = data[10]*data[15] - data[11]*data[14];
    TypeReal det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

    if (fabs(det) > Math<TypeReal>::EPSILON)
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

        TypeReal invDet = ((TypeReal)1)/det;
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
    			(TypeReal)0, (TypeReal)0, (TypeReal)0, (TypeReal)0,
    			(TypeReal)0, (TypeReal)0, (TypeReal)0, (TypeReal)0,
    			(TypeReal)0, (TypeReal)0, (TypeReal)0, (TypeReal)0,
    			(TypeReal)0, (TypeReal)0, (TypeReal)0, (TypeReal)0 );
    }

    return inverseMat;
}

//template <class TypeReal>
//void Matrix4<TypeReal>::inverseInPlace()
//{
//    TypeReal value[16];
//
//    TypeReal a0 = data[ 0]*data[ 5] - data[ 1]*data[ 4];
//    TypeReal a1 = data[ 0]*data[ 6] - data[ 2]*data[ 4];
//    TypeReal a2 = data[ 0]*data[ 7] - data[ 3]*data[ 4];
//    TypeReal a3 = data[ 1]*data[ 6] - data[ 2]*data[ 5];
//    TypeReal a4 = data[ 1]*data[ 7] - data[ 3]*data[ 5];
//    TypeReal a5 = data[ 2]*data[ 7] - data[ 3]*data[ 6];
//    TypeReal b0 = data[ 8]*data[13] - data[ 9]*data[12];
//    TypeReal b1 = data[ 8]*data[14] - data[10]*data[12];
//    TypeReal b2 = data[ 8]*data[15] - data[11]*data[12];
//    TypeReal b3 = data[ 9]*data[14] - data[10]*data[13];
//    TypeReal b4 = data[ 9]*data[15] - data[11]*data[13];
//    TypeReal b5 = data[10]*data[15] - data[11]*data[14];
//    TypeReal det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
//
//    if (fabs(det) > Math<TypeReal>::EPSILON)
//    {
//        value[ 0] = + data[ 5]*b5 - data[ 6]*b4 + data[ 7]*b3;
//        value[ 4] = - data[ 4]*b5 + data[ 6]*b2 - data[ 7]*b1;
//        value[ 8] = + data[ 4]*b4 - data[ 5]*b2 + data[ 7]*b0;
//        value[12] = - data[ 4]*b3 + data[ 5]*b1 - data[ 6]*b0;
//        value[ 1] = - data[ 1]*b5 + data[ 2]*b4 - data[ 3]*b3;
//        value[ 5] = + data[ 0]*b5 - data[ 2]*b2 + data[ 3]*b1;
//        value[ 9] = - data[ 0]*b4 + data[ 1]*b2 - data[ 3]*b0;
//        value[13] = + data[ 0]*b3 - data[ 1]*b1 + data[ 2]*b0;
//        value[ 2] = + data[13]*a5 - data[14]*a4 + data[15]*a3;
//        value[ 6] = - data[12]*a5 + data[14]*a2 - data[15]*a1;
//        value[10] = + data[12]*a4 - data[13]*a2 + data[15]*a0;
//        value[14] = - data[12]*a3 + data[13]*a1 - data[14]*a0;
//        value[ 3] = - data[ 9]*a5 + data[10]*a4 - data[11]*a3;
//        value[ 7] = + data[ 8]*a5 - data[10]*a2 + data[11]*a1;
//        value[11] = - data[ 8]*a4 + data[ 9]*a2 - data[11]*a0;
//        value[15] = + data[ 8]*a3 - data[ 9]*a1 + data[10]*a0;
//
//        TypeReal invDet = ((TypeReal)1)/det;
//        value[ 0] *= invDet;
//        value[ 1] *= invDet;
//        value[ 2] *= invDet;
//        value[ 3] *= invDet;
//        value[ 4] *= invDet;
//        value[ 5] *= invDet;
//        value[ 6] *= invDet;
//        value[ 7] *= invDet;
//        value[ 8] *= invDet;
//        value[ 9] *= invDet;
//        value[10] *= invDet;
//        value[11] *= invDet;
//        value[12] *= invDet;
//        value[13] *= invDet;
//        value[14] *= invDet;
//        value[15] *= invDet;
//
//        memcpy(data, value, 16*sizeof(TypeReal));
//    }
//    else
//    {
//    	set(
//    		(TypeReal)0, (TypeReal)0, (TypeReal)0, (TypeReal)0,
//    		(TypeReal)0, (TypeReal)0, (TypeReal)0, (TypeReal)0,
//    		(TypeReal)0, (TypeReal)0, (TypeReal)0, (TypeReal)0,
//    		(TypeReal)0, (TypeReal)0, (TypeReal)0, (TypeReal)0 );
//    }
//}

template <class TypeReal>
void Matrix4<TypeReal>::setFromAxisAngle(const Vector3<TypeReal> &axis, TypeReal angle)
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
	data[4] = k1ab-k3c;    data[5] = k1*sqr_b+k2; data[6] = k1bc+k3a;
	data[8] = k1ac+k3b;    data[9] = k1bc-k3a;    data[10] = k1*sqr_c+k2;
}




template <class TypeReal>
std::string Matrix4<TypeReal>::toString() const
{
    char buffer[200];
    sprintf( buffer, "gmath::Matrix4(%f, %f, %f, %f,\n               %f, %f, %f, %f\n               %f, %f, %f, %f\n               %f, %f, %f, %f);",
					data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
    std::string str(buffer);
    return str;
}
