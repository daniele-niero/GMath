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


#ifndef GMEULER_H
#define GMEULER_H

#include "gmRoot.h"
#include "gmMath.h"
#include "gmVector3.h"

namespace gmath
{

	template <class TypeReal>
	class Euler
	{
		public:
			Euler();
			Euler(const Euler<TypeReal>& other);
			Euler(const TypeReal inX, const TypeReal inY, const TypeReal inZ);
			Euler(const Vector3<TypeReal>& vec);

			TypeReal x, y, z;

			/*------ coordinate access ------*/
			TypeReal operator[] (int i) const;
			TypeReal& operator[] (int i);

			/*------ Comparisons ------*/
			bool operator == (const Euler<TypeReal> &other) const;
			bool operator != (const Euler<TypeReal> &other) const;

			void set(const TypeReal inX, const TypeReal inY, const TypeReal inZ);

			Euler<TypeReal> toDegrees() const;
			Euler<TypeReal> toRadians() const;

			void toDegreesInPlace();
			void toRadiansInPlace();

			Vector3<TypeReal> toVector() const;

			std::string toString() const;
	};

	#include "gmEuler.hpp"

	typedef Euler<float> Eulerf;
	typedef Euler<double> Eulerd;
}


#endif // GMEULER_H
