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

#ifndef GMQUATERNION_H
#define GMQUATERNION_H

namespace gmath
{
    template <typename real>
    class Quaternion
    {
    public:
        /*------ constructors ------*/
        Quaternion();
        Quaternion(real x, real y, real z, real w);
        Quaternion(const Vector4<real> &values);
        Quaternion(const real* list);

        /*------ properties ------*/
        real x, y, z, w;

        /*------ coordinate access ------*/
        real operator[] (int i) const;
        real& operator[] (int i);

        /** Pointer access for direct copying. */
        real* ptr();
        const real* ptr() const;

        /*------ Arithmetic operations ------*/
        Quaternion<real> operator + (const Quaternion<real> & other) const;
        Quaternion<real> operator - (const Quaternion<real> & other) const;
        Quaternion<real> operator * (real scalar) const;
        Quaternion<real> operator * (const Quaternion<real> & other) const;

        /*------ Arithmetic updates ------*/
        void operator += (const Quaternion<real> & other);
        void operator -= (const Quaternion<real> & other);
        void operator *= (real scalar);
        void operator *= (const Quaternion<real> & other);

        /*------ Arithmetic comparisons ------*/
        bool operator == (const Quaternion<real> & other) const;
        bool operator != (const Quaternion<real> & other) const;

        /*------ methods ------*/

        /** Set the three properties (x, y, z, w), with the given arguments
            @param inX The wanted value for x
            @param inY The wanted value for y
            @param inZ The wanted value for z
            @param inW The wanted value for w */
        void set(real inX, real inY, real inZ, real inW);

        /** return a Quaternion that is the exact copy of this one */
        Quaternion<real> duplicate() const;

        /** Perform the dot product between this vector and the given vector */
        real dot(const Quaternion<real> & other) const;
    };
}

#endif // GMQUATERNION_H