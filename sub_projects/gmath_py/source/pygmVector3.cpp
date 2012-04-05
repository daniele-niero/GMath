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
#include "pygmVector3.h"

using namespace boost::python;
using namespace gmath;


void vector3f_setitem_wrap(Vector3f* self, int index, float value){
    self->operator[](index) = value;
}

float  (Vector3f::*vector3f_getitem_wrap)(int) const = &Vector3f::operator[];


void wrapVector3()
{
    class_<Vector3f>("Vector3", init<>())
        .def( init<float, float, float>() )
        .def( init<const Vector3f &>() )
        //.def( init<const float *>() )

        .def_readwrite("x", &Vector3f::x)
        .def_readwrite("y", &Vector3f::y)
        .def_readwrite("z", &Vector3f::z)

        .def( "__str__", &Vector3f::toString )
        .def("__getitem__", vector3f_getitem_wrap)
        .def("__setitem__", vector3f_setitem_wrap)

        .def( self + Vector3f() )
        .def( self - Vector3f() )
        .def( self * float() )
        .def( self / float() )

        .def( self += Vector3f() )
        .def( self -= Vector3f() )
        .def( self *= float() )
        .def( self /= float() )

        .def( self == Vector3f() )
        .def( self != Vector3f() )

        .def("set", &Vector3f::set)
        .def("duplicate", &Vector3f::duplicate)
        .def("cross", &Vector3f::cross)
        .def("crossNormalized", &Vector3f::crossNormalized)
        .def("dot", &Vector3f::dot)
        .def("length", &Vector3f::length)
        .def("squaredLength", &Vector3f::squaredLength)
        .def("distance", &Vector3f::distance)
        .def("normalize", &Vector3f::normalize)
        .def("normalizeInPlace", &Vector3f::normalizeInPlace)
        .def("angle", &Vector3f::angle)
        .def("reflect", &Vector3f::reflect)
        .def("reflectInPlace", &Vector3f::reflectInPlace)
        .def("refract", &Vector3f::refract)
        .def("refractInPlace", &Vector3f::refractInPlace)
        ;
}

