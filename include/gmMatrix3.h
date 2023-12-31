#pragma once

#include "gmRoot.h"
#include "gmVector3.h"
#include "gmEuler.h"

namespace gmath
{
    // Quaternion forward declaration
    class Quaternion;

    /** Matrix class (3x3). @n
            [Xx, Xy, Xz] @n
            [Yx, Yy, Yz] @n
            [Zx, Zy, Zz] @n

        This class represents a 3x3 matrix that can be used to store
        rotations transformations. */
    class Matrix3
    {
    private:
        /*------ properties ------*/
        double _data[9];

    public:
        /*------ constructors ------*/
        Matrix3();
        Matrix3(double xx, double xy, double xz,
                double yx, double yy, double yz,
                double zx, double zy, double zz);
        Matrix3(const Matrix3 &other);
        Matrix3(const Vector3 &axisX,
                const Vector3 &axisY,
                const Vector3 &axisZ);
        Matrix3(const Quaternion& quat);
        Matrix3(const double* values);
        Matrix3(const std::vector<double>& values);

        /** Pointer access for direct copying. */
        double* data();
        const double* data() const;

        /*------ coordinate access ------*/
        double operator[] (int i) const;
        double &operator[] (int i);
        double operator() (int row, int col) const;
        double &operator() (int row, int col);

        /*------ Arithmetic operations ------*/
        Matrix3 operator - () const;
        Matrix3 operator - (double value) const;
        Matrix3 operator - (const Matrix3 &other) const;
        Matrix3 operator + (double value) const;
        Matrix3 operator + (const Matrix3 &other) const;
        Matrix3 operator / (double value) const;
        Matrix3 operator * (double value) const;
        Matrix3 operator * (const Matrix3 &other) const;

        /*------ Arithmetic updates ------*/
        Matrix3& operator += (double value);
        Matrix3& operator += (const Matrix3 &other);
        Matrix3& operator -= (double value);
        Matrix3& operator -= (const Matrix3 &other);
        Matrix3& operator /= (double value);
        Matrix3& operator *= (double value);
        Matrix3& operator *= (const Matrix3 &other);

        /*------ Comparisons ------*/
        bool operator == (const Matrix3 &other) const;
        bool operator != (const Matrix3 &other) const;

        /*------ Assignment ------*/
        void operator = (const Matrix3 &other);

        /*------ methods ------*/
        void setToIdentity();
        void set(double xx, double xy, double xz,
                 double yx, double yy, double yz,
                 double zx, double zy, double zz);
        void set(const double* values);
        void set(const std::vector<double>& values);

        Vector3 getRow(unsigned int i) const;
        void setRow(unsigned int i, const Vector3 &vec);

        Vector3 getAxisX() const;
        Vector3 getAxisY() const;
        Vector3 getAxisZ() const;
        void setAxisX(const Vector3& vec);
        void setAxisY(const Vector3& vec);
        void setAxisZ(const Vector3& vec);

        void setScale(const Vector3 &scale);
        void setScale(double sX, double sY, double sZ);
        void addScale(const Vector3 &scale);
        void addScale(double sX, double sY, double sZ);
        Vector3 getScale() const;

        /** Remember to take out scale first */
        void fromQuaternion(const Quaternion& rotationQuat);
        Quaternion toQuaternion() const;
        void toQuaternion(Quaternion &outQuaternion) const;

        void fromEuler(const double& angleX, const double& angleY, const double& angleZ, RotationOrder order=RotationOrder::XYZ);
        void fromEuler(const Euler &rotation, RotationOrder order=RotationOrder::XYZ);
        Euler toEuler(RotationOrder order=RotationOrder::XYZ) const;
        void toEuler(Euler& euler, RotationOrder order=RotationOrder::XYZ) const;

        Matrix3 transpose() const;
        void transposeInPlace();

        /** The determinant of a matrix is a floating point value which is used to
            indicate whether the matrix has an inverse or not. If zero, then no inverse exists. */
        double determinant() const;

        Matrix3 inverse() const;
        void inverseInPlace();

        Matrix3 orthogonal() const;
        void orthogonalInPlace();
        
        /** Returns a rotation matrix that rotates one vector into another.

            The generated rotation matrix will rotate the vector _from into
            the vector to. _from and to must be unit vectors!

            This method is based on the code from:

            Tomas Moller, John Hughes
            Efficiently Building a Matrix to Rotate One Vector to Another
            Journal of Graphics Tools, 4(4):1-4, 1999
            http://www.acm.org/jgt/papers/MollerHughes99/ */
        void fromVectorToVector(const Vector3 &fromVec, const Vector3 &toVec);
        void fromAxisAngle(const Vector3 &axis, double angle);

        /** Look from pos to target.

            The resulting transformation is a rotation Matrix where the primaryAxis points to target.
            The secondaryAxis is as close as possible to the up vector. */
        void lookAt(const Vector3 &pointAt, const Vector3 &normal, Axis primaryAxis=Axis::POSZ, Axis secondaryAxis=Axis::POSY);
        static Matrix3 createLookAt(const Vector3 &pointAt, const Vector3 &normal, Axis primaryAxis=Axis::POSZ, Axis secondaryAxis=Axis::POSY);

        std::string toString() const;

        // Special Matrices.
        static const Matrix3 IDENTITY;
    };
}
