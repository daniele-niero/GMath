#include "gmEuler.h"

using namespace std;

namespace gmath {

    Euler::Euler(Unit inUnit)
    {
        x=0.0;
        y=0.0;
        z=0.0;

		unit = inUnit;
    }

    Euler::Euler(const Euler& other)
    {
    	memcpy(&x, &other.x, 3*sizeof(double));
		unit = other.unit;
    }

    Euler::Euler(const double inX, const double inY, const double inZ, Unit inUnit)
    {
		x = inX; y = inY; z = inZ;
		unit = inUnit;
    }

    Euler::Euler(const Vector3& vec, Unit inUnit)
    {
    	memcpy(&x, vec.data(), 3*sizeof(double));
		unit = inUnit;
    }

    double* Euler::data()
    {
        return &x;
    }

    const double* Euler::data() const
    {
        return &x;
    }
    
    /*------ Coordinate access ------*/
    double Euler::operator[] (int i) const
    {
        if (i>2) {
            throw out_of_range("gEuler:\n\t index out of range");
        }
        return *(&x+i);
    }

    double& Euler::operator[] (int i)
    {
        if (i>2) {
            throw out_of_range("gEuler:\n\t index out of range");
        }
        return *(&x+i);
    }


    bool Euler::operator == (const Euler &other) const
    {
        return (
    		fabs(x-other.x)<EPSILON &&
    		fabs(y-other.y)<EPSILON &&
    		fabs(z-other.z)<EPSILON );
    }

    bool Euler::operator != (const Euler &other) const
    {
    	return (
    		fabs(x-other.x)>EPSILON ||
    		fabs(y-other.y)>EPSILON ||
    		fabs(z-other.z)>EPSILON );
    }


    void Euler::set(const double inX, const double inY, const double inZ)
    {
    	x=inX; y=inY; z=inZ;
    }

    Euler::Unit Euler::getUnit() const
    {
        return unit;
    }

    void Euler::setUnit(Unit inUnit)
    {
        if (unit!=inUnit)
        {
            unit = inUnit;
            if (inUnit==degrees)
            {
                x = gmath::toDegrees(x);
                y = gmath::toDegrees(y);
                z = gmath::toDegrees(z);
            }
            else
            {
                x = gmath::toRadians(x);
                y = gmath::toRadians(y);
                z = gmath::toRadians(z);
            }
        }
    }

    Euler Euler::toDegrees() const
    {
        if (unit==degrees)
        {
            return Euler( (*this) );
        }
        else
        {
    	   return Euler(
    			gmath::toDegrees(x),
			    gmath::toDegrees(y),
			    gmath::toDegrees(z),
                degrees
    			);
        }
    }

    Euler Euler::toRadians() const
    {
    	if (unit==radians)
        {
            return Euler( (*this) );
        }
        else
        {
            return Euler(
			    gmath::toRadians(x),
			    gmath::toRadians(y),
			    gmath::toRadians(z),
                radians
    			);
        }
    }

    Vector3 Euler::toVector() const
    {
    	return Vector3(x, y, z);
    }

    std::string Euler::toString() const
    {
        std::stringstream oss;
        oss << "gmath::Euler(" << x << ", " << y << ", " << z << ");";
        if (unit==degrees)
            oss << " - degrees -";
        else
            oss << " - radians -"; 

        return oss.str();
    }
}