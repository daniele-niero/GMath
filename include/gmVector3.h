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
	template <typename real>
	class Matrix3;

    template <typename real>
    class Matrix4;

	/**
	Three-dimensional vector.

	This class can be used to represent points, vectors, normals
	or even colors. The usual vector operations are available.
	*/
	template <typename real>
	class Vector3
	{
		public:
			/*------ constructors ------*/
			Vector3();
			Vector3(real inX, real inY, real inZ);
			Vector3(const Vector3<real> & other);
			Vector3(const real* list);

			/*------ properties ------*/
			real x, y, z;

			/** Pointer access for direct copying. */
			real* ptr();
			const real* ptr() const;

			/*------ coordinate access ------*/
			real operator[] (int i) const;
			real& operator[] (int i);

			/*------ Arithmetic operations ------*/
			Vector3<real> operator + (const Vector3<real> & other) const;
			Vector3<real> operator - (const Vector3<real> & other) const;
			Vector3<real> operator * (real scalar) const;
			Vector3<real> operator * (const Matrix3<real> &mat) const;
            Vector3<real> operator * (const Matrix4<real> &mat) const;
			Vector3<real> operator / (real scalar) const;

			/*------ Arithmetic updates ------*/
			void operator += (const Vector3<real> & other);
			void operator -= (const Vector3<real> & other);
			void operator *= (real scalar);
            void operator *= (const Matrix3<real> &mat);
            void operator *= (const Matrix4<real> &mat);
			void operator /= (real scalar);

			/*------ Arithmetic comparisons ------*/
			bool operator == (const Vector3<real> & other) const;
			bool operator != (const Vector3<real> & other) const;

			/*------ Arithmetic assignment ------*/
			void operator = (const Vector3<real> & other);

			/*------ methods ------*/

			/** Set the three properties (x, y, z), with the given arguments
			    @param inX The wanted value for x
			    @param inY The wanted value for y
			    @param inZ The wanted value for z */
			void set(real inX, real inY, real inZ);

			/** return a Vector3 that is the exact copy of this one */
			Vector3<real> duplicate() const;

			/** Perform the cross product between this vector and the given vector */
			Vector3<real> cross(const Vector3<real> & other) const;
			void crossInPlace(const Vector3<real> & other);

			/** Perform the cross product between this vector and the given vector,
			 *  and always return a normalised vector.
			 *  This function is useful to reduce lines of code. */
			Vector3<real> crossNormalized(const Vector3<real> & other) const;

			/** Perform the dot product between this vector and the given vector */
			real dot(const Vector3<real> & other) const;

			/** Calculate the length of this vector */
			real length() const;
			real squaredLength() const;

			/** Find the distance between this vector and the given vector */
			real distance(const Vector3<real> & other) const;

			Vector3<real> normalize() const;
			void normalizeInPlace();

			/** Return angle (in radians) between this vector and the given vector.
			    @note: Remember to normalize the vectors before to call this method. */
			real angle(const Vector3<real> & other) const;

			/** Return the reflection to a surface.
			    @param normal is The Vector3 which represent the surface normal.
			                  Note that normal should be normalized */
			Vector3<real> reflect(const Vector3<real> & normal) const;

			/** Reflect this vector to a surface.
				@param normal is The Vector3 which represent the surface normal.
						      Note that normal should be normalized */
			void reflectInPlace(const Vector3<real> & normal);

			/** Return the transmitted vector.
			    If the returned vector is zero then there is no transmitted light because
	        	of total internal reflection.
	        	@param normal The Vector3 which represent the surface normal.
	        	              Note that normal should be normalized
	        	@param eta The relative index of refraction. */
			Vector3<real> refract(const Vector3<real> & normal, real eta) const;

			/** Transmit this vector.
				If the returned vector is zero then there is no transmitted light because
				of total internal reflection.
				@param normal The Vector3 which represent the surface normal.
							  Note that normal should be normalized
				@param eta The relative index of refraction. */
			void refractInPlace(const Vector3<real> & normal, real eta);

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
