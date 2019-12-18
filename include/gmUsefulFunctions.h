#pragma once

#include "gmRoot.h"
#include "gmEuler.h"
#include "gmVector3.h"
#include "gmVector4.h"
#include "gmMatrix3.h"
#include "gmMatrix4.h"
#include "gmQuaternion.h"
#include "gmXfo.h"

namespace gmath
{
    bool almostEqual(const Vector3& a, const Vector3& b, double precision=DBL_MIN);
    bool almostEqual(const Vector4& a, const Vector4& b, double precision=DBL_MIN);
    bool almostEqual(const Euler& a, const Euler& b, double precision=DBL_MIN);
    bool almostEqual(const Quaternion& a, const Quaternion& b, double precision=DBL_MIN);
    bool almostEqual(const Matrix3& a, const Matrix3& b, double precision=DBL_MIN);
    bool almostEqual(const Matrix4& a, const Matrix4& b, double precision=DBL_MIN);
    bool almostEqual(const Xfo& a, const Xfo& b, double precision=DBL_MIN);

    enum class IntersectionType
    {
        UNDEFINED = 0,
        INTERSECTION = 1,
        NO_INTERSECTION = 2,
        PARRALLEL = 3,
        LAYS_ON_PLANE = 4,
        TOUCH_ON_ONE_POINT = 5
    };

    void aim(Matrix3& result, const Vector3& direction, const Vector3& upVector, Axis primaryAxis, Axis secondaryAxis);
    void aim(Quaternion& result, const Vector3& direction, const Vector3& upVector, Axis primaryAxis, Axis secondaryAxis);
    void aim(Xfo& result, const Vector3& direction, const Vector3& upVector, Axis primaryAxis, Axis secondaryAxis);

    /**
     Orient a Mat33 to point at 'direction'.
     This matrix will have the Y axis pointing to 'direction' and the X axis pointing to 'upVector' 
     */
    void fastAim(Matrix3& result, const Vector3& direction, const Vector3& upVector);

    /**
     Orient a Quat to point at 'direction'.
     This matrix will have the Y axis pointing to 'direction' and the X axis pointing to 'upVector' 
     */
    void fastAim(Quaternion& result, const Vector3& direction, const Vector3& upVector);

    /**
     Orient a Xfo to point at 'direction'.
     This matrix will have the Y axis pointing to 'direction' and the X axis pointing to 'upVector'
     */
    void fastAim(Xfo& result, const Vector3& direction, const Vector3& upVector);

    double distanceToPlane(const Vector3& planeOrigin, const Vector3& planeNormal, const Vector3& point);
    double distanceToLine(const Vector3& start, const Vector3& end, const Vector3& point, bool infiniteLine=true);

    /**
     Finds the closest point on a segment to a given point in space.
     */
    Vector3 closestPointToLine(const Vector3& start, const Vector3& end, const Vector3& point, bool infiniteLine=true);

    IntersectionType intersectLinePlane(Vector3& outVector, const Vector3& segP0, const Vector3& segP1, const Vector3& planeNormal, const Vector3& planePoint, bool infiniteLine=true);
    
    IntersectionType intersectPlanePlane(Vector3& outP1, Vector3& outP2, const Vector3& plane1Point, const Vector3& plane1Normal, const Vector3& plane2Point, const Vector3& plane2Normal);

    IntersectionType intersectCirclePlane(Vector3& outP1, Vector3& outP2, const Vector3& circleCenter, const Vector3& circleNormal, const double& circleRadius, const Vector3& planeNormal, const Vector3& planePoint);

    /**
     @param result the point of intersection, if intersection occurs. When the solution will give two points, this
                   will be the one along the direction of the line.
     @param lineOrigin origin of the line
     @param pointOnLine point on the line
     @param sphereCenter the sphere center
     @param sphereRadius the sphere radius
     */
    IntersectionType intersectLineSphere(Vector3& result, const Vector3& lineOrigin, const Vector3& pointOnLine, const Vector3& sphereCenter, const double& sphereRadius);
}