#pragma once

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
        Quaternion& operator += (const Quaternion &other);
        Quaternion& operator -= (const Quaternion &other);
        Quaternion& operator *= (const Quaternion &other);
        Quaternion& operator *= (double scalar);
        Quaternion& operator /= (double scalar);

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
            Assumes q1 and q2 are normalized and that q1 != -q2. */
        void slerpInPlace(const Quaternion &q1, const Quaternion &q2, double t, bool shortestPath=true);
		Quaternion slerp(const Quaternion &q2, double t, bool shortestPath=true) const;


        std::string toString() const;
    };
}
