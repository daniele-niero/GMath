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


#ifndef GMEULER_H
#define GMEULER_H

#include "gmRoot.h"
#include "gmMath.h"
#include "gmVector3.h"

namespace gmath
{

	template <typename real>
	class Euler
	{
		public:
			Euler();
			Euler(const Euler<real>& other);
			Euler(const real inX, const real inY, const real inZ);
			Euler(const Vector3<real>& vec);

			real x, y, z;

			/*------ coordinate access ------*/
			real operator[] (int i) const;
			real& operator[] (int i);

			/*------ Comparisons ------*/
			bool operator == (const Euler<real> &other) const;
			bool operator != (const Euler<real> &other) const;

			void set(const real inX, const real inY, const real inZ);

			Euler<real> toDegrees() const;
			Euler<real> toRadians() const;

			void toDegreesInPlace();
			void toRadiansInPlace();

			Vector3<real> toVector() const;

			std::string toString() const;
	};

	#include "gmEuler.hpp"

	typedef Euler<float> Eulerf;
	typedef Euler<double> Eulerd;
}


#endif // GMEULER_H
