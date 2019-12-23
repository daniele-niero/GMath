#pragma once

#include <string>
#include <stdexcept>
#include <math.h>
#include <iostream>
#include <vector>
#include "gmRoot.h"

#include <list>

#ifdef CMAYA
    #include <maya/MVector.h>
#endif

using namespace std;

namespace gmath
{
    // Matrices forward declaration
    class Matrix3;
    class Matrix4;

    /**
    Three-dimensional vector.

    This class can be used to represent points, vectors, normals
    or even colors. The usual vector operations are available.
    */
    class Vector3
    {
    public:
        /*------ constructors ------*/
        Vector3();
        Vector3(double inX, double inY, double inZ);
        Vector3(const Vector3& other);
        Vector3(const double* values);
        Vector3(const std::vector<double>& values); 

        ~Vector3() {}

        /*------ properties ------*/
        double x, y, z;

        /** Pointer access for direct copying. */
        double* data();
        const double* data() const;

        /*------ coordinate access ------*/
        double operator[] (int i) const;
        double& operator[] (int i);

        /*------ Arithmetic operations ------*/
        Vector3 operator + (const Vector3& other) const;
        Vector3 operator - (const Vector3& other) const;
        Vector3 operator - () const;
        Vector3 operator * (double scalar) const;
        Vector3 operator * (const Vector3& other) const;
        Vector3 operator * (const Matrix3& mat) const;
        Vector3 operator * (const Matrix4& mat) const;
        Vector3 operator / (double scalar) const;
        Vector3 operator / (const Vector3& other) const;

        /*------ Arithmetic updates ------*/
        Vector3& operator += (const Vector3& other);
        Vector3& operator -= (const Vector3& other);
        Vector3& operator *= (double scalar);
        Vector3& operator *= (const Vector3& other);
        Vector3& operator *= (const Matrix3& mat);
        Vector3& operator *= (const Matrix4& mat);
        Vector3& operator /= (double scalar);
        Vector3& operator /= (const Vector3& other);

        /*------ Arithmetic comparisons ------*/
        bool operator == (const Vector3& other) const;
        bool operator != (const Vector3& other) const;

        /*------ Arithmetic assignment ------*/
        void operator = (const Vector3& other);

        /*------ methods ------*/
        Vector3 clone() const;

        /** Set the three properties (x, y, z), with the given arguments
            @param inX The wanted value for x
            @param inY The wanted value for y
            @param inZ The wanted value for z */
        void set(double inX, double inY, double inZ);
        void set(const double* values);
        void set(const std::vector<double>& values);

        /** Perform the cross product between this vector and the given vector */
        Vector3 cross(const Vector3& other) const;
        void crossInPlace(const Vector3& other);

        /** Perform the cross product between this vector and the given vector,
         *  and always return a normalised vector.
         *  This function is useful to reduce lines of code. */
        Vector3 crossNormalize(const Vector3& other) const;
        void crossNormalizeInPlace(const Vector3& other);

        /** Perform the dot product between this vector and the given vector */
        double dot(const Vector3& other) const;

        /** Calculate the length of this vector */
        double length() const;
        double squaredLength() const;

        /** Find the distance between this vector and the given vector */
        double distance(const Vector3& other) const;
        double squaredDistance(const Vector3& other) const;

        Vector3 normalize() const;
        Vector3& normalizeInPlace();

        Vector3 inverse() const;
        Vector3& inverseInPlace();

        Vector3 negate() const;
        Vector3& negateInPlace();

        /** Return angle (in radians) between this vector and the given vector.
            @note: Remember to normalize the vectors before to call this method. */
        double angle(const Vector3& other) const;

        /** Return the reflection to a surface.
            @param normal is The Vector3 which represent the surface normal.
                          Note that normal should be normalized */
        Vector3 reflect(const Vector3& normal) const;

        /** Reflect this vector to a surface.
            @param normal is The Vector3 which represent the surface normal.
                          Note that normal should be normalized */
        void reflectInPlace(const Vector3& normal);

        /** Return the transmitted vector.
            If the returned vector is zero then there is no transmitted light because
            of total internal reflection.
            @param normal The Vector3 which represent the surface normal.
                          Note that normal should be normalized
            @param eta The relative index of refraction. */
        Vector3 refract(const Vector3& normal, double eta) const;

        /** Transmit this vector.
            If the returned vector is zero then there is no transmitted light because
            of total internal reflection.
            @param normal The Vector3 which represent the surface normal.
                          Note that normal should be normalized
            @param eta The relative index of refraction. */
        void refractInPlace(const Vector3& normal, double eta);

        Vector3 mirror(const Vector3& normal) const;
        void mirrorInPlace(const Vector3& normal);
        Vector3 mirror(CartesianPlane plane=CartesianPlane::YZ) const;
        void mirrorInPlace(CartesianPlane plane=CartesianPlane::YZ);

        /** interpolate between this vector and the given one. return a new vector */
        Vector3 linearInterpolate(const Vector3& other, double weight) const;

        /** interpolate between this vector and the given one. At the end store the result on this vector */
        void linearInterpolateInPlace(const Vector3& other, double weight);


        std::string toString() const;

        // Special Vectors.
        static const Vector3 XAXIS;
        static const Vector3 YAXIS;
        static const Vector3 ZAXIS;

        static const Vector3 N_XAXIS;
        static const Vector3 N_YAXIS;
        static const Vector3 N_ZAXIS;

        static const Vector3 ZERO;

        #ifdef CMAYA
            void fromMayaVector(const MVector&mvector);
            MVector toMayaVector() const;
        #endif
    };

    /** from an Axis enumerator gets the correspondent Vector3 */
    Vector3 getVector3FromAxis(Axis axis);
}
