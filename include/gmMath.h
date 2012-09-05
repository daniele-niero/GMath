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

#ifndef GMMATH_H
#define GMMATH_H

#include <math.h>
#include <float.h>
#include <limits.h>
#include <iostream>

#ifdef LINUX
#include <memory.h>
#endif

namespace gmath
{
	template <typename real>
	struct Math
	{
		public:
			/** The acos and asin
			    functions clamp the input argument to [-1,1] to avoid NaN issues
			    when the input is slightly larger than 1 or slightly smaller than -1.
			*/
			static real acos(real x);
			static real asin(real x);
			static real toRadians(real x);
			static real toDegrees(real x);

			static const real EPSILON;
			static const real PI;
			static const real HALFPI;
			static const real MAX;
			static const real MIN;
			static const real SMALLEST;
	};

	#include "gmMath.hpp"
}

#endif // GMMATH_H
