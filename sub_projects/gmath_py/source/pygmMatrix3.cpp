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
#include "pygmMatrix3.h"

using namespace boost::python;
using namespace gmath;


namespace {
        list matrix3_getdata_wrap(Matrix3f* self)
        {
            list retData;
            for (int i=0; i<9; i++)
            {
                retData.append(self->data[i]);
            }
            return retData;
        }

        void matrix3_setdata_wrap(Matrix3f* self, list &inlist)
        {
            for (int i=0; i<9; i++)
            {
                self->data[i] = extract<float>(inlist[i]);
            }
        }

        Matrix3f (Matrix3f::*addScale1)(float, float, float)= &Matrix3f::addScale;
        Matrix3f (Matrix3f::*addScale2)(const Vector3f&) = &Matrix3f::addScale;
        void (Matrix3f::*addScaleInPlace1)(float, float, float)= &Matrix3f::addScaleInPlace;
        void (Matrix3f::*addScaleInPlace2)(const Vector3f&) = &Matrix3f::addScaleInPlace;
        Matrix3f (Matrix3f::*setScale1)(float, float, float)= &Matrix3f::setScale;
        Matrix3f (Matrix3f::*setScale2)(const Vector3f&) = &Matrix3f::setScale;
        void (Matrix3f::*setScaleInPlace1)(float, float, float)= &Matrix3f::setScaleInPlace;
        void (Matrix3f::*setScaleInPlace2)(const Vector3f&) = &Matrix3f::setScaleInPlace;
        Matrix3f (*createScale1)(float, float, float)= &Matrix3f::createScale;
        Matrix3f (*createScale2)(const Vector3f&) = &Matrix3f::createScale;

        void (Matrix3f::*setFromEuler1)(const float&, const float&, const float&, RotationOrder) = &Matrix3f::setFromEuler;
        void (Matrix3f::*setFromEuler2)(const Eulerf&, RotationOrder) = &Matrix3f::setFromEuler;
        // to ensure RotationOrder with default argument...
        void matrix3_setFromEuler1_wrap(Matrix3f* self, const float& x, const float& y, const float& z)
        {
            self->setFromEuler(x, y, z);
        }
        void matrix3_setFromEuler2_wrap(Matrix3f* self, const Eulerf& euler)
        {
            self->setFromEuler(euler);
        }

        Matrix3f (*createFromEuler1)(const float&, const float&, const float&, RotationOrder) = &Matrix3f::createFromEuler;
        Matrix3f (*createFromEuler2)(const Eulerf&, RotationOrder) = &Matrix3f::createFromEuler;
        // to ensure RotationOrder with default argument...
        Matrix3f matrix3_createFromEuler1_wrap(const float& x, const float& y, const float& z)
        {
            return Matrix3f::createFromEuler(x, y, z);
        }
        Matrix3f matrix3_createFromEuler2_wrap(const Eulerf& euler)
        {
            return Matrix3f::createFromEuler(euler);
        }
}

void wrapMatrix3()
{
    class_<Matrix3f>("Matrix3", init<>())
        .def( init<float, float, float, float, float, float, float, float, float>() )
        .def( init<const Matrix3f &>() )
        .def( init<const Vector3f &, const Vector3f &, const Vector3f &>() )

        .add_property("data", &matrix3_getdata_wrap, &matrix3_setdata_wrap)

        .def("__str__", &Matrix3f::toString)
        .def("__getitem__", getitem_wrap<Matrix3f>)
        .def("__setitem__", setitem_wrap<Matrix3f>)

        .def( self + float() )
        .def( self + Matrix3f() )
        .def( self - float() )
        .def( self - Matrix3f() )
        .def( self / float() )
        .def( self * float() )
        .def( self * Matrix3f() )
        .def( self * Vector3f() )

        .def( self += float() )
        .def( self += Matrix3f() )
        .def( self -= float() )
        .def( self -= Matrix3f() )
        .def( self /= float() )
        .def( self *= float() )
        .def( self *= Matrix3f() )

        .def( self == Matrix3f() )
        .def( self != Matrix3f() )

        .def("setToIdentity", &Matrix3f::setToIdentity)
        .def("set", &Matrix3f::set)

        .def("transpose", &Matrix3f::transpose)
        .def("transposeInPlace", &Matrix3f::transposeInPlace)

        .def("determinant", &Matrix3f::determinant)

        .def("inverse", &Matrix3f::inverse)
        .def("inverseInPlace", &Matrix3f::inverseInPlace)

        .def("orthogonal", &Matrix3f::orthogonal)
        .def("orthogonalInPlace", &Matrix3f::orthogonalInPlace)

        .def("getScale", &Matrix3f::getScale)
        .def("addScale", addScale1)
        .def("addScale", addScale2)
        .def("addScaleInPlace", addScaleInPlace1)
        .def("addScaleInPlace", addScaleInPlace2)
        .def("setScale", setScale1)
        .def("setScale", setScale2)
        .def("setScaleInPlace", setScaleInPlace1)
        .def("setScaleInPlace", setScaleInPlace2)
        .def("createScale", createScale1)
        .def("createScale", createScale2)
        .staticmethod("createScale")

        .def("setFromEuler", setFromEuler1)
        .def("setFromEuler", setFromEuler2)
        .def("setFromEuler", &matrix3_setFromEuler1_wrap)
        .def("setFromEuler", &matrix3_setFromEuler2_wrap)

        .def("createFromEuler", createFromEuler1)
        .def("createFromEuler", createFromEuler2)
        .def("createFromEuler", &matrix3_createFromEuler1_wrap)
        .def("createFromEuler", &matrix3_createFromEuler2_wrap)
        .staticmethod("createFromEuler")

        .def("setFromVectorToVector", &Matrix3f::setFromVectorToVector)
        .def("createFromVectorToVector", &Matrix3f::createFromVectorToVector)
        .staticmethod("createFromVectorToVector")

        .def("lookAt", &Matrix3f::lookAt)
        .def("createLookAt", &Matrix3f::createLookAt)
        .staticmethod("createLookAt")

        .def("setFromAxisAngle", &Matrix3f::setFromAxisAngle)
        .def("createFromAxisAngle", &Matrix3f::createFromAxisAngle)
        .staticmethod("createFromAxisAngle")

        .def_readonly("IDENTITY", &Matrix3f::IDENTITY)

        ;
}
