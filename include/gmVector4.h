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

	template<class TypeReal>
	class Vector4
	{
	public:
		/*------ constructors ------*/
		Vector4();
		Vector4(TypeReal inX, TypeReal inY, TypeReal inZ, TypeReal inW);
		Vector4(const Vector4<TypeReal> & other);
		Vector4(const TypeReal* list);

		/*------ properties ------*/
		TypeReal x, y, z, w;

		/*------ coordinate access ------*/
		TypeReal operator[] (int i) const;
		TypeReal& operator[] (int i);

		/** Pointer access for direct copying. */
		TypeReal* ptr();
		const TypeReal* ptr() const;

		/*------ Arithmetic operations ------*/
		Vector4<TypeReal> operator + (const Vector4<TypeReal> & other) const;
		Vector4<TypeReal> operator - (const Vector4<TypeReal> & other) const;
		Vector4<TypeReal> operator * (TypeReal scalar) const;
		Vector4<TypeReal> operator / (TypeReal scalar) const;

		/*------ Arithmetic updates ------*/
		void operator += (const Vector4<TypeReal> & other);
		void operator -= (const Vector4<TypeReal> & other);
		void operator *= (TypeReal scalar);
		void operator /= (TypeReal scalar);

		/*------ Arithmetic comparisons ------*/
		bool operator == (const Vector4<TypeReal> & other) const;
		bool operator != (const Vector4<TypeReal> & other) const;

		/*------ Arithmetic assignment ------*/
		void operator = (const Vector4<TypeReal> & other);

		/*------ methods ------*/

		/** Set the three properties (x, y, z), with the given arguments
			@param inX The wanted value for x
			@param inY The wanted value for y
			@param inZ The wanted value for z
			@param inW The wanted value for w */
		void set(TypeReal inX, TypeReal inY, TypeReal inZ, TypeReal inW);

		/** return a Vector3 that is the exact copy of this one */
		Vector4<TypeReal> duplicate() const;

		/** Perform the dot product between this vector and the given vector */
		TypeReal dot(const Vector4<TypeReal> & other) const;

		/** Calculate the length of this vector */
		TypeReal length() const;
		TypeReal squaredLength() const;

		Vector4<TypeReal> normalize() const;
		void normalizeInPlace();

		std::string toString() const;
	};

	#include "gmVector4.hpp"

	typedef Vector4<float> Vector4f;
	typedef Vector4<double> Vector4d;
}

#endif // GMVECTOR4_H
