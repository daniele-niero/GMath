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


#ifndef GMVECTOR3_H
#define GMVECTOR3_H

#include <string>
#include <stdexcept>
#include <math.h>
#include <iostream>
#include "gmRoot.h"
#include "gmMath.h"

using namespace std;

namespace gmath
{
	// Matrices forward declaration
	template <class TypeReal>
	class Matrix3;

    template <class TypeReal>
    class Matrix4;

	/**
	Three-dimensional vector.

	This class can be used to represent points, vectors, normals
	or even colors. The usual vector operations are available.
	*/
	template <class TypeReal>
	class Vector3
	{
		public:
			/*------ constructors ------*/
			Vector3();
			Vector3(TypeReal inX, TypeReal inY, TypeReal inZ);
			Vector3(const Vector3<TypeReal> & other);
			Vector3(const TypeReal* list);

			/*------ properties ------*/
			TypeReal x, y, z;

			/** Pointer access for direct copying. */
			TypeReal* ptr();
			const TypeReal* ptr() const;

			/*------ coordinate access ------*/
			TypeReal operator[] (int i) const;
			TypeReal& operator[] (int i);

			/*------ Arithmetic operations ------*/
			Vector3<TypeReal> operator + (const Vector3<TypeReal> & other) const;
			Vector3<TypeReal> operator - (const Vector3<TypeReal> & other) const;
			Vector3<TypeReal> operator * (TypeReal scalar) const;
			Vector3<TypeReal> operator * (const Matrix3<TypeReal> &mat) const;
            Vector3<TypeReal> operator * (const Matrix4<TypeReal> &mat) const;
			Vector3<TypeReal> operator / (TypeReal scalar) const;

			/*------ Arithmetic updates ------*/
			void operator += (const Vector3<TypeReal> & other);
			void operator -= (const Vector3<TypeReal> & other);
			void operator *= (TypeReal scalar);
			void operator /= (TypeReal scalar);

			/*------ Arithmetic comparisons ------*/
			bool operator == (const Vector3<TypeReal> & other) const;
			bool operator != (const Vector3<TypeReal> & other) const;

			/*------ Arithmetic assignment ------*/
			void operator = (const Vector3<TypeReal> & other);

			/*------ methods ------*/

			/** Set the three properties (x, y, z), with the given arguments
			    @param inX The wanted value for x
			    @param inY The wanted value for y
			    @param inZ The wanted value for z */
			void set(TypeReal inX, TypeReal inY, TypeReal inZ);

			/** return a Vector3 that is the exact copy of this one */
			Vector3<TypeReal> duplicate() const;

			/** Perform the cross product between this vector and the given vector */
			Vector3<TypeReal> cross(const Vector3<TypeReal> & other) const;
			void crossInPlace(const Vector3<TypeReal> & other);

			/** Perform the cross product between this vector and the given vector,
			 *  and always return a normalised vector.
			 *  This function is useful to reduce lines of code. */
			Vector3<TypeReal> crossNormalized(const Vector3<TypeReal> & other) const;

			/** Perform the dot product between this vector and the given vector */
			TypeReal dot(const Vector3<TypeReal> & other) const;

			/** Calculate the length of this vector */
			TypeReal length() const;
			TypeReal squaredLength() const;

			/** Find the distance between this vector and the given vector */
			TypeReal distance(const Vector3<TypeReal> & other) const;

			Vector3<TypeReal> normalize() const;
			void normalizeInPlace();

			/** Return angle (in radians) between this vector and the given vector.
			    @note: Remember to normalize the vectors before to call this method. */
			TypeReal angle(const Vector3<TypeReal> & other) const;

			/** Return the reflection to a surface.
			    @param normal is The Vector3 which represent the surface normal.
			                  Note that normal should be normalized */
			Vector3<TypeReal> reflect(const Vector3<TypeReal> & normal) const;

			/** Reflect this vector to a surface.
				@param normal is The Vector3 which represent the surface normal.
						      Note that normal should be normalized */
			void reflectInPlace(const Vector3<TypeReal> & normal);

			/** Return the transmitted vector.
			    If the returned vector is zero then there is no transmitted light because
	        	of total internal reflection.
	        	@param normal The Vector3 which represent the surface normal.
	        	              Note that normal should be normalized
	        	@param eta The relative index of refraction. */
			Vector3<TypeReal> refract(const Vector3<TypeReal> & normal, TypeReal eta) const;

			/** Transmit this vector.
				If the returned vector is zero then there is no transmitted light because
				of total internal reflection.
				@param normal The Vector3 which represent the surface normal.
							  Note that normal should be normalized
				@param eta The relative index of refraction. */
			void refractInPlace(const Vector3<TypeReal> & normal, TypeReal eta);

			std::string toString() const;

			// Special Vectors.
			static const Vector3 XAXIS;
			static const Vector3 YAXIS;
			static const Vector3 ZAXIS;

			static const Vector3 N_XAXIS;
			static const Vector3 N_YAXIS;
			static const Vector3 N_ZAXIS;

	};

	#include "gmVector3.hpp"


	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;

};


#endif // GMVECTOR3_H
