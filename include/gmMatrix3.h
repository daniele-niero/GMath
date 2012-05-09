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


#ifndef GMMATRIX3_H
#define GMMATRIX3_H

#include "gmRoot.h"
#include "gmMath.h"
#include "gmVector3.h"
#include "gmEuler.h"

namespace gmath
{

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
            Matrix3(const real* list);

            /*------ properties ------*/
            real data[9];

            /** Pointer access for direct copying. */
            real* ptr();
            const real* ptr() const;

            /*------ coordinate access ------*/
            real operator[] (int i) const;
            real& operator[] (int i);

            /*------ Arithmetic operations ------*/
            Matrix3<real> operator + (real value) const;
            Matrix3<real> operator + (const Matrix3<real> &other) const;
            Matrix3<real> operator - (real value) const;
            Matrix3<real> operator - (const Matrix3<real> &other) const;
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

            Matrix3<real> transpose() const;
            void transposeInPlace();

            /** The deterMINant of a matrix is a floating point value which is used to
                indicate whether the matrix has an inverse or not. If zero, then no inverse exists. */
            real determinant() const;

            Matrix3<real> inverse() const;
            void inverseInPlace();

            Matrix3<real> orthogonal() const;
            void orthogonalInPlace();

            Vector3<real> getScale() const;
            Matrix3<real> addScale(const Vector3<real> &scale);
            Matrix3<real> addScale(real sX, real sY, real sZ);
            void addScaleInPlace(const Vector3<real> &scale);
            void addScaleInPlace(real sX, real sY, real sZ);
            Matrix3<real> setScale(const Vector3<real> &scale);
            Matrix3<real> setScale(real sX, real sY, real sZ);
            void setScaleInPlace(const Vector3<real> &scale);
            void setScaleInPlace(real sX, real sY, real sZ);
            static Matrix3<real> createScale(const Vector3<real> &scale);
            static Matrix3<real> createScale(real sX, real sY, real sZ);
            
            void setFromEuler(const real& angleX, const real& angleY, const real& angleZ, RotationOrder order=XYZ);
            void setFromEuler(const Euler<real> &rotation, RotationOrder order=XYZ);
            static Matrix3<real> createFromEuler(const Euler<real> &rotation, RotationOrder order=XYZ);
            static Matrix3<real> createFromEuler(const real& angleX, const real& angleY, const real& angleZ, RotationOrder order=XYZ);

            /** Remeber to take out scale first */
            Euler<real> toEuler(RotationOrder order=XYZ);
            bool toEuler(Euler<real>& eulerAngles, RotationOrder order=XYZ);

            /** Returns a rotation matrix that rotates one vector into another.

                The generated rotation matrix will rotate the vector _from into
                the vector to. _from and to must be unit vectors!

                This method is based on the code from:

                Tomas Moller, John Hughes
                Efficiently Building a Matrix to Rotate One Vector to Another
                Journal of Graphics Tools, 4(4):1-4, 1999
                http://www.acm.org/jgt/papers/MollerHughes99/ */
            void setFromVectorToVector(const Vector3<real> &fromVec, const Vector3<real> &toVec);
            static Matrix3<real> createFromVectorToVector(const Vector3<real> &fromVec, const Vector3<real> &toVec);

            /** Look from pos to target.

                The resulting transformation is a rotation Matrix where the primaryAxis points to target.
                The secondaryAxis is as close as possible to the up vector. */
            void lookAt(const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);
            static Matrix3<real> createLookAt(const Vector3<real> &pointAt, const Vector3<real> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);

            void setFromAxisAngle(const Vector3<real> &axis, real angle);
            static Matrix3<real> createFromAxisAngle(const Vector3<real> &axis, real angle);

            std::string toString() const;

            // Special Matrices.
            static const Matrix3 IDENTITY;
    };

    #include "gmMatrix3.hpp"


    typedef Matrix3<float> Matrix3f;
    typedef Matrix3<double> Matrix3d;
}

#endif // GMMATRIX3_H
