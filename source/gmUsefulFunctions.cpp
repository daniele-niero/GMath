#include "gmUsefulFunctions.h"

namespace gmath {

    bool almostEqual(const Vector3 &a, const Vector3 &b, double precision) {
        for (unsigned int i=0; i<3; i++) {
            if (!almostEqual(a[i], b[i], precision))
                return false;
        }
        return true;
    }

    bool almostEqual(const Euler &a, const Euler &b, double precision) {
        for (unsigned int i=0; i<3; i++) {
            if (!almostEqual(a[i], b[i], precision))
                return false;
        }
        return true;
    }

    bool almostEqual(const Vector4 &a, const Vector4 &b, double precision) {
        for (unsigned int i=0; i<4; i++) {
            if (!almostEqual(a[i], b[i], precision))
                return false;
        }
        return true;
    }

    bool almostEqual(const Quaternion &a, const Quaternion &b, double precision) {
        for (unsigned int i=0; i<4; i++) {
            if (!almostEqual(a[i], b[i], precision))
                return false;
        }
        return true;
    }

    bool almostEqual(const Matrix3 &a, const Matrix3 &b, double precision) {
        for (unsigned int i=0; i<9; i++) {
            if (!almostEqual(a[i], b[i], precision))
                return false;
        }
        return true;
    }

    bool almostEqual(const Matrix4 &a, const Matrix4 &b, double precision) {
        for (unsigned int i=0; i<16; i++) {
            if (!almostEqual(a[i], b[i], precision))
                return false;
        }
        return true;
    }

    bool almostEqual(const Xfo &a, const Xfo &b, double precision) {
        if (!almostEqual(a.tr, b.tr, precision))
            return false;
        if (!almostEqual(a.ori, b.ori, precision))
            return false;
        if (!almostEqual(a.sc, b.sc, precision))
            return false;
        return true;
    }


    void aim(Matrix3& result, const Vector3& direction, const Vector3& upVector, Axis primaryAxis, Axis secondaryAxis)
    {
        Vector3 primary   = direction.normalize();
        Vector3 secondary = upVector.normalize();

        if ((int)primaryAxis<0)
            primary *= -1.0;

        if ((int)secondaryAxis<0)
            secondary *= -1.0;

        Vector3 tertiary = primary.cross(secondary).normalize();
        secondary = tertiary.cross(primary).normalize();

        if ( isAxisX(primaryAxis) )
        {
            if ( isAxisY(secondaryAxis) ) 
            {
                result.setRow(0, primary);
                result.setRow(1, secondary);
                result.setRow(2, tertiary);
            }
            else if ( isAxisZ(secondaryAxis) )
            {
                result.setRow(0, primary);
                result.setRow(1, -tertiary);
                result.setRow(2, secondary);
            }
        }
        else if ( isAxisY(primaryAxis) )
        {
            if ( isAxisX(secondaryAxis) )
            {
                result.setRow(0, secondary);
                result.setRow(1, primary);
                result.setRow(2, -tertiary);
            }
            else if ( isAxisZ(secondaryAxis) )
            {
                result.setRow(0, tertiary);
                result.setRow(1, primary);
                result.setRow(2, secondary);
            }
        }
        else if ( isAxisZ(primaryAxis) )
        {
            if ( isAxisX(secondaryAxis) )
            {
                result.setRow(0, secondary);
                result.setRow(1, tertiary);
                result.setRow(2, primary);
            }
            else if ( isAxisY(secondaryAxis) )
            {
                result.setRow(0, -tertiary);
                result.setRow(1, secondary);
                result.setRow(2, primary);
            }
        }
    }

    void aim(Quaternion& result, const Vector3& direction, const Vector3& upVector, Axis primaryAxis, Axis secondaryAxis)
    {
        Matrix3 mresult;
        aim(mresult, direction, upVector, primaryAxis, secondaryAxis);
        result.fromMatrix3(mresult);
    }

    void aim(Xfo& result, const Vector3& direction, const Vector3& upVector, Axis primaryAxis, Axis secondaryAxis)
    {
        aim(result.ori, direction, upVector, primaryAxis, secondaryAxis);
    }

    void fastAim(Matrix3& result, const Vector3& direction, const Vector3& upVector)
    {
        Vector3 primary = direction.normalize();
        Vector3 secondary = primary.cross(upVector.normalize()).cross(primary).normalize();
        Vector3 tertiary = secondary.cross(primary).normalize();

        result.setRow(0, secondary);
        result.setRow(1, primary);
        result.setRow(2, tertiary);
    }

    void fastAim(Quaternion& result, const Vector3& direction, const Vector3& upVector)
    {
        Matrix3 mresult;
        fastAim(mresult, direction, upVector);
        result.fromMatrix3(mresult);
    }

    void fastAim(Xfo& result, const Vector3& direction, const Vector3& upVector)
    {
        fastAim(result.ori, direction, upVector);
    }


