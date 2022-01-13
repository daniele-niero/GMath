#include "gmVector4.h"

using namespace std;

namespace gmath {

    /*------ Constructors ------*/
    Vector4::Vector4()
    {
        x=0.0;
        y=0.0;
        z=0.0;
        w=0.0;
    }

    Vector4::Vector4(double inX, double inY, double inZ, double inW)
    {
        x = inX;
        y = inY;
        z = inZ;
        w = inW;
    }

    Vector4::Vector4(const Vector4 & other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }

    Vector4::Vector4(const double* values)
    {
        set(values);
    }

    Vector4::Vector4(const std::vector<double>& values)
    {
        set(values);
    }

    /*------ Coordinates access ------*/
    double Vector4::operator[] (int i) const
    {
        if (i>3){
            throw out_of_range("gmath::Vector4: index out of range");
        }
        return *(&x+i);
    }

    double& Vector4::operator[] (int i)
    {
        if (i>3){
            throw out_of_range("gmath::Vector4: index out of range");
        }
        return *(&x+i);
    }

    double* Vector4::data()
    {
    	return &x;
    }

    const double* Vector4::data() const
    {
    	return &x;
    }

    /*------ Arithmetic operations ------*/
    Vector4 Vector4::operator + (const Vector4 & other) const
    {
        Vector4 newVector4(x+other.x, y+other.y, z+other.z, w+other.w);

        return newVector4;
    }

    Vector4 Vector4::operator - (const Vector4 & other) const
    {
        Vector4 newVector4(x-other.x, y-other.y, z-other.z, w-other.w);
        return newVector4;
    }

    Vector4 Vector4::operator - () const
    {
        Vector4 newVector4(-x, -y, -z, -w);
        return newVector4;
    }

    Vector4 Vector4::operator * (double scalar) const
    {
        Vector4 newVector4(x*scalar, y*scalar, z*scalar, w*scalar);

        return newVector4;
    }

    Vector4 Vector4::operator / (double scalar) const
    {
        Vector4 newVector4;
        if (scalar == 0.0)
        {
            newVector4.x = NAN;
            newVector4.y = NAN;
            newVector4.z = NAN;
            newVector4.w = NAN;
        }
        else
        {
            newVector4.x = x/scalar;
            newVector4.y = y/scalar;
            newVector4.z = z/scalar;
            newVector4.w = w/scalar;
        }

        return newVector4;
    }

    /*------ Arithmetic updates ------*/
    Vector4& Vector4::operator += (const Vector4 & other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    Vector4& Vector4::operator -= (const Vector4 & other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    Vector4& Vector4::operator *= (double scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    Vector4& Vector4::operator /= (double scalar)
    {
        if (scalar == 0.0)
        {
            x = NAN;
            y = NAN;
            z = NAN;
            w = NAN;
        }
        else
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
        }
        return *this;
    }

    /*------ Comparisons ------*/
    bool Vector4::operator == (const Vector4 & other) const
    {
        return (almostEqual(x, other.x) && 
                almostEqual(y, other.y) && 
                almostEqual(z, other.z) &&
                almostEqual(w, other.w));
    }

    bool Vector4::operator != (const Vector4 & other) const
    {
        return (!almostEqual(x, other.x) || 
                !almostEqual(y, other.y) || 
                !almostEqual(z, other.z) ||
                !almostEqual(w, other.w));
    }

    /*------ Assignments ------*/
    void Vector4::operator = (const Vector4 & other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }
    
    /*------ Methods ------*/
    void Vector4::set(double inX, double inY, double inZ, double inW)
    {
        x = inX;
        y = inY;
        z = inZ;
        w = inW;
    }

    void Vector4::set(const double* values)
	{
	    x = values[0];
	    y = values[1];
	    z = values[2];
	    w = values[3];
	}
    
    void Vector4::set(const std::vector<double>& values)
    {
        if (values.size()!=4)
            throw out_of_range("gmath::Matrix4: values must be of 4 elements");
        
        this->x = values[0];
        this->y = values[1];
        this->z = values[2];
        this->w = values[3];
    }

    double Vector4::dot(const Vector4 & other) const
    {
        return x*other.x + y*other.y + z*other.z + w*other.w;
    }

    double Vector4::length() const
    {
        double dot = x*x + y*y + z*z + w*w;
        return sqrt( dot );
    }

    double Vector4::squaredLength() const
    {
        return x*x + y*y + z*z + w*w;
    }

    Vector4 Vector4::normalize() const
    {
        double len = length();

        double nlen;
        if (isCloseToZero(len))
        {
            nlen = 1.0;
        }
        else
        {
            nlen = 1.0/len;
        }

        return Vector4(x*nlen, y*nlen, z*nlen, w*nlen);
    }

    void Vector4::normalizeInPlace()
    {
        double len = length();
        
        double nlen;
        if (isCloseToZero(len))
        {
            nlen = 1.0;
        }
        else
        {
            nlen = 1.0/len;
        }

        x *= nlen;
        y *= nlen;
        z *= nlen;
        w *= nlen;
    }

    std::string Vector4::toString() const
    {
        std::stringstream oss;
        oss << "gmath::Vector4(" << x << ", " << y << ", " << z << ", " << w << ");";

        return oss.str();
    }

    #ifdef CMAYA
        void Vector4::fromMayaPoint(const MPoint &mpoint)
        {
            double dest[4];
            mpoint.get(dest);
            this->set(dest);
        }

        MPoint Vector4::toMayaPoint() const 
        {
            return MPoint(this->data());
        }
    #endif
}