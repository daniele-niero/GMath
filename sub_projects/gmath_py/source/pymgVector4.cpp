/*
A math library for 3D graphic.
Copyright (C) 2010 Daniele Niero

Author contact: nieroinfo@gmail.com

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
    class_<Vector4f>("Vector4", init<>())
        .def( init<float, float, float, float>() )
        .def( init<const Vector4f &>() )

        .def_readwrite("x", &Vector4f::x)
        .def_readwrite("y", &Vector4f::y)
        .def_readwrite("z", &Vector4f::z)
        .def_readwrite("w", &Vector4f::w)

        .def( "__str__", &Vector4f::toString )
        .def("__getitem__", getitem_wrap<Vector4f>)
        .def("__setitem__", setitem_wrap<Vector4f>)

        .def( self + Vector4f() )
        .def( self - Vector4f() )
        .def( self * float() )
        .def( self / float() )

        .def( self += Vector4f() )
        .def( self -= Vector4f() )
        .def( self *= float() )
        .def( self /= float() )

        .def( self == Vector4f() )
        .def( self != Vector4f() )

        .def("set", &Vector4f::set)
        .def("duplicate", &Vector4f::duplicate)

        .def("dot", &Vector4f::dot)
        .def("length", &Vector4f::length)
        .def("squaredLength", &Vector4f::squaredLength)
        
        .def("normalize", &Vector4f::normalize)
        .def("normalizeInPlace", &Vector4f::normalizeInPlace)
        ;
}

