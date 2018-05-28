#pragma once

#include "gmRoot.h"
#include "gmVector3.h"
#include "gmMatrix3.h"
#include "gmQuaternion.h"
#include "gmXfo.h"

namespace gmath
{
    enum class IntersectionType
    {
        UNDEFINED = 0,
        INTERSECTION = 1,
        NO_INTERSECTION = 2,
        PARRALLEL = 3,
        LAYS_ON_PLANE = 4
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
}