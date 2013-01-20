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
        bool toEulerWithArg2(Matrix3d* self, Eulerd& outEuler, RotationOrder order)
        {
            return self->toEuler(outEuler, order);
        }
        Eulerd toEulerWithArg3(Matrix3d* self)
        {
            return self->toEuler();
        }
        bool toEulerWithArg4(Matrix3d* self, Eulerd& outEuler)
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
