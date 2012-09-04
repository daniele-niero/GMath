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

#ifndef GMQUATERNION_H
#define GMQUATERNION_H

#include <string>
#include <stdexcept>
#include <math.h>
#include "gmMath.h"
#include "gmMatrix3.h"
#include "gmMatrix4.h"

using namespace std;

namespace gmath
{
    template <typename real>
    class Quaternion
    {
    public:
        /*------ constructors ------*/
        Quaternion();
        Quaternion(real x, real y, real z, real w);
        Quaternion(const Quaternion<real> &values);
        Quaternion(const real *list);

        /*------ properties ------*/
        real x, y, z, w;

        /*------ coordinate access ------*/
        real operator[] (int i) const;
        real& operator[] (int i);

        /** Pointer access for direct copying. */
        real* ptr();
        const real* ptr() const;

        /*------ Arithmetic operations ------*/
        Quaternion<real> operator + (const Quaternion<real> &other) const;
        Quaternion<real> operator - (const Quaternion<real> &other) const;
        Quaternion<real> operator * (const Quaternion<real> &other) const;
        Quaternion<real> operator * (real scalar) const;
        Quaternion<real> operator / (real scalar) const;

        /*------ Arithmetic updates ------*/
        void operator += (const Quaternion<real> &other);
        void operator -= (const Quaternion<real> &other);
        void operator *= (const Quaternion<real> &other);
        void operator *= (real scalar);
        void operator /= (real scalar);

        /*------ Arithmetic comparisons ------*/
        bool operator == (const Quaternion<real> &other) const;
        bool operator != (const Quaternion<real> &other) const;

        /*------ Arithmetic assignment ------*/
        void operator = (const Quaternion<real> & other);

        /*------ methods ------*/

        /** Set the three properties (x, y, z, w), with the given arguments
            @param inX The wanted value for x
            @param inY The wanted value for y
            @param inZ The wanted value for z
            @param inW The wanted value for w */
        void set(real inX, real inY, real inZ, real inW);

        Quaternion<real> inverse() const;
        void inverseInPlace();

        template <typename gmMatrixType>
        void fromMatrix(const gmMatrixType &mat);

        void fromMatrix3(const Matrix3<real> &mat);
        Matrix3<real> toMatrix3() const;

        void fromMatrix4(const Matrix4<real> &mat);
        Matrix4<real> toMatrix4() const;

        /** return a Quaternion that is the exact copy of this one */
        Quaternion<real> duplicate() const;

        /** Perform the dot product between this vector and the given vector */
        real dot(const Quaternion<real> & other) const;

        /*  This function comes from Imath, part of ILM's OpenEXR library.

            Spherical linear interpolation.
            Assumes q1 and q2 are normalized and that q1 != -q2.
        
            This method does *not* interpolate along the shortest
            arc between q1 and q2.  If you desire interpolation
            along the shortest arc, and q1^q2 is negative, then
            consider calling slerpShortestArc(), below, or flipping
            the second quaternion explicitly.
        
            The implementation of squad() depends on a slerp()
            that interpolates as is, without the automatic
            flipping.
        
            Don Hatch explains the method we use here on his
            web page, The Right Way to Calculate Stuff, at
            http://www.plunk.org/~hatch/rightway.php */
        Quaternion<real> slerp(const Quaternion<real> &q1, const Quaternion<real> &q2, real t, bool shortestPath=true);

        std::string toString() const;
    };

    #include "gmQuaternion.hpp"

    typedef Quaternion<float> Quaternionf;
    typedef Quaternion<double> Quaterniond;
}

#endif // GMQUATERNION_H