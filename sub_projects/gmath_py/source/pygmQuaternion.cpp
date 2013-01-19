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
#include "pygmQuaternion.h"

using namespace boost::python;
using namespace gmath;



void wrapQuaternion()
{
    class_<Quaterniond>("Quaternion", init<>())
        .def( init<double, double, double, double>() )
        .def( init<const Quaterniond &>() )

        .def_readwrite("x", &Quaterniond::x)
        .def_readwrite("y", &Quaterniond::y)
        .def_readwrite("z", &Quaterniond::z)
        .def_readwrite("w", &Quaterniond::w)

        .def( "__str__", &Quaterniond::toString )
        .def("__getitem__", &getitem_wrap<Quaterniond>)
        .def("__setitem__", &setitem_wrap<Quaterniond>)

        .def( self + Quaterniond() )
        .def( self - Quaterniond() )
        .def( self * double() )
        .def( self / double() )

        .def( self += Quaterniond() )
        .def( self -= Quaterniond() )
        .def( self *= double() )
        .def( self /= double() )

        .def( self == Quaterniond() )
        .def( self != Quaterniond() )

        .def("set", &Quaterniond::set)

        .def("inverse", &Quaterniond::inverse)
        .def("inverseInPlace", &Quaterniond::inverse)

        .def("fromMatrix3", &Quaterniond::fromMatrix3)
        .def("toMatrix3", &Quaterniond::toMatrix3)
        .def("fromMatrix4", &Quaterniond::fromMatrix4)
        .def("toMatrix4", &Quaterniond::toMatrix4)

        .def("dot", &Quaterniond::dot)

        .def("slerp", &Quaterniond::slerp)
        ;
}

