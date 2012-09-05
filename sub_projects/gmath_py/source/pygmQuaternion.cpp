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
    class_<Quaternionf>("Quaternion", init<>())
        .def( init<float, float, float, float>() )
        .def( init<const Quaternionf &>() )

        .def_readwrite("x", &Quaternionf::x)
        .def_readwrite("y", &Quaternionf::y)
        .def_readwrite("z", &Quaternionf::z)
        .def_readwrite("w", &Quaternionf::w)

        .def( "__str__", &Quaternionf::toString )
        .def("__getitem__", &getitem_wrap<Quaternionf>)
        .def("__setitem__", &setitem_wrap<Quaternionf>)

        .def( self + Quaternionf() )
        .def( self - Quaternionf() )
        .def( self * float() )
        .def( self / float() )

        .def( self += Quaternionf() )
        .def( self -= Quaternionf() )
        .def( self *= float() )
        .def( self /= float() )

        .def( self == Quaternionf() )
        .def( self != Quaternionf() )

        .def("set", &Quaternionf::set)

        .def("inverse", &Quaternionf::inverse)
        .def("inverseInPlace", &Quaternionf::inverse)

        .def("fromMatrix3", &Quaternionf::fromMatrix3)
        .def("toMatrix3", &Quaternionf::toMatrix3)
        .def("fromMatrix4", &Quaternionf::fromMatrix4)
        .def("toMatrix4", &Quaternionf::toMatrix4)

        .def("duplicate", &Quaternionf::duplicate)

        .def("dot", &Quaternionf::dot)

        // .def("slerp", &Quaternionf::slerp)
        ;
}

