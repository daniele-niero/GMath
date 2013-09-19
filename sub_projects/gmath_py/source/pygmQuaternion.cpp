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

