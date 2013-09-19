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
#include "pygmMatrix3.h"

using namespace boost::python;
using namespace gmath;


namespace {
        list matrix3_getdata_wrap(Matrix3d* self)
        {
            list retData;
            for (int i=0; i<9; i++)
            {
                retData.append(self->data[i]);
            }
            return retData;
        }

        void matrix3_setdata_wrap(Matrix3d* self, list &inlist)
        {
            for (int i=0; i<9; i++)
            {
                self->data[i] = extract<double>(inlist[i]);
            }
        }

        // to ensure RotationOrder with default argument...
        void setFromEulerWithArg1(Matrix3d* self, const double& x, const double& y, const double& z)
        {
            self->setFromEuler(x, y, z);
        }
        void setFromEulerWithArg2(Matrix3d* self, const Eulerd& euler)
        {
            self->setFromEuler(euler);
        }


        Eulerd toEulerWithArg1(Matrix3d* self, RotationOrder order)
        {
            return self->toEuler(order);
        }
        void toEulerWithArg2(Matrix3d* self, Eulerd& outEuler, RotationOrder order)
        {
            return self->toEuler(outEuler, order);
        }
        Eulerd toEulerWithArg3(Matrix3d* self)
        {
            return self->toEuler();
        }
        void toEulerWithArg4(Matrix3d* self, Eulerd& outEuler)
        {
            return self->toEuler(outEuler);
        }
}

void wrapMatrix3()
{
    class_<Matrix3d>("Matrix3", init<>())
        .def( init<double, double, double, double, double, double, double, double, double>() )
        .def( init<const Matrix3d &>() )
        .def( init<const Vector3d &, const Vector3d &, const Vector3d &>() )

        .add_property("data", &matrix3_getdata_wrap, &matrix3_setdata_wrap)

        .def("__str__", &Matrix3d::toString)
        .def("__getitem__", &getitem_wrap<Matrix3d>)
        .def("__setitem__", &setitem_wrap<Matrix3d>)
        .def("__call__", &call_wrap<Matrix3d>)

        .def( self + double() )
        .def( self + Matrix3d() )
        .def( self - double() )
        .def( self - Matrix3d() )
        .def( self / double() )
        .def( self * double() )
        .def( self * Matrix3d() )

        .def( self += double() )
        .def( self += Matrix3d() )
        .def( self -= double() )
        .def( self -= Matrix3d() )
        .def( self /= double() )
        .def( self *= double() )
        .def( self *= Matrix3d() )

        .def( self == Matrix3d() )
        .def( self != Matrix3d() )

        .def("setToIdentity", &Matrix3d::setToIdentity)
        .def("set", &Matrix3d::set)

        .def("getRow", &Matrix3d::getRow)
        .def("setRow", &Matrix3d::setRow)

        .def("getScale", &Matrix3d::getScale)
        .def("addScale", (void (Matrix3d::*)(double, double, double))&Matrix3d::addScale)
        .def("addScale", (void (Matrix3d::*)(const Vector3d&))&Matrix3d::addScale)
        .def("setScale", (void (Matrix3d::*)(double, double, double))&Matrix3d::setScale)
        .def("setScale", (void (Matrix3d::*)(const Vector3d&))&Matrix3d::setScale)

        .def("setFromEuler", (void (Matrix3d::*)(const double&, const double&, const double&, RotationOrder))&Matrix3d::setFromEuler)
        .def("setFromEuler", (void (Matrix3d::*)(const Eulerd&, RotationOrder))&Matrix3d::setFromEuler)
        .def("setFromEuler", setFromEulerWithArg1)
        .def("setFromEuler", setFromEulerWithArg2)

        .def("toEuler", toEulerWithArg1)
        .def("toEuler", toEulerWithArg2)
        .def("toEuler", toEulerWithArg3)
        .def("toEuler", toEulerWithArg4)
        
        .def("transpose", &Matrix3d::transpose)
        .def("transposeInPlace", &Matrix3d::transposeInPlace)

        .def("determinant", &Matrix3d::determinant)

        .def("inverse", &Matrix3d::inverse)
        .def("inverseInPlace", &Matrix3d::inverseInPlace)

        .def("orthogonal", &Matrix3d::orthogonal)
        .def("orthogonalInPlace", &Matrix3d::orthogonalInPlace)
        
        .def("setFromVectorToVector", &Matrix3d::setFromVectorToVector)
        .def("setFromAxisAngle", &Matrix3d::setFromAxisAngle)

        .def("lookAt", &Matrix3d::lookAt)
        .def("createLookAt", &Matrix3d::createLookAt)
        .staticmethod("createLookAt")


        .def_readonly("IDENTITY", &Matrix3d::IDENTITY)

        ;
}
