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
#include "gmRoot.h"
#include "gmMatrix3.h"
#include "gmMatrix4.h"

using namespace std;

namespace gmath
{
    class Quaternion
    {
    public:
        /*------ constructors ------*/
        Quaternion();
        Quaternion(double x, double y, double z, double w);
        Quaternion(const Quaternion &values);
        Quaternion(const double *list);
        Quaternion(const Matrix3& inMat);
        Quaternion(const Matrix4& inMat);
        Quaternion(const Vector3& axis, double angle);
        Quaternion(double angleX, double angleY, double angleZ);

        /*------ properties ------*/
        double x, y, z, w;

        /*------ coordinate access ------*/
        double operator[] (int i) const;
        double& operator[] (int i);

        /** Pointer access for direct copying. */
        double* data();
        const double* data() const;

        /*------ Arithmetic operations ------*/
		Quaternion operator - () const;
        Quaternion operator + (const Quaternion &other) const;
        Quaternion operator - (const Quaternion &other) const;
        Quaternion operator * (const Quaternion &other) const;
        Quaternion operator * (double scalar) const;
        Vector3 operator * (const Vector3 &vec) const;
        Quaternion operator / (double scalar) const;

        /*------ Arithmetic updates ------*/
        void operator += (const Quaternion &other);
        void operator -= (const Quaternion &other);
        void operator *= (const Quaternion &other);
        void operator *= (double scalar);
        void operator /= (double scalar);

        /*------ Arithmetic comparisons ------*/
        bool operator == (const Quaternion &other) const;
        bool operator != (const Quaternion &other) const;

        /*------ Arithmetic assignment ------*/
        void operator = (const Quaternion & other);

        /*------ methods ------*/

        /** Set the three properties (x, y, z, w), with the given arguments
            @param inX The wanted value for x
            @param inY The wanted value for y
            @param inZ The wanted value for z
            @param inW The wanted value for w */
        void set(double inX, double inY, double inZ, double inW);
        void setToIdentity();

        Vector3 getAxisY() const;
        Vector3 getAxisX() const;
        Vector3 getAxisZ() const;

        void fromMatrix3(const Matrix3 &mat);
        void fromMatrix4(const Matrix4 &mat);
        Matrix3 toMatrix3() const;
        Matrix4 toMatrix4() const;
		void setMatrix4(Matrix4& outMat) const;
		void setMatrix4(Matrix4& outMat, const Vector3& scale, const Vector3& pos) const;

        void fromAxisAngle(const Vector3& axis, double angle);
		void toAxisAngle(Vector3& outAxis, double& outAngle) const;

        void fromEuler(double angleX, double angleY, double angleZ, RotationOrder order=XYZ);
		void fromEuler(const Euler& euler, RotationOrder order=XYZ);
		Euler toEuler(RotationOrder order=XYZ) const;

		double length () const;
		double squaredLength () const;
		
		void normalizeInPlace();
		Quaternion normalize() const;

		Quaternion inverse() const;
        void inverseInPlace();

		void conjugateInPlace();
		Quaternion conjugate() const;

		Quaternion exp() const;
		Quaternion log() const;

        /** Perform the dot product between this vector and the given vector */
        double dot(const Quaternion & other) const;

        /*  This function comes from Imath, part of ILM's OpenEXR library.

            Spherical linear interpolation.
            Assumes q1 and q2 are normalized and that q1 != -q2.
        
            This method does *not* interpolate along the shortest arc between q1 and q2.  If you desire interpolation
            along the shortest arc, and q1^q2 is negative, then consider calling slerpShortestArc(), below, or flipping
            the second quaternion explicitly.
        
            The implementation of squad() depends on a slerp() that interpolates as is, without the automatic flipping.
        
            Don Hatch explains the method we use here on his web page, The Right Way to Calculate Stuff, at http://www.plunk.org/~hatch/rightway.php */
        void slerpInPlace(const Quaternion &q1, const Quaternion &q2, double t, bool shortestPath=true);
		Quaternion slerp(const Quaternion &q2, double t, bool shortestPath=true) const;


        std::string toString() const;
    };
}

#endif // GMQUATERNION_H
