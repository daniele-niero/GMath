#include "gmRoot.h"

namespace gmath
{
	std::string GMathError::prefix = "GMathError: ";

    // const double PRECISION = 1e-08;
    // const double PI = 4.0*atan(1.0);
    // const double HALFPI = PI*0.5;
    // const double MAX = DBL_MAX;
    // const double MIN = -DBL_MAX;
    // const double SMALLEST = DBL_MIN;

    bool isAxisX(Axis axis)
    {
        return (axis == Axis::POSX || axis == Axis::NEGX);
    }

    bool isAxisY(Axis axis)
    {
        return (axis == Axis::POSY || axis == Axis::NEGY);
    }

    bool isAxisZ(Axis axis)
    {
        return (axis == Axis::POSZ || axis == Axis::NEGZ);
    }

    double acos (double x)
    {
        if (-1.0 < x) {
            if (x < 1.0) {
                return std::acos(x);
            }
            else {
                return 0.0;
            }
        }
        else {
            return PI;
        }
    }

    double asin (double x)
    {
        if (-1.0 < x) {
            if (x < 1.0) {
                return std::asin(x);
            }
            else {
                return HALFPI;
            }
        }
        else {
            return -HALFPI;
        }
    }

    double toRadians(double x)
    {
        return x*(PI/180.0);
    }

    double toDegrees(double x)
    {
        return x*(180.0/PI);
    }
}