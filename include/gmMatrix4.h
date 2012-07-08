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

    /**
    Matrix class (3x3).
    [Xx, Xy, Xz]
    [Yx, Yy, Yz]
    [Zx, Zy, Zz]

    This class represents a 3x3 matrix that can be used to store
    rotations transformations.
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

            /*------ methods ------*/
            void setToIdentity();
            void set(real xx, real xy, real xz, real xw,
                     real yx, real yy, real yz, real yw,
                     real zx, real zy, real zz, real zw,
                     real px, real py, real pz, real pw);

            Vector3<real> getRow(unsigned int i) const;
            Vector4<real> getRow2(unsigned int i) const;
            void setRow(unsigned int i, const Vector3<real> &vec);
            void setRow(unsigned int i, const Vector4<real> &vec);

            void setPosition(const Vector3<real> &pos);
            void addPosition(const Vector3<real> &pos);
            /** Move the matrix accordingly to its axis, no the world axis */
            void translate(const Vector3<real> &pos);
            Vector3<real> getPosition() const;

            void setRotation(const Matrix3<real>& rotationMatrix);
            Matrix3<real> getRotation() const;

            Matrix4<real> transpose() const;
            void transposeInPlace();

            /** The determinant of a matrix is a floating point value which is used to
                indicate whether the matrix has an inverse or not. If zero, then no inverse exists. */
            real determinant() const;

            Matrix4<real> inverse() const;
            void inverseInPlace();

            Matrix4<real> orthogonal() const;
            void orthogonalInPlace();

            Vector3<real> getScale() const;
            Matrix4<real> addScale(const Vector3<real> &scale);
            Matrix4<real> addScale(real sX, real sY, real sZ);
            void addScaleInPlace(const Vector3<real> &scale);
            void addScaleInPlace(real sX, real sY, real sZ);
            Matrix4<real> setScale(const Vector3<real> &scale);
            Matrix4<real> setScale(real sX, real sY, real sZ);
            void setScaleInPlace(const Vector3<real> &scale);
            void setScaleInPlace(real sX, real sY, real sZ);

            void setFromEuler(const real& angleX, const real& angleY, const real& angleZ, RotationOrder order=XYZ);
            void setFromEuler(const Euler<real> &rotation, RotationOrder order=XYZ);
            static Matrix4<real> createFromEuler(const Euler<real> &rotation, RotationOrder order=XYZ);
            static Matrix4<real> createFromEuler(const real& angleX, const real& angleY, const real& angleZ, RotationOrder order=XYZ);

            /** Remember to take out scale first */
            Euler<real> toEuler(RotationOrder order=XYZ) const; 
            bool toEuler(Euler<real>& eulerAngles, RotationOrder order=XYZ) const;

            /* Returns a rotation matrix that rotates one vector into another.

                The generated rotation matrix will rotate the vector _from into
                the vector to. _from and to must be unit vectors!

                This method is based on the code from:

                Tomas Moller, John Hughes
                Efficiently Building a Matrix to Rotate One Vector to Another
                Journal of Graphics Tools, 4(4):1-4, 1999
                http://www.acm.org/jgt/papers/MollerHughes99/ */
//          void setFromVectorToVector(const Vector3<real> &fromVec, const Vector3<real> &toVec);
//          static Matrix4<real> createFromVectorToVector(const Vector3<real> &fromVec, const Vector3<real> &toVec);

            /** Look from pos to target.
              *
              * The resulting transformation is a rotation Matrix where the primaryAxis points to target.
              * The secondaryAxis is as close as possible to the up vector. */
            void lookAt(const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);
            static Matrix4<real> createLookAt(const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);

            void setFromAxisAngle(const Vector3<real> &axis, real angle);
            static Matrix4<real> createFromAxisAngle(const Vector3<real> &axis, real angle);

            std::string toString() const;

            // Special Matrices.
            static const Matrix4 IDENTITY;
    };

    #include "gmMatrix4.hpp"


    typedef Matrix4<float> Matrix4f;
    typedef Matrix4<double> Matrix4d;
}

#endif // GMMATRIX4_H
