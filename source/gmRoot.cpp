#include "gmRoot.h"

namespace gmath
{
	std::string GMathError::prefix = "GMathError: ";

    // const double EPSILON = 1e-08;
    // const double PI = 4.0*atan(1.0);
    // const double HALFPI = PI*0.5;
    // const double MAX = DBL_MAX;
    // const double MIN = -DBL_MAX;
    // const double SMALLEST = DBL_MIN;


    double acos (double x)
    {
        if (-(double)1 < x) {
            if (x < (double)1) {
                return (double) ::acos((double)x);
            }
            else {
                return (double)0;
            }
        }
        else {
            return PI;
        }
    }

    double asin (double x)
    {
        if (-(double)1 < x) {
            if (x < (double)1) {
                return (double) ::asin((double)x);
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
        return x*(PI/(double)180.0);
    }

    double toDegrees(double x)
    {
        return x*((double)180.0/PI);
    }
}