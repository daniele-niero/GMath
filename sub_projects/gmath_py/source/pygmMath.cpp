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

#include <boost/python.hpp>
#include "pygmRoot.h"
#include "pygmMath.h"

using namespace boost::python;
using namespace gmath;


void wrapMath()
{
    def("acos", &Math<float>::acos);
    def("asin", &Math<float>::asin);
    def("toRadians", &Math<float>::toRadians);
    def("toDegrees", &Math<float>::toDegrees);
    scope().attr("EPSILON") = Math<float>::EPSILON;
    scope().attr("PI") = Math<float>::PI;
    scope().attr("HALFPI") = Math<float>::HALFPI;
    scope().attr("MAX") = Math<float>::MAX;
    scope().attr("MIN") = Math<float>::MIN;
    scope().attr("SMALLEST") = Math<float>::SMALLEST;
}