#include "gmVector3.h"
#include "gmMatrix3.h"
#include "gmMatrix4.h"

using namespace std;

namespace gmath
{
    /*------ Constructors ------*/

    Vector3::Vector3()
    {
        x=0.0; 
        y=0.0;
        z=0.0; 
    }

    Vector3::Vector3(double inX, double inY, double inZ)
    {
        x = inX;
        y = inY;
        z = inZ;
    }

    Vector3::Vector3(const Vector3 & other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    Vector3::Vector3(const double* values)
    {
        set(values);
    }

    Vector3::Vector3(const vector<double>& values) 
    {
        set(values);
    }

    /*------ Coordinate access ------*/

    double Vector3::operator[] (int i) const
    {
        if (i>2) {
            throw out_of_range("gmath::Vector3 - index out of range");
        }
        return *(&x+i);
    }

    double& Vector3::operator[] (int i)
    {
        if (i>2) {
            throw out_of_range("gmath::Vector3 - index out of range");
        }
        return *(&x+i);
    }

    /*------ Data access ------*/

    double* Vector3::data()
    {
        return &x;
    }

    const double* Vector3::data() const
    {
        return &x;
    }

    /*------ Arithmetic operations ------*/

    Vector3 Vector3::operator + (const Vector3 & other) const
    {
        Vector3 newVector3(x+other.x, y+other.y, z+other.z);

        return newVector3;
    }

    Vector3 Vector3::operator - () const
    {
        Vector3 newVector3(-x, -y, -z);
        return newVector3;
    }

    Vector3 Vector3::operator - (const Vector3 & other) const
    {
        Vector3 newVector3(x-other.x, y-other.y, z-other.z);
        return newVector3;
    }

    Vector3 Vector3::operator * (double scalar) const
    {
        Vector3 newVector3(x*scalar, y*scalar, z*scalar);

        return newVector3;
    }

    Vector3 Vector3::operator * (const Vector3 & other) const
    {
        Vector3 newVector3(x*other.x, y*other.y, z*other.z);

        return newVector3;
    }

    Vector3 Vector3::operator * (const Matrix3 &mat) const
    {
        Vector3 retVec(
            mat.data()[0] * this->x + mat.data()[3] * this->y + mat.data()[6] * this->z,
            mat.data()[1] * this->x + mat.data()[4] * this->y + mat.data()[7] * this->z,
            mat.data()[2] * this->x + mat.data()[5] * this->y + mat.data()[8] * this->z
            );
        return retVec;
    }

    Vector3 Vector3::operator * (const Matrix4 &mat) const
    {
        Vector3 retVec(
            mat.data()[0] * this->x + mat.data()[4] * this->y + mat.data()[8]  * this->z + mat.data()[12],
            mat.data()[1] * this->x + mat.data()[5] * this->y + mat.data()[9]  * this->z + mat.data()[13],
            mat.data()[2] * this->x + mat.data()[6] * this->y + mat.data()[10] * this->z + mat.data()[14]
            );
        return retVec;
    }

    Vector3 Vector3::operator / (double scalar) const
    {
        Vector3 newVector3;
        if (scalar == 0.0)
        {
            newVector3.x = NAN;
            newVector3.y = NAN;
            newVector3.z = NAN;
        }
        else
        {
            newVector3.x = x/scalar;
            newVector3.y = y/scalar;
            newVector3.z = z/scalar;
        }

        return newVector3;
    }

    Vector3 Vector3::operator / (const Vector3 & other) const
    {
        Vector3 newVector;

        if (other.x == 0.0)
            newVector.x = NAN;
        else
            newVector.x = x/other.x;

        if (other.y == 0.0)
            newVector.y = NAN;
        else
            newVector.y = y/other.y;

        if (other.z == 0.0)
            newVector.z = NAN;
        else
            newVector.z = z/other.z;
            
        return newVector;
    }

    /*------ Arithmetic updates ------*/

    Vector3& Vector3::operator += (const Vector3 & other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3& Vector3::operator -= (const Vector3 & other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3& Vector3::operator *= (double scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3& Vector3::operator *= (const Vector3 & other)
    {
        x*=other.x; 
        y*=other.y; 
        z*=other.z;
        return *this;
    }

    Vector3& Vector3::operator *= (const Matrix3 &mat)
    {
        this->set(
            mat.data()[0] * this->x + mat.data()[1] * this->y + mat.data()[2] * this->z,
            mat.data()[3] * this->x + mat.data()[4] * this->y + mat.data()[5] * this->z,
            mat.data()[6] * this->x + mat.data()[7] * this->y + mat.data()[8] * this->z
            );
        return *this;
    }

    Vector3& Vector3::operator *= (const Matrix4 &mat)
    {
        this->set(
            mat.data()[0] * this->x + mat.data()[1] * this->y + mat.data()[2]  * this->z + mat.data()[12],
            mat.data()[4] * this->x + mat.data()[5] * this->y + mat.data()[6]  * this->z + mat.data()[13],
            mat.data()[8] * this->x + mat.data()[9] * this->y + mat.data()[10] * this->z + mat.data()[14]
            );
        return *this;
    }

    Vector3& Vector3::operator /= (double scalar)
    {
        if (scalar == 0.0)
        {
            x = NAN;
            y = NAN;
            z = NAN;
        }
        else
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
        }
        return *this;
    }

    Vector3& Vector3::operator /= (const Vector3 &other)
    {
        if (other.x == 0.0)
            x = NAN;
        else
            x /= other.x;

        if (other.y == 0.0)
            y = NAN;
        else
            y /= other.y;

        if (other.z == 0.0)
            z = NAN;
        else
            z /= other.z;
        return *this;
    }

    /*------ Comparisons ------*/

    bool Vector3::operator == (const Vector3 & other) const
    {
        return (fabs(x-other.x) < gmath::EPSILON && 
                fabs(y-other.y) < gmath::EPSILON && 
                fabs(z-other.z) < gmath::EPSILON);
    }

    bool Vector3::operator != (const Vector3 & other) const
    {
        return (fabs(x-other.x) > gmath::EPSILON || 
                fabs(y-other.y) > gmath::EPSILON || 
                fabs(z-other.z) > gmath::EPSILON);
    }

    /*------ Assignments ------*/

    void Vector3::operator = (const Vector3 & other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    
    /*------ Methods ------*/

    Vector3 Vector3::clone() const {
        return Vector3(*this);
    }

    void Vector3::set(double inX, double inY, double inZ)
    {
        x = inX;
        y = inY;
        z = inZ;
    }

    void Vector3::set(const double* values)
    {
        x = values[0];
        y = values[1];
        z = values[2];
    }
    
    void Vector3::set(const std::vector<double>& values)
    {
        if (values.size()!=3)
            throw out_of_range("gmath::Matrix3: values must be of 3 elements");
        
        this->x = values[0];
        this->y = values[1];
        this->z = values[2];
    }

    Vector3 Vector3::cross(const Vector3 & other) const
    {
        Vector3 retVec(
                y*other.z - z*other.y,
                z*other.x - x*other.z,
                x*other.y - y*other.x);
        return retVec;
    }

    void Vector3::crossInPlace(const Vector3 & other)
    {
        double newx = y*other.z - z*other.y;
        double newy = z*other.x - x*other.z;
        double newz = x*other.y - y*other.x;
        x = newx;
        y = newy;
        z = newz;
    }

    Vector3 Vector3::crossNormalize(const Vector3 & other) const
    {
        Vector3 retVec(y*other.z - z*other.y,
                             z*other.x - x*other.z,
                             x*other.y - y*other.x);
        retVec.normalizeInPlace();
        return retVec;
    }

    void Vector3::crossNormalizeInPlace(const Vector3 & other)
    {
        crossInPlace(other);
        normalizeInPlace();
    }

    double Vector3::dot(const Vector3 & other) const
    {
        return x*other.x + y*other.y + z*other.z;
    }

    double Vector3::length() const
    {
        double dot = x*x + y*y + z*z;
        return sqrt( dot );
    }

    double Vector3::squaredLength() const
    {
        return x*x + y*y + z*z;
    }

    double Vector3::squaredDistance(const Vector3 & other) const
    {
        Vector3 distVec( (*this)-(other) );
        return distVec.squaredLength();
    }

    double Vector3::distance(const Vector3 & other) const
    {
        Vector3 distVec( (*this)-(other) );
        return distVec.length();
    }

    Vector3 Vector3::normalize() const
    {
        double len = length();
        double nlen;
        if (len < gmath::EPSILON)
        {
            nlen = 1.0;
        }
        else
        {
            nlen = 1.0/len;
        }

        return Vector3(x*nlen, y*nlen, z*nlen);
    }

    Vector3& Vector3::normalizeInPlace()
    {
        double len = length();

        double nlen;
        if (len < gmath::EPSILON)
        {
            nlen = 1.0;
        }
        else
        {
            nlen = 1.0/len;
        }

        x*=nlen;
        y*=nlen;
        z*=nlen;

        return *this;
    }

    Vector3 Vector3::inverse() const 
    {
        return Vector3(1.0/x, 1.0/y, 1.0/z);
    }

    Vector3& Vector3::inverseInPlace()
    {
        x = 1.0/x;
        y = 1.0/y;
        z = 1.0/z;
        return *this;
    }

    Vector3 Vector3::negate() const
    {
        return Vector3(-x, -y, -z);
    }

    Vector3& Vector3::negateInPlace()
    {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    double Vector3::angle(const Vector3 & other) const
    {
        double ang = gmath::acos((dot(other))); 
        return ang;
    }

    Vector3 Vector3::reflect(const Vector3 & normal) const
    {
        double dot = this->dot(normal);
        return ( normal * (2.0*dot) ) - *this;
    }

    void Vector3::reflectInPlace(const Vector3 & normal)
    {
        double dot = this->dot(normal);
        *this = ( normal * (2.0*dot) ) - *this;
    }

    Vector3 Vector3::refract(const Vector3 & normal, double eta) const
    {
        double dot = this->dot(normal);
        double k = 1.0 - eta*eta*(1.0 - dot*dot);

        Vector3 retVec;
        if (k >= gmath::EPSILON)
        {
            retVec = *this * eta;
            retVec -= normal * (eta*dot + sqrt(k));
        }
        return retVec;
    }

    void Vector3::refractInPlace(const Vector3 & normal, double eta)
    {
        double dot = this->dot(normal);
        double k = 1.0 - eta*eta*(1.0 - dot*dot);

        if (k >= gmath::EPSILON)
        {
            *this *= eta;
            *this -= normal * (eta*dot + sqrt(k));
        }
        else
        {
            this->set(double(0.0), double(0.0), double(0.0));
        }
    }

    Vector3 Vector3::mirror(const Vector3& normal) const 
    {
        Vector3 result(*this);
        result.mirrorInPlace(normal);
        return result;
    }

    void Vector3::mirrorInPlace(const Vector3& normal) 
    {
        Vector3 n = normal.normalize();
        Vector3 u = n*(this->dot(n));
        *this -= u*2.0;
    }

    Vector3 Vector3::mirror(CartesianPlane plane) const 
    {
        Vector3 normal;
        switch(plane) {
            case CartesianPlane::XY:
                normal = Vector3::ZAXIS;
                break;
            case CartesianPlane::YZ: 
                normal = Vector3::XAXIS;
                break;
            case CartesianPlane::ZX: 
                normal = Vector3::YAXIS;
                break; 
        }
        return mirror(normal);
    }

    void Vector3::mirrorInPlace(CartesianPlane plane) 
    {
        Vector3 normal;
        switch(plane) {
            case CartesianPlane::XY: 
                normal = Vector3::ZAXIS;
                break;
            case CartesianPlane::YZ: 
                normal = Vector3::XAXIS;
                break;
            case CartesianPlane::ZX: 
                normal = Vector3::YAXIS;
                break; 
        }
        return mirrorInPlace(normal);
    }

    Vector3 Vector3::linearInterpolate(const Vector3 & other, double weight) const
    {
        return Vector3((other.x - x) * weight + x,
                             (other.y - y) * weight + y,
                             (other.z - z) * weight + z);
    }

    void Vector3::linearInterpolateInPlace(const Vector3 & other, double weight)
    {
        x = (other.x - x) * weight + x;
        y = (other.y - y) * weight + y;
        z = (other.z - z) * weight + z;
    }

    std::string Vector3::toString() const
    {
        std::stringstream oss;
        oss << "gmath::Vector3(" << x << ", " << y << ", " << z << ");";

        return oss.str();
    }


    // Special Vectors.
    const Vector3 Vector3::XAXIS = Vector3(1.0, 0.0, 0.0);
    const Vector3 Vector3::YAXIS = Vector3(0.0, 1.0, 0.0);
    const Vector3 Vector3::ZAXIS= Vector3(0.0, 0.0, 1.0);

    const Vector3 Vector3::N_XAXIS = Vector3(-1.0, 0.0, 0.0);
    const Vector3 Vector3::N_YAXIS = Vector3(0.0, -1.0, 0.0);
    const Vector3 Vector3::N_ZAXIS = Vector3(0.0, 0.0, -1.0);

    const Vector3 Vector3::ZERO = Vector3(0.0, 0.0, 0.0);


    #ifdef CMAYA
        void Vector3::fromMayaVector(const MVector &mvector)
        {
            double dest[3];
            mvector.get(dest);
            this->set(dest);
        }

        MVector Vector3::toMayaVector() const 
        {
            return MVector(this->data());
        }
    #endif

    Vector3 getVector3FromAxis(Axis axis) 
    {
        switch(axis) {
            case Axis::POSX:
                return Vector3::XAXIS;
            case Axis::POSY:
                return Vector3::YAXIS;
            case Axis::POSZ:
                return Vector3::ZAXIS;
            case Axis::NEGX:
                return Vector3::N_XAXIS;
            case Axis::NEGY:
                return Vector3::N_YAXIS;
            case Axis::NEGZ:
                return Vector3::N_ZAXIS;
            default:
                return Vector3(NAN, NAN, NAN);
        }
    }
}