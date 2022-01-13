#include "gmEuler.h"

using namespace std;

namespace gmath {

    /*------ Constructors ------*/

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

    Euler::Euler(const double* values, Unit inUnit)
    {
        x = values[0];
        y = values[1];
        z = values[2];

        unit = inUnit;
    }

    Euler::Euler(const std::vector<double>& values, Unit inUnit)
    {
        x = values[0];
        y = values[1];
        z = values[2];

        unit = inUnit;
    }

    /*------ Data access ------*/

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

    /*------ Comparisons ------*/

    bool Euler::operator == (const Euler &other) const
    {
        return (
            almostEqual(x, other.x) &&
            almostEqual(y, other.y) &&
            almostEqual(z, other.z) );
    }

    bool Euler::operator != (const Euler &other) const
    {
        return (
            !almostEqual(x, other.x) ||
            !almostEqual(y, other.y) ||
            !almostEqual(z, other.z) );
    }

    /*------ Methods ------*/

    void Euler::set(const double inX, const double inY, const double inZ)
    {
        x=inX; y=inY; z=inZ;
    }

    void Euler::set(const double* values)
    {
        x=values[0]; y=values[1]; z=values[2];
    }

    void Euler::set(const std::vector<double>& values)
    {
        x=values[0]; y=values[1]; z=values[2];
    }

    Unit Euler::getUnit() const
    {
        return unit;
    }

    void Euler::setUnit(Unit inUnit)
    {
        if (unit!=inUnit)
        {
            unit = inUnit;
            if (inUnit==Unit::degrees)
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
        if (unit==Unit::degrees)
        {
            return Euler( (*this) );
        }
        else
        {
           return Euler(
                gmath::toDegrees(x),
                gmath::toDegrees(y),
                gmath::toDegrees(z),
                Unit::degrees
                );
        }
    }

    Euler Euler::toRadians() const
    {
        if (unit==Unit::radians)
        {
            return Euler( (*this) );
        }
        else
        {
            return Euler(
                gmath::toRadians(x),
                gmath::toRadians(y),
                gmath::toRadians(z),
                Unit::radians
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
        if (unit==Unit::degrees)
            oss << " - degrees -";
        else
            oss << " - radians -"; 

        return oss.str();
    }
}