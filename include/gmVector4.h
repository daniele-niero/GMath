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

#ifndef GMVECTOR4_H
#define GMVECTOR4_H

#include <string>
#include <stdexcept>
#include <math.h>
#include "gmMath.h"

using namespace std;

namespace gmath
{

	template<typename real>
	class Vector4
	{
	public:
		/*------ constructors ------*/
		Vector4();
		Vector4(real inX, real inY, real inZ, real inW);
		Vector4(const Vector4<real> & other);
		Vector4(const real* list);

		/*------ properties ------*/
		real x, y, z, w;

		/*------ coordinate access ------*/
		real operator[] (int i) const;
		real& operator[] (int i);

		/** Pointer access for direct copying. */
		real* ptr();
		const real* ptr() const;

		/*------ Arithmetic operations ------*/
		Vector4<real> operator + (const Vector4<real> & other) const;
		Vector4<real> operator - (const Vector4<real> & other) const;
		Vector4<real> operator - () const;
		Vector4<real> operator * (real scalar) const;
		Vector4<real> operator / (real scalar) const;

		/*------ Arithmetic updates ------*/
		void operator += (const Vector4<real> & other);
		void operator -= (const Vector4<real> & other);
		void operator *= (real scalar);
		void operator /= (real scalar);

		/*------ Arithmetic comparisons ------*/
		bool operator == (const Vector4<real> & other) const;
		bool operator != (const Vector4<real> & other) const;

		/*------ Arithmetic assignment ------*/
		void operator = (const Vector4<real> & other);

		/*------ methods ------*/

		/** Set the three properties (x, y, z, w), with the given arguments
			@param inX The wanted value for x
			@param inY The wanted value for y
			@param inZ The wanted value for z
			@param inW The wanted value for w */
		void set(real inX, real inY, real inZ, real inW);

		/** Perform the dot product between this vector and the given vector */
		real dot(const Vector4<real> & other) const;

		/** Calculate the length of this vector */
		real length() const;
		real squaredLength() const;

		Vector4<real> normalize() const;
		void normalizeInPlace();

		std::string toString() const;
	};

	#include "gmVector4.hpp"

	typedef Vector4<float> Vector4f;
	typedef Vector4<double> Vector4d;
}

#endif // GMVECTOR4_H
