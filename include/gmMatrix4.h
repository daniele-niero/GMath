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
    template <class TypeReal>
    class Matrix4
    {
        public:
            /*------ constructors ------*/
            Matrix4();
            Matrix4(TypeReal xx, TypeReal xy, TypeReal xz, TypeReal xw,
                    TypeReal yx, TypeReal yy, TypeReal yz, TypeReal yw,
                    TypeReal zx, TypeReal zy, TypeReal zz, TypeReal zw,
                    TypeReal px, TypeReal py, TypeReal pz, TypeReal pw);
            Matrix4(const Matrix4<TypeReal> &other);
            Matrix4(const Vector4<TypeReal> &row0,
                    const Vector4<TypeReal> &row1,
                    const Vector4<TypeReal> &row2,
                    const Vector4<TypeReal> &row3);
//          Matrix4(const TypeReal* list);

            /*------ properties ------*/
            TypeReal data[16];

            /** Pointer access for direct copying. */
            TypeReal* ptr();
            const TypeReal* ptr() const;

            /*------ coordinate access ------*/
            TypeReal operator[] (int i) const;
            TypeReal& operator[] (int i);

            /*------ Arithmetic operations ------*/
            Matrix4<TypeReal> operator + (const TypeReal &value) const;
            Matrix4<TypeReal> operator + (const Matrix4<TypeReal> &other) const;
            Matrix4<TypeReal> operator - (const TypeReal &value) const;
            Matrix4<TypeReal> operator - (const Matrix4<TypeReal> &other) const;
            Matrix4<TypeReal> operator / (const TypeReal &value) const;
            Matrix4<TypeReal> operator * (const TypeReal &value) const;
            Matrix4<TypeReal> operator * (const Matrix4<TypeReal> &other) const;
            Vector4<TypeReal> operator * (const Vector4<TypeReal> &vector) const;
            Vector3<TypeReal> operator * (const Vector3<TypeReal> &vector) const;

            /*------ Arithmetic updates ------*/
            void operator += (const TypeReal &value);
            void operator += (const Matrix4<TypeReal> &other);
            void operator -= (const TypeReal &value);
            void operator -= (const Matrix4<TypeReal> &other);
            void operator /= (const TypeReal &value);
            void operator *= (const TypeReal &value);
            void operator *= (const Matrix4<TypeReal> &other);

            /*------ Comparisons ------*/
            bool operator == (const Matrix4<TypeReal> &other) const;
            bool operator != (const Matrix4<TypeReal> &other) const;

            /*------ Assignment ------*/
            void operator = (const Matrix4<TypeReal> &other);

            /*------ methods ------*/
            void setToIdentity();
            void set(TypeReal xx, TypeReal xy, TypeReal xz, TypeReal xw,
                     TypeReal yx, TypeReal yy, TypeReal yz, TypeReal yw,
                     TypeReal zx, TypeReal zy, TypeReal zz, TypeReal zw,
                     TypeReal px, TypeReal py, TypeReal pz, TypeReal pw);

            void setPosition(const Vector3<TypeReal> &pos);
            void addPosition(const Vector3<TypeReal> &pos);
            void translate(const Vector3<TypeReal> &pos);
            Vector3<TypeReal> getPosition() const;

            void setRotation(const Matrix3<TypeReal>& rotationMatrix);
            Matrix3<TypeReal> getRotation() const;

            Matrix4<TypeReal> transpose() const;
            void transposeInPlace();

            /** The deterMINant of a matrix is a floating point value which is used to
                indicate whether the matrix has an inverse or not. If zero, then no inverse exists. */
            TypeReal determinant() const;

            Matrix4<TypeReal> inverse() const;
            void inverseInPlace();

//          Matrix4<TypeReal> orthogonal() const;
//          void orthogonalInPlace();

            Vector3<TypeReal> getScale() const;
            Matrix4<TypeReal> addScale(const Vector3<TypeReal> &scale);
            Matrix4<TypeReal> addScale(TypeReal sX, TypeReal sY, TypeReal sZ);
            void addScaleInPlace(const Vector3<TypeReal> &scale);
            void addScaleInPlace(TypeReal sX, TypeReal sY, TypeReal sZ);
            Matrix4<TypeReal> setScale(const Vector3<TypeReal> &scale);
            Matrix4<TypeReal> setScale(TypeReal sX, TypeReal sY, TypeReal sZ);
            void setScaleInPlace(const Vector3<TypeReal> &scale);
            void setScaleInPlace(TypeReal sX, TypeReal sY, TypeReal sZ);

//          void setFromEuler(const TypeReal& angleX, const TypeReal& angleY, const TypeReal& angleZ, RotationOrder order=XYZ);
//          void setFromEuler(const Euler<TypeReal> &rotation, RotationOrder order=XYZ);
//          static Matrix4<TypeReal> createFromEuler(const Euler<TypeReal> &rotation, RotationOrder order=XYZ);
//          static Matrix4<TypeReal> createFromEuler(const TypeReal& angleX, const TypeReal& angleY, const TypeReal& angleZ, RotationOrder order=XYZ);

            /* Remeber to take out scale first */
//          Euler<TypeReal> toEuler(RotationOrder order=XYZ);
//          bool toEuler(Euler<TypeReal>& eulerAngles, RotationOrder order=XYZ);

            /* Returns a rotation matrix that rotates one vector into another.

                The generated rotation matrix will rotate the vector _from into
                the vector to. _from and to must be unit vectors!

                This method is based on the code from:

                Tomas Moller, John Hughes
                Efficiently Building a Matrix to Rotate One Vector to Another
                Journal of Graphics Tools, 4(4):1-4, 1999
                http://www.acm.org/jgt/papers/MollerHughes99/ */
//          void setFromVectorToVector(const Vector3<TypeReal> &fromVec, const Vector3<TypeReal> &toVec);
//          static Matrix4<TypeReal> createFromVectorToVector(const Vector3<TypeReal> &fromVec, const Vector3<TypeReal> &toVec);

            /** Look from pos to target.
              *
              * The resulting transformation is a rotation Matrix where the primaryAxis points to target.
              * The secondaryAxis is as close as possible to the up vector. */
            void lookAt(const Vector3<TypeReal> &pointAt, const Vector3<TypeReal> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);
            static Matrix4<TypeReal> createLookAt(const Vector3<TypeReal> &pointAt, const Vector3<TypeReal> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);

            void setFromAxisAngle(const Vector3<TypeReal> &axis, TypeReal angle);
            static Matrix4<TypeReal> createFromAxisAngle(const Vector3<TypeReal> &axis, TypeReal angle);

            std::string toString() const;

            // Special Matrices.
            static const Matrix4 IDENTITY;
    };

    #include "gmMatrix4.hpp"


    typedef Matrix4<float> Matrix4f;
    typedef Matrix4<double> Matrix4d;
}

#endif // GMMATRIX4_H
