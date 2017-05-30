#include "gmQuaternion.h"

using namespace std;

namespace gmath{
    //--------------------------------------------------------------------------
    // Taken from Imath
    // Don Hatch's version of sin(x)/x, which is accurate for very small x.
    // Returns 1 for x == 0.
    //--------------------------------------------------------------------------
    inline double sinx_over_x (double x)
    {
    	if (x * x < gmath::EPSILON)
    		return 1.0;
    	else
    		return  sin (x) / x;
    }


    /*------ Constructors ------*/

    Quaternion::Quaternion()
    {
    	x=0.0; 
    	y=0.0;
    	z=0.0;
        w=1.0;
    }

    Quaternion::Quaternion(double x, double y, double z, double w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Quaternion::Quaternion(const Quaternion &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->w = other.w;
    }

    Quaternion::Quaternion(const Matrix3& inMat)
    {
        this->fromMatrix3(inMat);
    }

    Quaternion::Quaternion(const Matrix4& inMat)
    {
        this->fromMatrix4(inMat);
    }

    Quaternion::Quaternion(const Vector3& axis, double angle)
    {
        this->fromAxisAngle(axis, angle);
    }

    Quaternion::Quaternion(double angleX, double angleY, double angleZ)
    {
        this->fromEuler(angleX, angleY, angleZ);
    }

    Quaternion::Quaternion(const double *values)
    {
        set(values);
    }
    
    Quaternion::Quaternion(const std::vector<double>& values)
    {
        set(values);
    }

    /*------ Coordinate access ------*/

    double Quaternion::operator[] (int i) const
    {
        if (i>3) {
            throw out_of_range("gQuaternion:\n\t index out of range");
        }
        return *(&x+i);
    }

    double& Quaternion::operator[] (int i)
    {
        if (i>3) {
            throw out_of_range("gQuaternion:\n\t index out of range");
        }
        return *(&x+i);
    }

    double* Quaternion::data()
    {
        return &x;
    }

    const double* Quaternion::data() const
    {
        return &x;
    }

    /*------ Arithmetic operations ------*/

    Quaternion Quaternion::operator - () const
    {
    	return Quaternion(-x, -y, -z, -w);
    }

    Quaternion Quaternion::operator + (const Quaternion &other) const
    {
        Quaternion newQuaternion(x+other.x, y+other.y, z+other.z, w+other.w);

        return newQuaternion;
    }

    Quaternion Quaternion::operator - (const Quaternion &other) const
    {
        Quaternion newQuaternion(x-other.x, y-other.y, z-other.z, w-other.w);
        return newQuaternion;
    }

    Quaternion Quaternion::operator * (double scalar) const
    {
        Quaternion newQuaternion(x*scalar, y*scalar, z*scalar, w*scalar);

        return newQuaternion;
    }

    Quaternion Quaternion::operator * (const Quaternion &other) const
    {
        Quaternion result;

        result.x = w*other.x + x*other.w + y*other.z - z*other.y;
        result.y = w*other.y + y*other.w + z*other.x - x*other.z;
        result.z = w*other.z + z*other.w + x*other.y - y*other.x;
        result.w = w*other.w - (x*other.x + y*other.y + z*other.z);

        return result;
    }

    Vector3 Quaternion::operator * (const Vector3& vec) const
    {
        double tx, ty, tz;
    	double rx, ry, rz;

        tx = z * vec.y - y * vec.z;
        ty = x * vec.z - z * vec.x;
        tz = y * vec.x - x * vec.y;

        rx = z * ty - y * tz;
        ry = x * tz - z * tx;
        rz = y * tx - x * ty;

    	Vector3 v = vec;
    	v.x -= (tx*w-rx)*2; 
    	v.y -= (ty*w-ry)*2;
    	v.z -= (tz*w-rz)*2;
    	return v;
    }

    Quaternion Quaternion::operator / (double scalar) const
    {
        Quaternion newQuaternion;
        if (scalar == 0.0)
        {
            newQuaternion.x = NAN;
            newQuaternion.y = NAN;
            newQuaternion.z = NAN;
            newQuaternion.w = NAN;
        }
        else
        {
            newQuaternion.x = x/scalar;
            newQuaternion.y = y/scalar;
            newQuaternion.z = z/scalar;
            newQuaternion.w = w/scalar;
        }

        return newQuaternion;
    }

    /*------ Arithmetic updates ------*/

    Quaternion& Quaternion::operator += (const Quaternion & other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    Quaternion& Quaternion::operator -= (const Quaternion & other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    Quaternion& Quaternion::operator *= (double scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    Quaternion& Quaternion::operator *= (const Quaternion &other)
    {
        this->set(w*other.x + x*other.w + y*other.z - z*other.y,
                  w*other.y + y*other.w + z*other.x - x*other.z,
                  w*other.z + z*other.w + x*other.y - y*other.x,
                  w*other.w - x*other.x - y*other.y - z*other.z);
        return *this;
    }

    Quaternion& Quaternion::operator /= (double scalar)
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

    bool Quaternion::operator == (const Quaternion & other) const
    {
        return (fabs(x-other.x) < gmath::EPSILON && 
                fabs(y-other.y) < gmath::EPSILON && 
                fabs(z-other.z) < gmath::EPSILON &&
                fabs(w-other.w) < gmath::EPSILON);
    }

    bool Quaternion::operator != (const Quaternion & other) const
    {
        return (fabs(x-other.x) > gmath::EPSILON || 
                fabs(y-other.y) > gmath::EPSILON || 
                fabs(z-other.z) > gmath::EPSILON ||
                fabs(w-other.w) < gmath::EPSILON);
    }

    /*------ Assignments ------*/

    void Quaternion::operator = (const Quaternion & other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }

    /*------ Methods ------*/
    
    void Quaternion::set(double inX, double inY, double inZ, double inW)
    {
        x = inX;
        y = inY;
        z = inZ;
        w = inW;
    }

    void Quaternion::set(const double *values)
    {
        this->x = values[0];
        this->y = values[1];
        this->z = values[2];
        this->w = values[3];
    }
    
    void Quaternion::set(const std::vector<double>& values)
    {
        if (values.size()!=4)
            throw out_of_range("Quaternion: values must be of 4 elments");
        
        this->x = values[0];
        this->y = values[1];
        this->z = values[2];
        this->w = values[3];
    }

    void Quaternion::setToIdentity()
    {
    	x=0.0; y=0.0; z=0.0; w=1.0; 
    }

    Vector3 Quaternion::getAxisX() const
    {
        return (*this) * Vector3::XAXIS; 
    }

    Vector3 Quaternion::getAxisY() const
    {
        return (*this) * Vector3::YAXIS; 
    }

    Vector3 Quaternion::getAxisZ() const
    {
        return (*this) * Vector3::ZAXIS; 
    }

    void Quaternion::fromMatrix3(const Matrix3& mat)
    {
        // Code from Geometric Tools www.geometrictools.com
        // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
        // article "HQuaternion Calculus and Fast Animation".

        const int next[3] = { 1, 2, 0 };

        double trace = mat(0,0) + mat(1,1) + mat(2,2);
        double root;

        if (trace > 0)
        {
            // |w| > 1/2, may as well choose w > 1/2
            root = sqrt(trace + 1.0);  // 2w
            w = 0.5*root;
            root = 0.5/root;  // 1/(4w)
    		x = (mat(1,2) - mat(2,1))*root;
    		y = (mat(2,0) - mat(0,2))*root;
    		z = (mat(0,1) - mat(1,0))*root;
        }
        else
        {
            // |w| <= 1/2
            int i = 0;
            if (mat(1,1) > mat(0,0))
            {
                i = 1;
            }
            if (mat(2,2) > mat(i,i))
            {
                i = 2;
            }
            int j = next[i];
            int k = next[j];

            root = sqrt(mat(i,i) - mat(j,j) - mat(k,k) + 1.0);
            double* quat[3] = { &x, &y, &z };
            *quat[i] = 0.5*root;
            root = 0.5/root;
            this->w = (mat(j,k) - mat(k,j))*root;
            *quat[j] = (mat(i,j) + mat(j,i))*root;
            *quat[k] = (mat(i,k) + mat(k,i))*root;
        }
    }
    void Quaternion::fromMatrix4(const Matrix4& mat)
    {
        fromMatrix3(mat.toMatrix3());
    }

    Matrix3 Quaternion::toMatrix3() const
    {
        double xx = 2.0*x*x;
        double yy = 2.0*y*y;
        double zz = 2.0*z*z;
        double xy = 2.0*x*y;
        double zw = 2.0*z*w;
        double xz = 2.0*x*z;
        double yw = 2.0*y*w;
        double yz = 2.0*y*z;
        double xw = 2.0*x*w;
        return Matrix3(
                1.0-yy-zz, xy+zw,     xz-yw,
                xy-zw,     1.0-xx-zz, yz+xw,
                xz+yw,     yz-xw,     1.0-xx-yy 
                );
    }

    Matrix4 Quaternion::toMatrix4() const
    {
        double xx = 2.0*x*x;
        double yy = 2.0*y*y;
        double zz = 2.0*z*z;
        double xy = 2.0*x*y;
        double zw = 2.0*z*w;
        double xz = 2.0*x*z;
        double yw = 2.0*y*w;
        double yz = 2.0*y*z;
        double xw = 2.0*x*w;
        return Matrix4(
                1.0-yy-zz, xy+zw,     xz-yw,     0.0,
                xy-zw,     1.0-xx-zz, yz+xw,     0.0,
                xz+yw,     yz-xw,     1.0-xx-yy, 0.0,
                0.0,       0.0,       0.0,       1.0
                );
    }

    void Quaternion::setMatrix4(Matrix4& outMat) const
    {
        double xx = 2.0*x*x;
        double yy = 2.0*y*y;
        double zz = 2.0*z*z;
        double xy = 2.0*x*y;
        double zw = 2.0*z*w;
        double xz = 2.0*x*z;
        double yw = 2.0*y*w;
        double yz = 2.0*y*z;
        double xw = 2.0*x*w;
        outMat.set(
                1.0-yy-zz, xy+zw,     xz-yw,     0.0,
                xy-zw,     1.0-xx-zz, yz+xw,     0.0,
                xz+yw,     yz-xw,     1.0-xx-yy, 0.0,
                0.0,       0.0,       0.0,       1.0
                );
    }

    void Quaternion::setMatrix4(Matrix4& outMat, const Vector3& scale, const Vector3& pos) const
    {
        double xx = 2.0*x*x;
        double yy = 2.0*y*y;
        double zz = 2.0*z*z;
        double xy = 2.0*x*y;
        double zw = 2.0*z*w;
        double xz = 2.0*x*z;
        double yw = 2.0*y*w;
        double yz = 2.0*y*z;
        double xw = 2.0*x*w;
        outMat.set(
                1.0-yy-zz, xy+zw,     xz-yw,     0.0,
                xy-zw,     1.0-xx-zz, yz+xw,     0.0,
                xz+yw,     yz-xw,     1.0-xx-yy, 0.0,
                pos.x,     pos.y,     pos.z,     1.0);
    	outMat.setScale(scale);
    }

    void Quaternion::fromAxisAngle(const Vector3& axis, double angle)
    {
        // assert:  axis[] is unit length
        //
        // The quaternion representing the rotation is
        //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

        double halfAngle = angle/2.0;
        Vector3 quatVec = axis.normalize() * sin(halfAngle);
        w = cos(halfAngle);
        x = quatVec.x;
        y = quatVec.y;
        z = quatVec.z;
    }

    void Quaternion::toAxisAngle (Vector3& outAxis, double& outAngle) const
    {
        // The quaternion representing the rotation is
        //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

        double sqrLength = x*x + y*y
            + z*z;

        if (sqrLength > gmath::EPSILON)
        {
            outAngle = (2)*acos(w);
            double invLength;
    		if (sqrLength != 0)
    			invLength = 1/sqrt(sqrLength);
    		else
    			invLength = 0;
            outAxis.x = x*invLength;
            outAxis.y = y*invLength;
            outAxis.z = z*invLength;
        }
        else
        {
            // Angle is 0 (mod 2*gmath::PI), so any axis will do.
            outAngle = 0;
            outAxis.set(1, 0, 0);
        }
    }

    void Quaternion::fromEuler(double angleX, double angleY, double angleZ, RotationOrder order)
    {
    	Quaternion XQuat(Vector3::XAXIS, angleX);
        Quaternion YQuat(Vector3::YAXIS, angleY);
        Quaternion ZQuat(Vector3::ZAXIS, angleZ);

        switch (order)
        {
        case XYZ :
            (*this) = XQuat*(YQuat*ZQuat);
            break;
        case XZY :
            (*this) = XQuat*(ZQuat*YQuat);
            break;
        case YXZ :
            (*this) = YQuat*(XQuat*ZQuat);
            break;
        case YZX :
            (*this) = YQuat*(ZQuat*XQuat);
            break;
        case ZXY :
            (*this) = ZQuat*(XQuat*YQuat);
            break;
        case ZYX :
            (*this) = ZQuat*(YQuat*XQuat);
            break;
        }
    }

    void Quaternion::fromEuler(const Euler& euler, RotationOrder order)
    {
        // ensure euler is radians
		Euler r = euler.toRadians();
    	this->fromEuler(r.x, r.y, r.z, order);
    }

    Euler Quaternion::toEuler(RotationOrder order) const
    {
    	Matrix3 mat = this->toMatrix3();
    	return mat.toEuler(order);
    }

    double Quaternion::length () const
    {
    	return sqrt(w*w + x*x + y*y + z*z);
    }

    double Quaternion::squaredLength () const
    {
    	return w*w + x*x + y*y + z*z;
    }

    void Quaternion::normalizeInPlace ()
    {
    	double len = length();

    	if (len > gmath::EPSILON)
    	{
    		double invLength = (1)/len;
    		w *= invLength;
    		x *= invLength;
    		y *= invLength;
    		z *= invLength;
    	}
    	else
    	{
    		w = 0;
    		x = 0;
    		y = 0;
    		z = 0;
    	}
    }

    Quaternion Quaternion::normalize () const
    {
    	Quaternion retQuat;
    	double len = length();

    	if (len > gmath::EPSILON)
    	{
    		double invLength = (1)/len;
    		retQuat.w = w*invLength;
    		retQuat.x = x*invLength;
    		retQuat.y = y*invLength;
    		retQuat.z = z*invLength;
    	}
    	else
    	{
    		retQuat.w = 0;
    		retQuat.x = 0;
    		retQuat.y = 0;
    		retQuat.z = 0;
    	}
        return retQuat;
    }

    void Quaternion::inverseInPlace ()
    {
    	double norm = squaredLength();
    	if (norm > 0)
    	{
    		double invNorm = (1)/norm;
    		w = w*invNorm;
    		x = -x*invNorm;
    		y = -y*invNorm;
    		z = -z*invNorm;
    	}
    	else
    	{
    		// Return an invalid result to flag the error.
    		set(0, 0, 0, 0);
    	}
    }

    Quaternion Quaternion::inverse () const
    {
    	Quaternion inv;

    	double norm = squaredLength();
    	if (norm > 0)
    	{
    		double invNorm = (1)/norm;
    		inv.w = w*invNorm;
    		inv.x = -x*invNorm;
    		inv.y = -y*invNorm;
    		inv.z = -z*invNorm;
    	}
    	else
    	{
    		// Return an invalid result to flag the error.
    		inv.set(0, 0, 0, 0);
    	}

    	return inv;
    }

    void Quaternion::conjugateInPlace ()
    {
    	set(-x, -y, -z, w);
    }

    Quaternion Quaternion::conjugate () const
    {
    	return Quaternion(-x, -y, -z, w);
    }

    Quaternion Quaternion::exp () const
    {
    	// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    	// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
    	// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

    	Quaternion result;

    	double angle = sqrt(x*x + y*y + z*z);

    	double sn = sin(angle);
    	result.w = cos(angle);

    	if (fabs(sn) >= gmath::EPSILON)
    	{
    		double coeff = sn/angle;

    		result.x = coeff*this->x;
    		result.y = coeff*this->y;
    		result.z = coeff*this->z;
    		//result.w = coeff*this->w;
    	}
    	else
    	{
    		result.x = this->x;
    		result.y = this->y;
    		result.z = this->z;
    		//result.w = this->w;
    	}

    	return result;
    }

    Quaternion Quaternion::log () const
    {
    	// If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    	// log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
    	// sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

    	Quaternion result;
    	result.w = 0;

    	if (fabs(w) < 1)
    	{
    		double angle = acos(w);
    		double sn = sin(angle);
    		if (fabs(sn) >= gmath::EPSILON)
    		{
    			double coeff = angle/sn;
    			result.x = coeff*this->x;
    			result.y = coeff*this->y;
    			result.z = coeff*this->z;
    			//result.w = coeff*this->w;
    			return result;
    		}
    	}

    	result.x = this->x;
    	result.y = this->y;
    	result.z = this->z;
    	result.w = this->w;
    	return result;
    }

    double Quaternion::dot(const Quaternion & other) const
    {
        return x*other.x + y*other.y + z*other.z + w*other.w;
    }

    void Quaternion::slerpInPlace(const Quaternion &q1, const Quaternion &q2, double t, bool shortestPath)
    {	
    	Quaternion Q2 = q2;
        if (q1.dot(q2)<0.0)
        {
            Q2 = -q2;
        }

        Quaternion qd = q1 - Q2;
        double lengthD =  sqrt (qd.dot(qd));

        Quaternion qs = q1 + Q2;
        double lengthS =  sqrt (qs.dot(qs));

        double a = 2.0 *  atan2(lengthD, lengthS);
        double s = 1.0 - t;

    	(*this) = 
            q1 * (sinx_over_x(s * a) / sinx_over_x(a) * s)  +
            Q2 * (sinx_over_x(t * a) / sinx_over_x(a) * t) ;
    }

    Quaternion Quaternion::slerp(const Quaternion &q2, double t, bool shortestPath) const
    {	
    	Quaternion Q2 = q2;
        if ((*this).dot(q2)<0.0)
        {
            Q2 = -q2;
        }

        Quaternion qd = (*this) - Q2;
        double lengthD =  sqrt (qd.dot(qd));

        Quaternion qs = (*this) + Q2;
        double lengthS =  sqrt (qs.dot(qs));

        double a = 2.0 *  atan2(lengthD, lengthS);
        double s = 1.0 - t;

    	return
            (*this) * (sinx_over_x(s * a) / sinx_over_x(a) * s)  +
            Q2 * (sinx_over_x(t * a) / sinx_over_x(a) * t) ;
    }

    std::string Quaternion::toString() const
    {
        std::stringstream oss;
        oss << "gmath::Quaternion("<< x <<", "<< y <<", "<< z <<", "<< w <<");";

        return oss.str();
    }

}
