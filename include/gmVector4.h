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
#include "gmRoot.h"

using namespace std;

namespace gmath
{
	class Vector4
	{
	public:
		/*------ constructors ------*/
		Vector4();
		Vector4(double inX, double inY, double inZ, double inW);
		Vector4(const Vector4 & other);
		Vector4(const double* list);

		/*------ properties ------*/
		double x, y, z, w;

		/*------ coordinate access ------*/
		double operator[] (int i) const;
		double& operator[] (int i);

		/** Pointer access for direct copying. */
		double* data();
		const double* data() const;

		/*------ Arithmetic operations ------*/
		Vector4 operator + (const Vector4 & other) const;
		Vector4 operator - (const Vector4 & other) const;
		Vector4 operator - () const;
		Vector4 operator * (double scalar) const;
		Vector4 operator / (double scalar) const;

		/*------ Arithmetic updates ------*/
		Vector4& operator += (const Vector4 & other);
		Vector4& operator -= (const Vector4 & other);
		Vector4& operator *= (double scalar);
		Vector4& operator /= (double scalar);

		/*------ Arithmetic comparisons ------*/
		bool operator == (const Vector4 & other) const;
		bool operator != (const Vector4 & other) const;

		/*------ Arithmetic assignment ------*/
		void operator = (const Vector4 & other);

		/*------ methods ------*/

		/** Set the three properties (x, y, z, w), with the given arguments
			@param inX The wanted value for x
			@param inY The wanted value for y
			@param inZ The wanted value for z
			@param inW The wanted value for w */
		void set(double inX, double inY, double inZ, double inW);

		/** Perform the dot product between this vector and the given vector */
		double dot(const Vector4 & other) const;

		/** Calculate the length of this vector */
		double length() const;
		double squaredLength() const;

		Vector4 normalize() const;
		void normalizeInPlace();

		std::string toString() const;
	};
}

#endif // GMVECTOR4_H
