#pragma once

#include <memory>

#include "gmVector3.h"
#include "gmQuaternion.h"
#include "gmMatrix4.h"

#ifdef CMAYA
#include <maya/MMatrix.h>
#endif

namespace gmath
{   
    /** The Xfo type represents a 3D transform. 
        It uses a Vector3 for translation and scaling as well as a Quaternion for its rotation. 
        It was inspired by FabricEngine's own Xfo type 

        @seealso Quat, Vec3, Euler, Mat44, Mat33 */
    class Xfo
    {
    public:
        /*------ properties ------*/
        shared_ptr<Quaternion> ori;
        shared_ptr<Vector3> tr;
        shared_ptr<Vector3> sc;

        /*------ constructors ------*/
        Xfo();
        Xfo(const Xfo& other);
        Xfo(const Vector3& tr);
        Xfo(const Quaternion& ori);
        Xfo(const Vector3& tr, const Quaternion& ori);
        Xfo(const Quaternion& ori, const Vector3& tr, const Vector3& sc);
        Xfo(const Matrix4& mat);
        Xfo(const double& eulerX, const double& eulerY, const double& eulerZ, 
            const double& trX, const double& trY, const double& trZ,
            const double& scX, const double& scY, const double& scZ);

        /*------ Arithmetic operations ------*/
        Xfo operator * (const Xfo& other) const;

        /*------ Arithmetic updates ------*/
        Xfo& operator *= (const Xfo& other);

        /*------ Arithmetic comparisons ------*/
        bool operator == (const Xfo& other) const;
        bool operator != (const Xfo& other) const;

        /*------ Arithmetic assignment ------*/
        void operator = (const Xfo& other);

        /*------ methods ------*/
        Xfo clone() const;
        
        void setToIdentity();
        void fromMatrix4(const Matrix4& mat);
        Matrix4 toMatrix4() const;
        Vector3 transformVector(const Vector3& vec) const;
        Xfo inverse() const;
        Xfo& inverseInPlace();
        Vector3 inverseTransformVector(const Vector3& vec) const;
        Xfo slerp(const Xfo& other, const double& t) const;
        Xfo& slerpInPlace(const Xfo& other, const double& t);
        double distanceTo(const Xfo& other) const;

        Xfo mirror(const Vector3& center, const Vector3& normal, 
                   Axis primary=Axis::POSY, Axis secondary=Axis::POSZ) const;
        Xfo& mirrorInPlace(const Vector3& center, const Vector3& normal, 
                           Axis primary=Axis::POSY, Axis secondary=Axis::POSZ);

        Xfo mirror(CartesianPlane plane=CartesianPlane::YZ) const;
        Xfo& mirrorInPlace(CartesianPlane plane=CartesianPlane::YZ);

        std::string toString() const;

        #ifdef CMAYA
            void fromMayaMatrix(const MMatrix mmatrix);
            MMatrix toMayaMatrix() const;
        #endif
    };

    #ifdef CMAYA

        Xfo getGlobalXfo(const MDagPath &path);
        Xfo getGlobalXfo(const std::string &dagName);

        void setGlobalXfo(MDagPath &path, const Xfo &xfo);
        void setGlobalXfo(const std::string &dagName, const Xfo &xfo);

        Xfo getLocalXfo(const MDagPath &path);
        Xfo getLocalXfo(const std::string &dagName);
        
        void setLocalXfo(MDagPath &path, const Xfo &xfo);
        void setLocalXfo(const std::string &dagName, const Xfo &xfo);

    #endif
}