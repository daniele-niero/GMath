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
    class_<Eulerd>("Euler", init<>())
        .def( init<const Eulerd &>() )
        .def( init<double, double, double>() )
        .def( init<const Vector3d &>() )

        .def_readwrite("x", &Eulerd::x)
        .def_readwrite("y", &Eulerd::y)
        .def_readwrite("z", &Eulerd::z)

        .def("__str__", &Eulerd::toString)
        .def("__getitem__", &getitem_wrap<Eulerd>)
        .def("__setitem__", &setitem_wrap<Eulerd>)

        .def( self == Eulerd() )
        .def( self != Eulerd() )

        .def("set", &Eulerd::set)
        .def("toDegrees", &Eulerd::toDegrees)
        .def("toRadians", &Eulerd::toRadians)
        .def("toDegreesInPlace", &Eulerd::toDegreesInPlace)
        .def("toRadiansInPlace", &Eulerd::toRadiansInPlace)

        .def("toVector", &Eulerd::toVector)
        ;
}