    double distanceToPlane(const Vector3& planeOrigin, const Vector3& planeNormal, const Vector3& point)
    {
        Vector3 p = point - planeOrigin;
        return p.dot(planeNormal.normalize());
    }


    double distanceToLine(const Vector3& start, const Vector3& end, const Vector3& point, bool infiniteLine)
    {
        Vector3 line   = end-start;
        Vector3 p = point-start;

        double lineLength = line.length();
        if ( isCloseToZero(lineLength) || !infiniteLine)
        {
            return p.length();
        }
        else
        {
            line.normalizeInPlace();
            // project point on line
            double d = p.dot(line);
            if (!infiniteLine)
            {
                if (d<0.0)
                    return p.length();
                else if (d>lineLength)
                    return (point-end).length();
            }

            d = abs(d);
            double ps = p.length();
            return sqrt( (ps*ps) - (d*d) );
        }
    }


    Vector3 closestPointToLine(const Vector3& start, const Vector3& end, const Vector3& point, bool infiniteLine)
    {
        Vector3 line   = end-start;
        Vector3 spoint = point-start;

        double lineLength = line.length();
        if ( isCloseToZero(lineLength) || !infiniteLine)
        {
            return start;
        }
        else
        {
            line.normalizeInPlace();
            // project point on line
            double distance = spoint.dot(line);
            if (!infiniteLine)
                distance = clamp(distance, 0.0, lineLength);
            return start + (line*distance);
        }
    }


    IntersectionType intersectLinePlane(Vector3& outVector, const Vector3& segP0, const Vector3& segP1, const Vector3& planeNormal, const Vector3& planePoint, const bool infiniteLine)
    {
        Vector3 segment = segP1 - segP0;
        Vector3 planePointSegment = planePoint - segP0;

        double dotA = segment.dot(planeNormal);
        double dotB = planePointSegment.dot(planeNormal);

        if (isCloseToZero(dotA))
        {
            if (isCloseToZero(dotB))
                return IntersectionType::LAYS_ON_PLANE;
            else
                return IntersectionType::PARRALLEL;
        }

        // they are not parallel
        // compute intersection
        double x = (planePointSegment.dot(planeNormal))*(1.0 / dotA);
        if ((x < 0.0 || x > 1.0) && !infiniteLine)
            return IntersectionType::NO_INTERSECTION;

        outVector = (segP1*x) + (segP0*(1.0 - x));
        return IntersectionType::INTERSECTION;
    }


    IntersectionType intersectPlanePlane(Vector3& outOrigin, Vector3& outDirection, const Vector3& plane1Point, const Vector3& plane1Normal, const Vector3& plane2Point, const Vector3& plane2Normal)
    {
        double dot = plane1Normal.dot(plane2Normal);

        if (almostEqual(abs(dot), 1.0)) // planes are parallel
            return IntersectionType::PARRALLEL;

        // the perpendicular to both planes' normals is the direction vector of the line we
        // are looking for
        outDirection = plane1Normal.cross(plane2Normal);
        outDirection.normalizeInPlace();
        Vector3 v = outDirection.cross(plane1Normal);  // vector perpendicular to intersection line
        v.normalizeInPlace();

        return intersectLinePlane(outOrigin, plane1Point, v + plane1Point, plane2Normal, plane2Point, true);
    }


    IntersectionType intersectCirclePlane(Vector3& outP1, Vector3& outP2, const Vector3& circleCenter, const Vector3& circleNormal, const double& circleRadius, const Vector3& planeNormal, const Vector3& planePoint)
    {
        Vector3 lineP1;
        Vector3 lineP2;
        IntersectionType intersecPlanePlane = intersectPlanePlane(lineP1, lineP2, planePoint, planeNormal, circleCenter, circleNormal);

        if (intersecPlanePlane == IntersectionType::INTERSECTION)
        {
            Vector3 centerToLine = closestPointToLine(lineP1, lineP2, circleCenter);
            double distCenterLine = (centerToLine - circleCenter).length();

            if (distCenterLine > circleRadius)// no contact
            {
                return IntersectionType::NO_INTERSECTION;
            }
            else if (distCenterLine == circleRadius) // there is only one contact point
            {
                outP1 = centerToLine;
                outP2 = centerToLine;
                return IntersectionType::INTERSECTION;
            }

            // knowing the radius and now the distance between centre and intersection line,
            // with the Pythagoras' theorem we can find the distance between centerToLine and circumference
            double distCenterLineCircle = sqrt((circleRadius*circleRadius) - (distCenterLine*distCenterLine));

            Vector3 lineDir = lineP2 - lineP1;
            lineDir.normalizeInPlace();

            // the points are...
            outP1 = (lineDir*distCenterLineCircle) + centerToLine;
            outP2 = ((lineDir*-1.0)*distCenterLineCircle) + centerToLine;

            return IntersectionType::INTERSECTION;
        }

        return IntersectionType::NO_INTERSECTION;
    }
}