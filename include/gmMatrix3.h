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


#ifndef GMMATRIX3_H
#define GMMATRIX3_H

#include "gmRoot.h"
#include "gmMath.h"
#include "gmVector3.h"
#include "gmEuler.h"

namespace gmath
{
// Quaternion forward declaration
template <typename real>
class Quaternion;

/** Matrix class (3x3). @n
        [Xx, Xy, Xz] @n
        [Yx, Yy, Yz] @n
        [Zx, Zy, Zz] @n

    This class represents a 3x3 matrix that can be used to store
    rotations transformations. */
template <typename real>
class Matrix3
{
public:
    /*------ constructors ------*/
    Matrix3();
    Matrix3(real xx, real xy, real xz,
            real yx, real yy, real yz,
            real zx, real zy, real zz);
    Matrix3(const Matrix3<real> &other);
    Matrix3(const Vector3<real> &axisX,
            const Vector3<real> &axisY,
            const Vector3<real> &axisZ);
    Matrix3(const Quaternion<real>& quat);
    Matrix3(const real* list);

    /*------ properties ------*/
    real data[9];

    /** Pointer access for direct copying. */
    real* ptr();
    const real* ptr() const;

    /*------ coordinate access ------*/
    real operator[] (int i) const;
    real &operator[] (int i);
    real operator() (int row, int col) const;
    real &operator() (int row, int col);

    /*------ Arithmetic operations ------*/
    Matrix3<real> operator - ();
    Matrix3<real> operator - (real value) const;
    Matrix3<real> operator - (const Matrix3<real> &other) const;
    Matrix3<real> operator + (real value) const;
    Matrix3<real> operator + (const Matrix3<real> &other) const;
    Matrix3<real> operator / (real value) const;
    Matrix3<real> operator * (real value) const;
    Matrix3<real> operator * (const Matrix3<real> &other) const;

    /*------ Arithmetic updates ------*/
    void operator += (real value);
    void operator += (const Matrix3<real> &other);
    void operator -= (real value);
    void operator -= (const Matrix3<real> &other);
    void operator /= (real value);
    void operator *= (real value);
    void operator *= (const Matrix3<real> &other);

    /*------ Comparisons ------*/
    bool operator == (const Matrix3<real> &other) const;
    bool operator != (const Matrix3<real> &other) const;

    /*------ Assignment ------*/
    void operator = (const Matrix3<real> &other);

    /*------ methods ------*/
    void setToIdentity();
    void set(real xx, real xy, real xz,
             real yx, real yy, real yz,
             real zx, real zy, real zz);

    Vector3<real> getRow(unsigned int i) const;
    void setRow(unsigned int i, const Vector3<real> &vec);

	Vector3<real> getAxisX() const;
	Vector3<real> getAxisY() const;
	Vector3<real> getAxisZ() const;
	void setAxisX(const Vector3<real>& vec);
	void setAxisY(const Vector3<real>& vec);
	void setAxisZ(const Vector3<real>& vec);

    void setScale(const Vector3<real> &scale);
    void setScale(real sX, real sY, real sZ);
    void addScale(const Vector3<real> &scale);
    void addScale(real sX, real sY, real sZ);
    Vector3<real> getScale() const;

    /** Remember to take out scale first */
	void fromQuaternion(const Quaternion<real>& rotationQuat);
    Quaternion<real> toQuaternion() const;
    void toQuaternion(Quaternion<real> &outQuaternion) const;

    void fromEuler(const real& angleX, const real& angleY, const real& angleZ, RotationOrder order=XYZ);
    void fromEuler(const Euler<real> &rotation, RotationOrder order=XYZ);
    Euler<real> toEuler(RotationOrder order=XYZ) const;
    void toEuler(Euler<real>& euler, RotationOrder order=XYZ) const;

    Matrix3<real> transpose() const;
    void transposeInPlace();

    /** The deterMINant of a matrix is a floating point value which is used to
        indicate whether the matrix has an inverse or not. If zero, then no inverse exists. */
    real determinant() const;

    Matrix3<real> inverse() const;
    void inverseInPlace();

    Matrix3<real> orthogonal() const;
    void orthogonalInPlace();
    
    /** Returns a rotation matrix that rotates one vector into another.

        The generated rotation matrix will rotate the vector _from into
        the vector to. _from and to must be unit vectors!

        This method is based on the code from:

        Tomas Moller, John Hughes
        Efficiently Building a Matrix to Rotate One Vector to Another
        Journal of Graphics Tools, 4(4):1-4, 1999
        http://www.acm.org/jgt/papers/MollerHughes99/ */
    void fromVectorToVector(const Vector3<real> &fromVec, const Vector3<real> &toVec);
    void fromAxisAngle(const Vector3<real> &axis, real angle);

    /** Look from pos to target.

        The resulting transformation is a rotation Matrix where the primaryAxis points to target.
        The secondaryAxis is as close as possible to the up vector. */
    void lookAt(const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);
    static Matrix3<real> createLookAt(const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);

    std::string toString() const;

    // Special Matrices.
    static const Matrix3 IDENTITY;
};

#include "gmMatrix3.hpp"


typedef Matrix3<float> Matrix3f;
typedef Matrix3<double> Matrix3d;
}

#endif // GMMATRIX3_H
