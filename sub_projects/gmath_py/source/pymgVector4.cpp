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
#include "pygmVector4.h"

using namespace boost::python;
using namespace gmath;



void wrapVector4()
{
    class_<Vector4d>("Vector4", init<>())
        .def( init<double, double, double, double>() )
        .def( init<const Vector4d &>() )

        .def_readwrite("x", &Vector4d::x)
        .def_readwrite("y", &Vector4d::y)
        .def_readwrite("z", &Vector4d::z)
        .def_readwrite("w", &Vector4d::w)

        .def( "__str__", &Vector4d::toString )
        .def("__getitem__", getitem_wrap<Vector4d>)
        .def("__setitem__", setitem_wrap<Vector4d>)

        .def( self + Vector4d() )
        .def( self - Vector4d() )
        .def( self - self )
        .def( self * double() )
        .def( self / double() )

        .def( self += Vector4d() )
        .def( self -= Vector4d() )
        .def( self *= double() )
        .def( self /= double() )

        .def( self == Vector4d() )
        .def( self != Vector4d() )

        .def("set", &Vector4d::set)

        .def("dot", &Vector4d::dot)
        .def("length", &Vector4d::length)
        .def("squaredLength", &Vector4d::squaredLength)
        
        .def("normalize", &Vector4d::normalize)
        .def("normalizeInPlace", &Vector4d::normalizeInPlace)
        ;
}

