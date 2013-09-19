/* Copyright (c) 2010-13, Daniele Niero
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this 
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

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

