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
#include "pygmMatrix4.h"

using namespace boost::python;
using namespace gmath;


namespace {
list matrix4_getdata_wrap(Matrix4f* self)
{
    list retData;
    for (int i=0; i<16; i++)
    {
        retData.append(self->data[i]);
    }
    return retData;
}

void matrix4_setdata_wrap(Matrix4f* self, list &inlist)
{
    for (int i=0; i<16; i++)
    {
        self->data[i] = extract<float>(inlist[i]);
    }
}

Matrix4f (Matrix4f::*addScale1)(float, float, float)= &Matrix4f::addScale;
Matrix4f (Matrix4f::*addScale2)(const Vector3f&) = &Matrix4f::addScale;
void (Matrix4f::*addScaleInPlace1)(float, float, float)= &Matrix4f::addScaleInPlace;
void (Matrix4f::*addScaleInPlace2)(const Vector3f&) = &Matrix4f::addScaleInPlace;
Matrix4f (Matrix4f::*setScale1)(float, float, float)= &Matrix4f::setScale;
Matrix4f (Matrix4f::*setScale2)(const Vector3f&) = &Matrix4f::setScale;
void (Matrix4f::*setScaleInPlace1)(float, float, float)= &Matrix4f::setScaleInPlace;
void (Matrix4f::*setScaleInPlace2)(const Vector3f&) = &Matrix4f::setScaleInPlace;
// Matrix4f (*createScale1)(float, float, float)= &Matrix4f::createScale;
// Matrix4f (*createScale2)(const Vector3f&) = &Matrix4f::createScale;

// void (Matrix4f::*setFromEuler1)(const float&, const float&, const float&, RotationOrder) = &Matrix4f::setFromEuler;
// void (Matrix4f::*setFromEuler2)(const Eulerf&, RotationOrder) = &Matrix4f::setFromEuler;
// // to ensure RotationOrder with default argument...
// void matrix4_setFromEuler1_wrap(Matrix4f* self, const float& x, const float& y, const float& z)
// {
//     self->setFromEuler(x, y, z);
// }
// void matrix4_setFromEuler2_wrap(Matrix4f* self, const Eulerf& euler)
// {
//     self->setFromEuler(euler);
// }

// Matrix4f (*createFromEuler1)(const float&, const float&, const float&, RotationOrder) = &Matrix4f::createFromEuler;
// Matrix4f (*createFromEuler2)(const Eulerf&, RotationOrder) = &Matrix4f::createFromEuler;
// // to ensure RotationOrder with default argument...
// Matrix4f matrix4_createFromEuler1_wrap(const float& x, const float& y, const float& z)
// {
//     return Matrix4f::createFromEuler(x, y, z);
// }
// Matrix4f matrix4_createFromEuler2_wrap(const Eulerf& euler)
// {
//     return Matrix4f::createFromEuler(euler);
// }
}

void wrapMatrix4()
{
    class_<Matrix4f>("Matrix4", init<>())
        .def( init<float, float, float, float,  
                   float, float, float, float,
                   float, float, float, float,
                   float, float, float, float>() )
        .def( init<const Matrix4f &>() )
        .def( init<const Vector4f &, const Vector4f &, const Vector4f &, const Vector4f &>() )

        .add_property("data", &matrix4_getdata_wrap, &matrix4_setdata_wrap)

        .def("__str__", &Matrix4f::toString)
        .def("__getitem__", getitem_wrap<Matrix4f>)
        .def("__setitem__", setitem_wrap<Matrix4f>)

        .def( self + float() )
        .def( self + Matrix4f() )
        .def( self - float() )
        .def( self - Matrix4f() )
        .def( self / float() )
        .def( self * float() )
        .def( self * Matrix4f() )

        .def( self += float() )
        .def( self += Matrix4f() )
        .def( self -= float() )
        .def( self -= Matrix4f() )
        .def( self /= float() )
        .def( self *= float() )
        .def( self *= Matrix4f() )

        .def( self == Matrix4f() )
        .def( self != Matrix4f() )

        .def("setToIdentity", &Matrix4f::setToIdentity)
        .def("set", &Matrix4f::set)

        .def("setPosition", &Matrix4f::setPosition)
        .def("addPosition", &Matrix4f::addPosition)
        .def("translate", &Matrix4f::translate)
        .def("getPosition", &Matrix4f::getPosition)

        .def("setRotation", &Matrix4f::setRotation)
        .def("getRotation", &Matrix4f::getRotation)

        .def("transpose", &Matrix4f::transpose)
        .def("transposeInPlace", &Matrix4f::transposeInPlace)

        .def("determinant", &Matrix4f::determinant)

        .def("inverse", &Matrix4f::inverse)
        .def("inverseInPlace", &Matrix4f::inverseInPlace)

        .def("getScale", &Matrix4f::getScale)
        .def("addScale", addScale1)
        .def("addScale", addScale2)
        .def("addScaleInPlace", addScaleInPlace1)
        .def("addScaleInPlace", addScaleInPlace2)
        .def("setScale", setScale1)
        .def("setScale", setScale2)
        .def("setScaleInPlace", setScaleInPlace1)
        .def("setScaleInPlace", setScaleInPlace2)

        .def("lookAt", &Matrix4f::lookAt)
        .def("createLookAt", &Matrix3f::createLookAt)
        .staticmethod("createLookAt")

        .def("setFromAxisAngle", &Matrix4f::setFromAxisAngle)
        .def("createFromAxisAngle", &Matrix4f::createFromAxisAngle)
        .staticmethod("createFromAxisAngle")

        .def_readonly("IDENTITY", &Matrix4f::IDENTITY)

        ;
}
