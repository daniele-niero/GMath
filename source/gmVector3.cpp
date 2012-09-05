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

#include "../include/gmVector3.h"

namespace gmath
{
	template<> const Vector3<float> Vector3<float>::XAXIS(1.0f, 0.0f, 0.0f);
	template<> const Vector3<float> Vector3<float>::YAXIS(0.0f, 1.0f, 0.0f);
	template<> const Vector3<float> Vector3<float>::ZAXIS(0.0f, 0.0f, 1.0f);

	template<> const Vector3<double> Vector3<double>::XAXIS(1.0, 0.0, 0.0);
	template<> const Vector3<double> Vector3<double>::YAXIS(0.0, 1.0, 0.0);
	template<> const Vector3<double> Vector3<double>::ZAXIS(0.0, 0.0, 1.0);


	template<> const Vector3<float> Vector3<float>::N_XAXIS(-1.0f, 0.0f, 0.0f);
	template<> const Vector3<float> Vector3<float>::N_YAXIS(0.0f, -1.0f, 0.0f);
	template<> const Vector3<float> Vector3<float>::N_ZAXIS(0.0f, 0.0f, -1.0f);

	template<> const Vector3<double> Vector3<double>::N_XAXIS(-1.0, 0.0, 0.0);
	template<> const Vector3<double> Vector3<double>::N_YAXIS(0.0, -1.0, 0.0);
	template<> const Vector3<double> Vector3<double>::N_ZAXIS(0.0, 0.0, -1.0);


	template<> const Vector3<double> Vector3<double>::ZERO(0.0, 0.0, 0.0);
	template<> const Vector3<float> Vector3<float>::ZERO(0.0f, 0.0f, 0.0f);
}
