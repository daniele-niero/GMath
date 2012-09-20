/* Copyright (c) 2012, Daniele Niero
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
			Vector3<real> operator - () const;
			Vector3<real> operator * (real scalar) const;
			Vector3<real> operator * (const Vector3<real> & other) const;
			Vector3<real> operator * (const Matrix3<real> &mat) const;
            Vector3<real> operator * (const Matrix4<real> &mat) const;
			Vector3<real> operator / (real scalar) const;
			Vector3<real> operator / (const Vector3<real> & other) const;

			/*------ Arithmetic updates ------*/
			void operator += (const Vector3<real> & other);
			void operator -= (const Vector3<real> & other);
			void operator *= (real scalar);
			void operator *= (const Vector3<real> & other);
            void operator *= (const Matrix3<real> &mat);
            void operator *= (const Matrix4<real> &mat);
			void operator /= (real scalar);
			void operator /= (const Vector3<real> & other);

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
			Vector3<real> crossNormalize(const Vector3<real> & other) const;
			void crossNormalizeInPlace(const Vector3<real> & other);

			/** Perform the dot product between this vector and the given vector */
			real dot(const Vector3<real> & other) const;

			/** Calculate the length of this vector */
			real length() const;
			real squaredLength() const;

			/** Find the distance between this vector and the given vector */
			real distance(const Vector3<real> & other) const;
			real squaredDistance(const Vector3<real> & other) const;

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

			/** interpolate between this vector and the given one. return a new vector */
			Vector3<real> linearInterpolate(const Vector3<real> & other, real weight) const;

			/** interpolate between this vector and the given one. At the end store the result on this vector */
			void linearInterpolateInPlace(const Vector3<real> & other, real weight);


			std::string toString() const;

			// Special Vectors.
			static const Vector3 XAXIS;
			static const Vector3 YAXIS;
			static const Vector3 ZAXIS;

			static const Vector3 N_XAXIS;
			static const Vector3 N_YAXIS;
			static const Vector3 N_ZAXIS;

			static const Vector3 ZERO;
	};

	#include "gmVector3.hpp"


	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;

};


#endif // GMVECTOR3_H
