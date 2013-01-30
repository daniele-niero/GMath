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


#ifndef GMMATRIX4_H
#define GMMATRIX4_H

#include "gmRoot.h"
#include "gmMath.h"
#include "gmVector3.h"
#include "gmVector4.h"
#include "gmMatrix3.h"
#include "gmEuler.h"

namespace gmath
{

	// Quaternion forward declaration
	template <typename real>
	class Quaternion;

/**
Matrix class (4x4).
[Xx, Xy, Xz, Xw,]
[Yx, Yy, Yz, Yw,]
[Zx, Zy, Zz, Zw,]
[Px, Py, Pz, Pw]

This class represents a 4x4 matrix that can be used to store transformations.
This matrix is ROW MAJOR.
*/
template <typename real>
class Matrix4
{
public:
    /*------ constructors ------*/
    Matrix4();
    Matrix4(real xx, real xy, real xz, real xw,
            real yx, real yy, real yz, real yw,
            real zx, real zy, real zz, real zw,
            real px, real py, real pz, real pw);

    Matrix4(const Matrix4<real> &other);

    Matrix4(const Vector4<real> &row0,
            const Vector4<real> &row1,
            const Vector4<real> &row2,
            const Vector4<real> &row3);

    Matrix4(const Vector3<real> &row0,
            const Vector3<real> &row1,
            const Vector3<real> &row2,
            const Vector3<real> &row3);

    Matrix4(const Vector3<real> &row0,
            const Vector3<real> &row1,
            const Vector3<real> &row2);

    Matrix4(const Quaternion<real>& quat);
    Matrix4(const Quaternion<real>& quat, const Vector3<real>& pos);

    Matrix4(const real* list);

    /*------ properties ------*/
    real data[16];

    /** Pointer access for direct copying. */
    real* ptr();
    const real* ptr() const;

    /*------ coordinate access ------*/
    real operator[] (int i) const;
    real &operator[] (int i);
    real operator() (int row, int col) const;
    real &operator() (int row, int col);

    /*------ Arithmetic operations ------*/
    Matrix4<real> operator + (const real &value) const;
    Matrix4<real> operator + (const Matrix4<real> &other) const;
    Matrix4<real> operator - (const real &value) const;
    Matrix4<real> operator - (const Matrix4<real> &other) const;
    Matrix4<real> operator / (const real &value) const;
    Matrix4<real> operator * (const real &value) const;
    Matrix4<real> operator * (const Matrix4<real> &other) const;

    /*------ Arithmetic updates ------*/
    void operator += (const real &value);
    void operator += (const Matrix4<real> &other);
    void operator -= (const real &value);
    void operator -= (const Matrix4<real> &other);
    void operator /= (const real &value);
    void operator *= (const real &value);
    void operator *= (const Matrix4<real> &other);

    /*------ Comparisons ------*/
    bool operator == (const Matrix4<real> &other) const;
    bool operator != (const Matrix4<real> &other) const;

    /*------ Assignment ------*/
    void operator = (const Matrix4<real> &other);

    /*------ Sets and Gets ------*/
    void setToIdentity();
    void set(real xx, real xy, real xz, real xw,
             real yx, real yy, real yz, real yw,
             real zx, real zy, real zz, real zw,
             real px, real py, real pz, real pw);

    Vector3<real> getRow(unsigned int i) const;
    Vector4<real> getRow2(unsigned int i) const;
    void setRow(unsigned int i, const Vector3<real> &vec);
    void setRow(unsigned int i, const Vector4<real> &vec);
    
    Vector3<real> getAxisX() const;
    Vector3<real> getAxisY() const;
    Vector3<real> getAxisZ() const;
    
    void setAxisX(const Vector3<real> &vec);
    void setAxisY(const Vector3<real> &vec);
    void setAxisZ(const Vector3<real> &vec);

    void setPosition(const Vector3<real> &pos);
    void setPosition(real inX, real inY, real inZ);
    void addPosition(const Vector3<real> &pos);
    void addPosition(real inX, real inY, real inZ);
    /** Move the matrix accordingly to its axis, no the world axis */
    void translate(const Vector3<real> &pos);
    void translate(real inX, real inY, real inZ);
    Vector3<real> getPosition() const;

    void setRotation(const Matrix3<real>& rotationMatrix);
    void setRotation(const Quaternion<real>& rotationQuat);
    void setRotation(const Euler<real> &rotation, RotationOrder order=XYZ);
    void setRotation(real angleX, real angleY, real angleZ, RotationOrder order=XYZ);

    void setScale(const Vector3<real> &scale);
    void setScale(real sX, real sY, real sZ);
    void addScale(const Vector3<real> &scale);
    void addScale(real sX, real sY, real sZ);
    Vector3<real> getScale() const;

    /** Remember to take out scale first */
    Matrix3<real> toMatrix3() const;
    Quaternion<real> toQuaternion() const;
    Euler<real> toEuler(RotationOrder order=XYZ) const; 
    void toMatrix3(Matrix3<real> &outMatrix3) const;
    void toQuaternion(Quaternion<real> &outQuaternion) const;
    bool toEuler(Euler<real> &outEuler, RotationOrder order=XYZ) const;

    Vector3<real> rotateVector(const Vector3<real> &vec) const;

    Matrix4<real> transpose() const;
    void transposeInPlace();

    /** The determinant of a matrix is a floating point value which is used to
        indicate whether the matrix has an inverse or not. If zero, then no inverse exists. */
    real determinant() const;

    Matrix4<real> inverse() const;
    void inverseInPlace();

    Matrix4<real> orthogonal() const;
    void orthogonalInPlace();


    /* Returns a rotation matrix that rotates one vector into another.

        The generated rotation matrix will rotate the vector _from into
        the vector to. _from and to must be unit vectors!

        This method is based on the code from:

        Tomas Moller, John Hughes
        Efficiently Building a Matrix to Rotate One Vector to Another
        Journal of Graphics Tools, 4(4):1-4, 1999
        http://www.acm.org/jgt/papers/MollerHughes99/ */
    void setFromVectorToVector(const Vector3<real> &fromVec, const Vector3<real> &toVec);

    /** Look from pos to target.
      *
      * The resulting transformation is a rotation Matrix where the primaryAxis points to target.
      * The secondaryAxis is as close as possible to the up vector. */
    void lookAt(const Vector3<real> &pos, const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);
    // Like the previous lookAt but this one takes the position from the matrix itself
    void lookAt(const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);
    static Matrix4<real> createLookAt(const Vector3<real> &pos, const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);

    void setFromAxisAngle(const Vector3<real> &axis, real angle);

    std::string toString() const;

    // Special Matrices.
    static const Matrix4 IDENTITY;
};

#include "gmMatrix4.hpp"


typedef Matrix4<float> Matrix4f;
typedef Matrix4<double> Matrix4d;

}

#endif // GMMATRIX4_H
