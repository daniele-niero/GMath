/* Copyright (c) 2012, Daniele Niero
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
#include "pygmMatrix4.h"

using namespace boost::python;
using namespace gmath;


namespace {
    list matrix4_getdata_wrap(Matrix4d* self)
    {
        list retData;
        for (int i=0; i<16; i++)
        {
            retData.append(self->data[i]);
        }
        return retData;
    }

    void matrix4_setdata_wrap(Matrix4d* self, list &inlist)
    {
        for (int i=0; i<16; i++)
        {
            self->data[i] = extract<double>(inlist[i]);
        }
    }
}

void wrapMatrix4()
{
    class_<Matrix4d>("Matrix4", init<>())
        .def( init<double, double, double, double,  
                   double, double, double, double,
                   double, double, double, double,
                   double, double, double, double>() )
        .def( init<const Matrix4d &>() )
        .def( init<const Vector4d &, const Vector4d &, const Vector4d &, const Vector4d &>() )
        .def( init<const Vector3d &, const Vector3d &, const Vector3d &, const Vector3d &>() )
        .def( init<const Vector3d &, const Vector3d &, const Vector3d &>() )
        .def( init<const Quaternion<double> &>() )
        .def( init<const Quaternion<double> &, const Vector3d &>() )

        .add_property("data", &matrix4_getdata_wrap, &matrix4_setdata_wrap)

        .def("__str__", &Matrix4d::toString)
        .def("__getitem__", &getitem_wrap<Matrix4d>)
        .def("__setitem__", &setitem_wrap<Matrix4d>)
        .def("__call__", &call_wrap<Matrix4d>)

        .def( self + double() )
        .def( self + Matrix4d() )
        .def( self - double() )
        .def( self - Matrix4d() )
        .def( self / double() )
        .def( self * double() )
        .def( self * Matrix4d() )

        .def( self += double() )
        .def( self += Matrix4d() )
        .def( self -= double() )
        .def( self -= Matrix4d() )
        .def( self /= double() )
        .def( self *= double() )
        .def( self *= Matrix4d() )

        .def( self == Matrix4d() )
        .def( self != Matrix4d() )

        .def("setToIdentity", &Matrix4d::setToIdentity)
        .def("set", &Matrix4d::set)

        .def("getRow", &Matrix4d::getRow)
        .def("getRow2", &Matrix4d::getRow2)
        .def("setRow", (void (Matrix4d::*)(unsigned int, const Vector3d &))&Matrix4d::setRow)
        .def("setRow", (void (Matrix4d::*)(unsigned int, const Vector4d &))&Matrix4d::setRow)

        .def("getAxisX", &Matrix4d::getAxisX)
        .def("getAxisY", &Matrix4d::getAxisY)
        .def("getAxisZ", &Matrix4d::getAxisZ)

        .def("setAxisX", &Matrix4d::setAxisX)
        .def("setAxisY", &Matrix4d::setAxisY)
        .def("setAxisZ", &Matrix4d::setAxisZ)

        .def("setPosition", (void (Matrix4d::*)(double, double, double))&Matrix4d::setPosition)
        .def("setPosition", (void (Matrix4d::*)(const Vector3d &))&Matrix4d::setPosition)
        .def("addPosition", (void (Matrix4d::*)(double, double, double))&Matrix4d::addPosition)
        .def("addPosition", (void (Matrix4d::*)(const Vector3d &))&Matrix4d::addPosition)
        .def("translate", (void (Matrix4d::*)(double, double, double))&Matrix4d::translate)
        .def("translate", (void (Matrix4d::*)(const Vector3d &))&Matrix4d::translate)
        .def("getPosition", &Matrix4d::getPosition)

        .def("setRotation", (void (Matrix4d::*)(const Matrix3d &))&Matrix4d::setRotation)
        .def("setRotation", (void (Matrix4d::*)(const Quaterniond &))&Matrix4d::setRotation)
        .def("setRotation", (void (Matrix4d::*)(const Eulerd &, RotationOrder))&Matrix4d::setRotation)
        .def("setRotation", (void (Matrix4d::*)(double, double, double, RotationOrder))&Matrix4d::setRotation)
        
        .def("setScale", (void (Matrix4d::*)(const Vector3d &))&Matrix4d::setScale)
        .def("setScale", (void (Matrix4d::*)(double, double, double))&Matrix4d::setScale)
        .def("addScale", (void (Matrix4d::*)(const Vector3d &))&Matrix4d::addScale)
        .def("addScale", (void (Matrix4d::*)(double, double, double))&Matrix4d::addScale)
        .def("getScale", &Matrix4d::getScale)

        .def("transpose", &Matrix4d::transpose)
        .def("transposeInPlace", &Matrix4d::transposeInPlace)

        .def("determinant", &Matrix4d::determinant)

        .def("inverse", &Matrix4d::inverse)
        .def("inverseInPlace", &Matrix4d::inverseInPlace)

        .def("orthogonal", &Matrix4d::orthogonal)
        .def("orthogonalInPlace", &Matrix4d::orthogonalInPlace)

        .def("fromVectorToVector", &Matrix4d::fromVectorToVector)

        .def("lookAt", (void (Matrix4d::*)(const Vector3d &, const Vector3d &, const Vector3d &, Axis, Axis))&Matrix4d::lookAt)
        .def("lookAt", (void (Matrix4d::*)(const Vector3d &, const Vector3d &, Axis, Axis))&Matrix4d::lookAt)
        .def("createLookAt", &Matrix3d::createLookAt)
        .staticmethod("createLookAt")

        .def("fromAxisAngle", &Matrix4d::fromAxisAngle)

        .def_readonly("IDENTITY", &Matrix4d::IDENTITY)
        ;
}