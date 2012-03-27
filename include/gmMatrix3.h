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
	class Matrix3
	{
		public:
			/*------ constructors ------*/
			Matrix3();
			Matrix3(TypeReal xx, TypeReal xy, TypeReal xz,
					TypeReal yx, TypeReal yy, TypeReal yz,
					TypeReal zx, TypeReal zy, TypeReal zz);
			Matrix3(const Matrix3<TypeReal> &other);
			Matrix3(const Vector3<TypeReal> &axisX,
					const Vector3<TypeReal> &axisY,
					const Vector3<TypeReal> &axisZ);
			Matrix3(const TypeReal* list);

			/*------ properties ------*/
			TypeReal data[9];

			/** Pointer access for direct copying. */
			TypeReal* ptr();
			const TypeReal* ptr() const;

			/*------ Arithmetic operations ------*/
			Matrix3<TypeReal> operator + (TypeReal value) const;
			Matrix3<TypeReal> operator + (const Matrix3<TypeReal> &other) const;
			Matrix3<TypeReal> operator - (TypeReal value) const;
			Matrix3<TypeReal> operator - (const Matrix3<TypeReal> &other) const;
			Matrix3<TypeReal> operator / (TypeReal value) const;
			Matrix3<TypeReal> operator * (TypeReal value) const;
			Matrix3<TypeReal> operator * (const Matrix3<TypeReal> &other) const;
			Vector3<TypeReal> operator * (const Vector3<TypeReal> &vector) const;

			/*------ Arithmetic updates ------*/
			void operator += (TypeReal value);
			void operator += (const Matrix3<TypeReal> &other);
			void operator -= (TypeReal value);
			void operator -= (const Matrix3<TypeReal> &other);
			void operator /= (TypeReal value);
			void operator *= (TypeReal value);
			void operator *= (const Matrix3<TypeReal> &other);

			/*------ Comparisons ------*/
			bool operator == (const Matrix3<TypeReal> &other) const;
			bool operator != (const Matrix3<TypeReal> &other) const;

			/*------ Assignment ------*/
			void operator = (const Matrix3<TypeReal> &other);

			/*------ methods ------*/
			void setToIdentity();
			void set(TypeReal xx, TypeReal xy, TypeReal xz,
					 TypeReal yx, TypeReal yy, TypeReal yz,
					 TypeReal zx, TypeReal zy, TypeReal zz);

			Matrix3<TypeReal> transpose() const;
			void transposeInPlace();

			/** The deterMINant of a matrix is a floating point value which is used to
			    indicate whether the matrix has an inverse or not. If zero, then no inverse exists. */
			TypeReal determinant() const;

			Matrix3<TypeReal> inverse() const;
			void inverseInPlace();

			Matrix3<TypeReal> orthogonal() const;
			void orthogonalInPlace();

			Vector3<TypeReal> getScale() const;
			Matrix3<TypeReal> addScale(const Vector3<TypeReal> &scale);
			Matrix3<TypeReal> addScale(TypeReal sX, TypeReal sY, TypeReal sZ);
			void addScaleInPlace(const Vector3<TypeReal> &scale);
			void addScaleInPlace(TypeReal sX, TypeReal sY, TypeReal sZ);
			Matrix3<TypeReal> setScale(const Vector3<TypeReal> &scale);
			Matrix3<TypeReal> setScale(TypeReal sX, TypeReal sY, TypeReal sZ);
			void setScaleInPlace(const Vector3<TypeReal> &scale);
			void setScaleInPlace(TypeReal sX, TypeReal sY, TypeReal sZ);
			static Matrix3<TypeReal> createScale(const Vector3<TypeReal> &scale);
			static Matrix3<TypeReal> createScale(TypeReal sX, TypeReal sY, TypeReal sZ);
			
			void setFromEuler(const TypeReal& angleX, const TypeReal& angleY, const TypeReal& angleZ, RotationOrder order=XYZ);
			void setFromEuler(const Euler<TypeReal> &rotation, RotationOrder order=XYZ);
			static Matrix3<TypeReal> createFromEuler(const Euler<TypeReal> &rotation, RotationOrder order=XYZ);
			static Matrix3<TypeReal> createFromEuler(const TypeReal& angleX, const TypeReal& angleY, const TypeReal& angleZ, RotationOrder order=XYZ);

			/** Remeber to take out scale first */
			Euler<TypeReal> toEuler(RotationOrder order=XYZ);
			bool toEuler(Euler<TypeReal>& eulerAngles, RotationOrder order=XYZ);

			/** Returns a rotation matrix that rotates one vector into another.

		        The generated rotation matrix will rotate the vector _from into
		        the vector to. _from and to must be unit vectors!

		        This method is based on the code from:

		        Tomas Moller, John Hughes
		        Efficiently Building a Matrix to Rotate One Vector to Another
		        Journal of Graphics Tools, 4(4):1-4, 1999
		        http://www.acm.org/jgt/papers/MollerHughes99/ */
			void setFromVectorToVector(const Vector3<TypeReal> &fromVec, const Vector3<TypeReal> &toVec);
			static Matrix3<TypeReal> createFromVectorToVector(const Vector3<TypeReal> &fromVec, const Vector3<TypeReal> &toVec);

			/** Look from pos to target.

				The resulting transformation is a rotation Matrix where the primaryAxis points to target.
				The secondaryAxis is as close as possible to the up vector. */
			void lookAt(const Vector3<TypeReal> &pointAt, const Vector3<TypeReal> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);
			static Matrix3<TypeReal> createLookAt(const Vector3<TypeReal> &pointAt, const Vector3<TypeReal> &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);

			void setFromAxisAngle(const Vector3<TypeReal> &axis, TypeReal angle);
			static Matrix3<TypeReal> createFromAxisAngle(const Vector3<TypeReal> &axis, TypeReal angle);

			std::string toString() const;

			// Special Matrices.
			static const Matrix3 IDENTITY;
	};

	#include "gmMatrix3.hpp"


	typedef Matrix3<float> Matrix3f;
	typedef Matrix3<double> Matrix3d;
}

#endif // GMMATRIX3_H
