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

