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
#include "pygmVector3.h"

using namespace boost::python;
using namespace gmath;


void wrapVector3()
{
    class_<Vector3d>("Vector3", init<>())
        .def( init<double, double, double>() )
        .def( init<const Vector3d &>() )
        //.def( init<const double *>() )

        .def_readwrite("x", &Vector3d::x)
        .def_readwrite("y", &Vector3d::y)
        .def_readwrite("z", &Vector3d::z)

        .def( "__str__", &Vector3d::toString )
        .def("__getitem__", getitem_wrap<Vector3d>)
        .def("__setitem__", setitem_wrap<Vector3d>)

        .def( self + Vector3d() )
        .def( self - Vector3d() )
        .def( self - self )
        .def( self * double() )
        .def( self * Vector3d() )
        .def( self * Matrix3d() )
        .def( self * Matrix4d() )
        .def( self / double() )
        .def( self / Vector3d() )

        .def( self += Vector3d() )
        .def( self -= Vector3d() )
        .def( self *= double() )
        .def( self *= Matrix3d() )
        .def( self *= Matrix4d() )
        .def( self /= double() )
        .def( self /= Vector3d() )

        .def( self == Vector3d() )
        .def( self != Vector3d() )

        .def("set", &Vector3d::set)
        .def("cross", &Vector3d::cross)
        .def("crossInPlace", &Vector3d::crossInPlace)
        .def("crossNormalize", &Vector3d::crossNormalize)
        .def("crossNormalizeInPlace", &Vector3d::crossNormalizeInPlace)
        .def("dot", &Vector3d::dot)
        .def("length", &Vector3d::length)
        .def("squaredLength", &Vector3d::squaredLength)
        .def("distance", &Vector3d::distance)
        .def("squaredDistance", &Vector3d::squaredDistance)
        .def("normalize", &Vector3d::normalize)
        .def("normalizeInPlace", &Vector3d::normalizeInPlace)
        .def("angle", &Vector3d::angle)
        .def("reflect", &Vector3d::reflect)
        .def("reflectInPlace", &Vector3d::reflectInPlace)
        .def("refract", &Vector3d::refract)
        .def("refractInPlace", &Vector3d::refractInPlace)
        .def("linearInterpolate", &Vector3d::linearInterpolate)
        .def("linearInterpolateInPlace", &Vector3d::linearInterpolateInPlace)
        ;
}

