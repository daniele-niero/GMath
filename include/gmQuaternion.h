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
        Quaternion(const Matrix3<real>& inMat);
        Quaternion(const Matrix4<real>& inMat);
        Quaternion(const Vector3<real>& axis, real angle);
        Quaternion(real angleX, real angleY, real angleZ);

        /*------ properties ------*/
        real x, y, z, w;

        /*------ coordinate access ------*/
        real operator[] (int i) const;
        real& operator[] (int i);

        /** Pointer access for direct copying. */
        real* ptr();
        const real* ptr() const;

        /*------ Arithmetic operations ------*/
		Quaternion<real> operator - () const;
        Quaternion<real> operator + (const Quaternion<real> &other) const;
        Quaternion<real> operator - (const Quaternion<real> &other) const;
        Quaternion<real> operator * (const Quaternion<real> &other) const;
        Quaternion<real> operator * (real scalar) const;
        Vector3<real> operator * (const Vector3<real> &vec) const;
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
        void setToIdentity();

        Vector3<real> getAxisY() const;
        Vector3<real> getAxisX() const;
        Vector3<real> getAxisZ() const;

        template <typename gmMatrixType>
        void fromMatrix(const gmMatrixType &mat);
        void fromMatrix3(const Matrix3<real> &mat);
        Matrix3<real> toMatrix3() const;
        void fromMatrix4(const Matrix4<real> &mat);
        Matrix4<real> toMatrix4() const;
		void setMatrix4(Matrix4<real>& outMat) const;
		void setMatrix4(Matrix4<real>& outMat, const Vector3<real>& scale, const Vector3<real>& pos) const;

        void fromAxisAngle(const Vector3<real>& axis, real angle);
		void toAxisAngle(Vector3<real>& outAxis, real& outAngle) const;

        void fromEuler(real angleX, real angleY, real angleZ, RotationOrder order=XYZ);
		void fromEuler(const Euler<real>& euler, RotationOrder order=XYZ);
		Euler<real> toEuler(RotationOrder order=XYZ) const;

		real length () const;
		real squaredLength () const;
		
		void normalizeInPlace();
		Quaternion<real> normalize() const;

		Quaternion<real> inverse() const;
        void inverseInPlace();

		void conjugateInPlace();
		Quaternion<real> conjugate() const;

		Quaternion<real> exp() const;
		Quaternion<real> log() const;

        /** Perform the dot product between this vector and the given vector */
        real dot(const Quaternion<real> & other) const;

        /*  This function comes from Imath, part of ILM's OpenEXR library.

            Spherical linear interpolation.
            Assumes q1 and q2 are normalized and that q1 != -q2.
        
            This method does *not* interpolate along the shortest arc between q1 and q2.  If you desire interpolation
            along the shortest arc, and q1^q2 is negative, then consider calling slerpShortestArc(), below, or flipping
            the second quaternion explicitly.
        
            The implementation of squad() depends on a slerp() that interpolates as is, without the automatic flipping.
        
            Don Hatch explains the method we use here on his web page, The Right Way to Calculate Stuff, at http://www.plunk.org/~hatch/rightway.php */
        void slerpInPlace(const Quaternion<real> &q1, const Quaternion<real> &q2, real t, bool shortestPath=true);
		Quaternion<real> slerp(const Quaternion<real> &q2, real t, bool shortestPath=true) const;


        std::string toString() const;
    };

    #include "gmQuaternion.hpp"

    typedef Quaternion<float> Quaternionf;
    typedef Quaternion<double> Quaterniond;
}

#endif // GMQUATERNION_H
