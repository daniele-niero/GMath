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
#include "pygmEuler.h"

using namespace boost::python;
using namespace gmath;


void wrapEuler()
{
    class_<Eulerf>("Euler", init<>())
        .def( init<const Eulerf &>() )
        .def( init<float, float, float>() )
        .def( init<const Vector3f &>() )

        .def_readwrite("x", &Eulerf::x)
        .def_readwrite("y", &Eulerf::y)
        .def_readwrite("z", &Eulerf::z)

        .def("__str__", &Eulerf::toString)
        .def("__getitem__", &getitem_wrap<Eulerf>)
        .def("__setitem__", &setitem_wrap<Eulerf>)

        .def( self == Eulerf() )
        .def( self != Eulerf() )

        .def("set", &Eulerf::set)
        .def("toDegrees", &Eulerf::toDegrees)
        .def("toRadians", &Eulerf::toRadians)
        .def("toDegreesInPlace", &Eulerf::toDegreesInPlace)
        .def("toRadiansInPlace", &Eulerf::toRadiansInPlace)

        .def("toVector", &Eulerf::toVector)
        ;
}

