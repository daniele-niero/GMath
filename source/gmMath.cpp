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

#include "../include/gmMath.h"

namespace gmath
{
	template<> const float Math<float>::EPSILON = 1e-06f;
	template<> const float Math<float>::PI = (float)(4.0*atan(1.0));
	template<> const float Math<float>::HALFPI = Math<float>::PI*0.5f;
	template<> const float Math<float>::MAX = FLT_MAX;
	template<> const float Math<float>::MIN = -FLT_MAX;
	template<> const float Math<float>::SMALLEST = FLT_MIN;

	template<> const double Math<double>::EPSILON = 1e-08;
	template<> const double Math<double>::PI = 4.0*atan(1.0);
	template<> const double Math<double>::HALFPI = Math<double>::PI*0.5;
	template<> const double Math<double>::MAX = DBL_MAX;
	template<> const double Math<double>::MIN = -DBL_MAX;
	template<> const double Math<double>::SMALLEST = DBL_MIN;
}
