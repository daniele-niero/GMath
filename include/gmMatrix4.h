#pragma once

#include "gmRoot.h"
#include "gmVector3.h"
#include "gmVector4.h"
#include "gmMatrix3.h"
#include "gmEuler.h"

namespace gmath
{

	// Quaternion forward declaration
	class Quaternion;

    /**
    Matrix class (4x4).
    [Xx, Xy, Xz, Xw,]
    [Yx, Yy, Yz, Yw,]
    [Zx, Zy, Zz, Zw,]
    [Px, Py, Pz, Pw]

    This class represents a 4x4 matrix that can be used to store transformations.
    This matrix is ROW MAJOR.
    */
    class Matrix4
    {
    private:
        /*------ properties ------*/
        double _data[16];
    
    public:
        /*------ constructors ------*/
        Matrix4();
        Matrix4(double xx, double xy, double xz, double xw,
                double yx, double yy, double yz, double yw,
                double zx, double zy, double zz, double zw,
                double px, double py, double pz, double pw);

        Matrix4(const Matrix4 &other);

        Matrix4(const Vector4 &row0,
                const Vector4 &row1,
                const Vector4 &row2,
                const Vector4 &row3);

        Matrix4(const Vector3 &row0,
                const Vector3 &row1,
                const Vector3 &row2,
                const Vector3 &row3);

        Matrix4(const Vector3 &row0,
                const Vector3 &row1,
                const Vector3 &row2);

        Matrix4(const Quaternion& quat);
        Matrix4(const Quaternion& quat, const Vector3& pos);

        Matrix4(const double* list);
        Matrix4(const std::vector<double>& values);

        /** Pointer access for direct copying. */
        double* data();
        const double* data() const;

        /*------ coordinate access ------*/
        double operator[] (int i) const;
        double &operator[] (int i);
        double operator() (int row, int col) const;
        double &operator() (int row, int col);

        /*------ Arithmetic operations ------*/
        Matrix4 operator + (const double &value) const;
        Matrix4 operator + (const Matrix4 &other) const;
        Matrix4 operator - (const double &value) const;
        Matrix4 operator - (const Matrix4 &other) const;
        Matrix4 operator / (const double &value) const;
        Matrix4 operator * (const double &value) const;
        Matrix4 operator * (const Matrix4 &other) const;

        /*------ Arithmetic updates ------*/
        Matrix4& operator += (const double &value);
        Matrix4& operator += (const Matrix4 &other);
        Matrix4& operator -= (const double &value);
        Matrix4& operator -= (const Matrix4 &other);
        Matrix4& operator /= (const double &value);
        Matrix4& operator *= (const double &value);
        Matrix4& operator *= (const Matrix4 &other);

        /*------ Comparisons ------*/
        bool operator == (const Matrix4 &other) const;
        bool operator != (const Matrix4 &other) const;

        /*------ Assignment ------*/
        void operator = (const Matrix4 &other);

        /*------ Sets and Gets ------*/
        void set(double xx, double xy, double xz, double xw,
                 double yx, double yy, double yz, double yw,
                 double zx, double zy, double zz, double zw,
                 double px, double py, double pz, double pw);
        void set(const double* values);
        void set(const std::vector<double>& values);

        void setToIdentity();

        Vector3 getRow(unsigned int i) const;
        Vector4 getRow2(unsigned int i) const;
        void setRow(unsigned int i, const Vector3 &vec);
        void setRow(unsigned int i, const Vector4 &vec);
        
        Vector3 getAxisX() const;
        Vector3 getAxisY() const;
        Vector3 getAxisZ() const;
        
        void setAxisX(const Vector3 &vec);
        void setAxisY(const Vector3 &vec);
        void setAxisZ(const Vector3 &vec);

        void setPosition(const Vector3 &pos);
        void setPosition(double inX, double inY, double inZ);
        void addPosition(const Vector3 &pos);
        void addPosition(double inX, double inY, double inZ);
        /** Move the matrix accordingly to its axis, no the world axis */
        void translate(const Vector3 &pos);
        void translate(double inX, double inY, double inZ);
        Vector3 getPosition() const;

        void setRotation(const Matrix3& rotationMatrix);
        void setRotation(const Quaternion& rotationQuat);
        void setRotation(const Euler &rotation, RotationOrder order=XYZ);
        void setRotation(double angleX, double angleY, double angleZ, RotationOrder order=XYZ);

        void setScale(const Vector3 &scale);
        void setScale(double sX, double sY, double sZ);
        void addScale(const Vector3 &scale);
        void addScale(double sX, double sY, double sZ);
        Vector3 getScale() const;

        /** Remember to take out scale first */
        Matrix3 toMatrix3() const;
        Quaternion toQuaternion() const;
        Euler toEuler(RotationOrder order=XYZ) const; 
        void toMatrix3(Matrix3 &outMatrix3) const;
        void toQuaternion(Quaternion &outQuaternion) const;
        void toEuler(Euler &outEuler, RotationOrder order=XYZ) const;

    	void fromMatrix3(const Matrix3 &inMat3);
    	void fromQuaternion(const Quaternion &inQuat);
    	void fromEuler(const double &angleX, const double &angleY, const double &angleZ, RotationOrder order=XYZ);
    	void fromEuler(const Euler &inEuler, RotationOrder order=XYZ);
    	
        Vector3 rotateVector(const Vector3 &vec) const;

        Matrix4 transpose() const;
        void transposeInPlace();

        /** The determinant of a matrix is a floating point value which is used to
            indicate whether the matrix has an inverse or not. If zero, then no inverse exists. */
        double determinant() const;

        Matrix4 inverse() const;
        void inverseInPlace();

        Matrix4 orthogonal() const;
        void orthogonalInPlace();

        /* Returns a rotation matrix that rotates one vector into another.

            The generated rotation matrix will rotate the vector _from into
            the vector to. _from and to must be unit vectors!

            This method is based on the code from:

            Tomas Moller, John Hughes
            Efficiently Building a Matrix to Rotate One Vector to Another
            Journal of Graphics Tools, 4(4):1-4, 1999
            http://www.acm.org/jgt/papers/MollerHughes99/ */
        void fromVectorToVector(const Vector3 &fromVec, const Vector3 &toVec);

        /** Look from pos to target.
          *
          * The resulting transformation is a rotation Matrix where the primaryAxis points to target.
          * The secondaryAxis is as close as possible to the up vector. */
        void lookAt(const Vector3 &pos, const Vector3 &pointAt, const Vector3 &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);
        // Like the previous lookAt but this one takes the position from the matrix itself
        void lookAt(const Vector3 &pointAt, const Vector3 &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);
        static Matrix4 createLookAt(const Vector3 &pos, const Vector3 &pointAt, const Vector3 &normal, Axis primaryAxis=POSZ, Axis secondaryAxis=POSY);

        void fromAxisAngle(const Vector3 &axis, double angle);

        std::string toString() const;

        // Special Matrices.
        static const Matrix4 IDENTITY;
    };

}
