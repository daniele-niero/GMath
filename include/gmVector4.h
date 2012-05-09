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

		/** return a Vector3 that is the exact copy of this one */
		Vector4<real> duplicate() const;

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
