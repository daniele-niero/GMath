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
#include "pygmMatrix3.h"

using namespace boost::python;
using namespace gmath;



list matrix4_getdata_wrap(Matrix3f* self)
{
    list retData;
    for (int i=0; i<9; i++)
    {
        retData.append(&(self->data[i]));
    }
    return retData;
}

void matrix4_setdata_wrap(Matrix3f* self, list &inlist)
{
    for (int i=0; i<9; i++)
    {
        self->data[i] = extract<float>(inlist[i]);
    }
}



void wrapMatrix3()
{
    class_<Matrix3f>("Matrix3", init<>())
        .def( init<float, float, float, float, float, float, float, float, float>() )
        .def( init<const Matrix3f &>() )
        .def( init<const Vector3f &, const Vector3f &, const Vector3f &>() )

        .def("getData", &matrix4_getdata_wrap)
        .def("setData", &matrix4_setdata_wrap)


        .def("__str__", &Matrix3f::toString)
        ;
}
